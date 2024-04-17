/**
 * @file data_processing_node.cpp
 * @author Hoan Duong & Hien Nguyen
 * @brief the data processing node of my thesis at my university, Ho Chi Minh University of Technology.
 * @version 1
 * @date 2024-03-29
 */
#include <algorithm>
#include <chrono>
#include <cmath>
#include <functional>
#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include "tf2_msgs/msg/tf_message.hpp"

#define SAMPLE_TIME 100
#define ACCEPTED_ERROR 0.035 // 3.5 cm

class DataProcessingNode : public rclcpp::Node {
 public:
  DataProcessingNode()
    : Node("data_processing_node"), angleIMU(0.0), flag(0.0), actual_position({0.0, 0.0}), desired_position({0.0, 0.0}) {
    subscription_angle_IMU_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
      "/angle_IMU", 10, std::bind(&DataProcessingNode::angle_IMU_callback, this, std::placeholders::_1));

    subscription_tf_ = this->create_subscription<tf2_msgs::msg::TFMessage>(
      "/tf", 10, std::bind(&DataProcessingNode::tf_callback, this, std::placeholders::_1));

    subscription_reference_map_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
      "/reference_map", 10, std::bind(&DataProcessingNode::reference_map_callback, this, std::placeholders::_1));

    publisher_flag_ = this->create_publisher<std_msgs::msg::Float64MultiArray>("/flag", 10);

    publisher_delta_ = this->create_publisher<std_msgs::msg::Float64MultiArray>("/delta", 10);
    timer_ = this->create_wall_timer(std::chrono::milliseconds(SAMPLE_TIME), std::bind(&DataProcessingNode::timer_callback, this));
    RCLCPP_ERROR(get_logger(), "data_processing_node initialized.");
  }

 private:
  void timer_callback() {
    double deltaDistance = sqrt(pow((actual_position[0] - desired_position[0]), 2) + pow((actual_position[1] - desired_position[1]), 2));
    double deltaAngle = std::atan2((desired_position[1] -actual_position[1]), (desired_position[0]-actual_position[0]) )-angleIMU;

    auto message = std_msgs::msg::Float64MultiArray();
    message.data.resize(2); // Set size of data vector to 4
    message.data[0] = deltaAngle;
    message.data[1] = deltaDistance;
    message.layout.data_offset = 555;
    publisher_delta_->publish(message);

    if (deltaDistance < ACCEPTED_ERROR) {
      flag++;
      auto message = std_msgs::msg::Float64MultiArray();
      message.data.resize(1); // Set size of data vector to 4
      message.data[0] = flag;
      message.layout.data_offset = 777;
      publisher_flag_->publish(message);
    }
  }

  void angle_IMU_callback(const std_msgs::msg::Float64MultiArray::SharedPtr msg) {
    if (msg->layout.data_offset == 444 && msg->data.size() == 1) {
      // RCLCPP_INFO(this->get_logger(), "Received angle of IMU");
      // Handle actual angle IMU
      angleIMU = msg->data[0] * M_PI / 180.0; // radian
    } else {
      RCLCPP_ERROR(this->get_logger(), "Invalid message format or size of /angle_IMU topic");
    }
  }

  void reference_map_callback(
    const std_msgs::msg::Float64MultiArray::SharedPtr msg) {
    if (msg->layout.data_offset == 666 && msg->data.size() == 2) {
      // Handle a reference map
      desired_position[0] = msg->data[0];
      desired_position[1] = msg->data[1];
    } else {
      RCLCPP_ERROR(this->get_logger(), "Invalid message format or size of /reference_map topic ");
    }
  }

  void tf_callback(const tf2_msgs::msg::TFMessage::SharedPtr msg) {
    for (auto transform : msg->transforms) {
      if (transform.child_frame_id == "base_footprint") {
        // RCLCPP_INFO(this->get_logger(), "Received a reference map");
        // Handle a reference map
        actual_position[0] = -transform.transform.translation.x;
        actual_position[1] =  transform.transform.translation.y;
        break; // Exit loop after finding the desired transform
      } else {
        RCLCPP_ERROR(this->get_logger(), "Invalid message format or size of /tf topic ");
        break;
      }
    }
  }

  double angleIMU;
  double flag;
  std::vector<double> actual_position;
  std::vector<double> desired_position;
  rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr subscription_angle_IMU_;
  rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr subscription_reference_map_;
  rclcpp::Subscription<tf2_msgs::msg::TFMessage>::SharedPtr subscription_tf_;
  rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr publisher_delta_;
  rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr publisher_flag_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<DataProcessingNode>());
  rclcpp::shutdown();
  return 0;
}
