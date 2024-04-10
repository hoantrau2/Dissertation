/**
 * @file stanley_node.cpp
 * @author Hoan Duong & Hien Nguyen
 * @brief the stanley_node of my thesis at my university, Ho Chi Minh University of Technology.
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

#define Kp 10
#define Ksoft 10
#define SAMPLE_TIME 100

class StanleyNode : public rclcpp::Node {
 public:
  StanleyNode()
    : Node("stanley_node"), angleIMU(0.0), linearVelocity(0.0), actual_position({0.0, 0.0, 0.0}), desired_position({0.0, 0.0, 0.0}) {

    subscription_angle_IMU_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
      "/angle_IMU", 10, std::bind(&StanleyNode::angle_IMU_callback, this, std::placeholders::_1));

    subscription_actual_velocities_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
      "/actual_velocities", 10, std::bind(&StanleyNode::actual_velocities_callback, this, std::placeholders::_1));

    subscription_tf_ = this->create_subscription<tf2_msgs::msg::TFMessage>(
      "/tf", 10, std::bind(&StanleyNode::tf_callback, this, std::placeholders::_1));

    subscription_reference_map_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
      "/reference_map", 10, std::bind(&StanleyNode::reference_map_callback, this, std::placeholders::_1));

    publisher_delta_angle_ = this->create_publisher<std_msgs::msg::Float64MultiArray>("/delta_angle", 10);
    timer_ = this->create_wall_timer(std::chrono::milliseconds(SAMPLE_TIME), std::bind(&StanleyNode::timer_callback, this));
  }

 private:
  void timer_callback() {
    // double error_distace = -(actual_position[0] - desired_positon[0]) * std::cos(actual_position[2]) +
    //                        (actual_position[1] - desired_positon[1]) * std::sin(actual_position[2]);
    // double angle_stenley_output = desired_positon[2] - std::atan2(Kp * error_distace, Ksoft + linear_velocity);

    double error_distace = sqrt(pow((actual_position[0] - desired_position[0]), 2) + pow((actual_position[1] - desired_position[1]), 2));
    double angle_stenley_output;
    if (actual_position[2] - desired_position[2] >= 0)
      angle_stenley_output = actual_position[2] - desired_position[2] + std::atan2(Kp * error_distace, Ksoft + linearVelocity);
    else
      angle_stenley_output = actual_position[2] - desired_position[2] - std::atan2(Kp * error_distace, Ksoft + linearVelocity);
    // publish message with delta angle
    auto message = std_msgs::msg::Float64MultiArray();
    message.data.resize(1); 
    message.data[0] = angle_stenley_output;
    RCLCPP_INFO(this->get_logger(), " angle_stenley_output = %lf ", message.data[0]);
    message.layout.data_offset = 555;
    publisher_delta_angle_->publish(message);
  }

  void actual_velocities_callback(const std_msgs::msg::Float64MultiArray::SharedPtr msg) {
    if (msg->layout.data_offset == 222 && msg->data.size() == 4) {
      // Handle actual velocities data
      linearVelocity = ((msg->data[0] + msg->data[1]) / 2 + (msg->data[2] + msg->data[3]) / 2) / 2;
    } else {
      RCLCPP_ERROR(this->get_logger(), "Invalid message format or size of /actual_velocities topic");
    }
  }

  void angle_IMU_callback(const std_msgs::msg::Float64MultiArray::SharedPtr msg) {
    if (msg->layout.data_offset == 444 && msg->data.size() == 1) {
      // RCLCPP_INFO(this->get_logger(), "Received angle of IMU");
      // Handle actual angle IMU
      angleIMU = msg->data[0];
    } else {
      RCLCPP_ERROR(this->get_logger(), "Invalid message format or size of /angle_IMU topic");
    }
  }

  void reference_map_callback(
    const std_msgs::msg::Float64MultiArray::SharedPtr msg) {
    if (msg->layout.data_offset == 666 && msg->data.size() == 3) {
      // RCLCPP_INFO(this->get_logger(), "Received a reference map");
      // Handle a reference map
      for (size_t i = 0; i < 3; ++i) {
        desired_position[i] = msg->data[i];
      }
      // RCLCPP_INFO(this->get_logger(), " reference x = %lf   y = %lf   yaw = %lf ", desired_position[0], desired_position[1], desired_position[2]);
    } else {
      RCLCPP_ERROR(this->get_logger(), "Invalid message format or size of /reference_map topic ");
    }
  }

  void tf_callback(const tf2_msgs::msg::TFMessage::SharedPtr msg) {
    for (auto transform : msg->transforms) {
      if (transform.child_frame_id == "base_footprint") {
        // RCLCPP_INFO(this->get_logger(), "Received a reference map");
        // Handle a reference map
        actual_position[0] = transform.transform.translation.x;
        actual_position[1] = transform.transform.translation.y;
        actual_position[2] = transform.transform.rotation.z;
        RCLCPP_INFO(this->get_logger(), " actual x = %lf   y = %lf   yaw = %lf ", actual_position[0], actual_position[1], actual_position[2]);
        break; // Exit loop after finding the desired transform
      }
    }
  }

  double angleIMU;
  double linearVelocity;
  std::vector<double> actual_position;
  std::vector<double> desired_position;
  rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr subscription_angle_IMU_;
  rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr subscription_actual_velocities_;
  rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr subscription_reference_map_;
  rclcpp::Subscription<tf2_msgs::msg::TFMessage>::SharedPtr subscription_tf_;
  rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr publisher_delta_angle_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<StanleyNode>());
  rclcpp::shutdown();
  return 0;
}