/**
 * @file data_processing_node.cpp
 * @author Hoan Duong & Hien Nguyen
 * @brief Data processing node for thesis project at Ho Chi Minh University of Technology.
 * @version 1
 * @date 2024-03-29
 */

#include <cmath>
#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include "tf2_msgs/msg/tf_message.hpp"

#define SAMPLE_TIME 100
#define Kp 0.3
#define Ksoft 0

#define A (std::tan(M_PI / 4))
#define B 0
#define STEP_DISTANCE 0.02
#define COUNTER 250

class DataProcessingNode : public rclcpp::Node {
 public:
  DataProcessingNode()
    : Node("data_processing_node_straight"), angleIMU(0.0), actual_position({0.0, 0.0}), index(0), d(0.0) {
    initializeArrays();
    setupSubscribersAndPublishers();
    setupTimer();
    RCLCPP_INFO(get_logger(), "Data processing node initialized.");
  }

 private:
  double angleIMU;
  std::vector<double> actual_position;
  int index;
  double d ;
  double x[COUNTER];
  double y[COUNTER];
  double theta[COUNTER];
  rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr subscription_angle_IMU_;
  rclcpp::Subscription<tf2_msgs::msg::TFMessage>::SharedPtr subscription_tf_;
  rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr publisher_delta_;
  rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr publisher_position_;
  rclcpp::TimerBase::SharedPtr timer_;

  void initializeArrays() {
    x[0] = 0;
    y[0] = 0;
    theta[0] = std::atan2(A, 1);
    RCLCPP_INFO(this->get_logger(), "Initializing arrays...");
    for (int i = 1; i <= COUNTER; i++) {
      x[i] = x[i - 1] + STEP_DISTANCE;
      y[i] = A * x[i] + B;
      theta[i] = std::atan2(A, 1);
      RCLCPP_INFO(this->get_logger(), "x[%d] = %lf, y[%d] = %lf, theta[%d] = %lf", i, x[i], i, y[i], i, theta[i]);
    }
  }

  void setupSubscribersAndPublishers() {
    subscription_angle_IMU_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
      "/angle_IMU", 10, std::bind(&DataProcessingNode::angle_IMU_callback, this, std::placeholders::_1));

    subscription_tf_ = this->create_subscription<tf2_msgs::msg::TFMessage>(
      "/tf", 10, std::bind(&DataProcessingNode::tf_callback, this, std::placeholders::_1));

    publisher_delta_ = this->create_publisher<std_msgs::msg::Float64MultiArray>("/delta", 10);
    publisher_position_ = this->create_publisher<std_msgs::msg::Float64MultiArray>("/position", 10);
  }

  void setupTimer() {
    timer_ = this->create_wall_timer(std::chrono::milliseconds(SAMPLE_TIME), std::bind(&DataProcessingNode::timer_callback, this));
  }

  void timer_callback() {
    double d_min = std::sqrt(std::pow((actual_position[0] - x[index]), 2) + std::pow((actual_position[1] - y[index]), 2));;
    for (int i = index+1; i < std::min(index + 10, COUNTER); i++) {
       d = std::sqrt(std::pow((actual_position[0] - x[i]), 2) + std::pow((actual_position[1] - y[i]), 2));
      if (d < d_min) {
        d_min = d;
        index = i;
      }
    }
      double arctann = std::atan2(Kp * d_min, Ksoft + 0.4);
    if (arctann > 20 * M_PI / 180)
      arctann = 20 * M_PI / 180;
    else if (arctann < -20 * M_PI / 180)
      arctann = -20 * M_PI / 180;

    auto message = std_msgs::msg::Float64MultiArray();
    message.data.resize(2);
    if (std::atan2(actual_position[1], actual_position[0]) - theta[int(index)] >= 0)
      message.data[0] = theta[int(index)]- angleIMU - arctann;
      // message.data[0] = 45 * M_PI / 180- angleIMU - arctann;
    else
      message.data[0] = theta[int(index)] - angleIMU + arctann;
      // message.data[0] = 45 * M_PI / 180- angleIMU - arctann;
// message.data[0] = theta[int(index)] - angleIMU ;
// message.data[0] = 45 * M_PI / 180- angleIMU ;
    message.data[1] = d_min ;
    message.layout.data_offset = 555;
    publisher_delta_->publish(message);
  }

  void angle_IMU_callback(const std_msgs::msg::Float64MultiArray::SharedPtr msg) {
    if (msg->layout.data_offset == 444 && msg->data.size() == 1) {
      angleIMU = msg->data[0] * M_PI / 180.0; // Convert to radians
    } else {
      RCLCPP_ERROR(get_logger(), "Invalid message format or size of /angle_IMU topic");
    }
  }

  void tf_callback(const tf2_msgs::msg::TFMessage::SharedPtr msg) {
    for (auto transform : msg->transforms) {
      if (transform.child_frame_id == "base_footprint") {
        actual_position[0] = -transform.transform.translation.x;
        actual_position[1] = transform.transform.translation.y;
        auto message2 = std_msgs::msg::Float64MultiArray();
        message2.data.resize(6); // Set size of data vector to 4
        message2.data[0] = actual_position[0];
        message2.data[1] = actual_position[1];
        message2.data[2] = angleIMU;
        message2.data[3] = d;
        message2.data[4] = index;
        message2.data[5]  = theta[int(index)];
        message2.layout.data_offset = 888;
        publisher_position_->publish(message2);
        break; // Exit loop after finding the desired transform
      } else {
        RCLCPP_ERROR(get_logger(), "Invalid message format or size of /tf topic ");
        break;
      }
    }
  }
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<DataProcessingNode>());
  rclcpp::shutdown();
  return 0;
}