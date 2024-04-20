/**
 * @file circumference_node.cpp
 * @author Hoan Duong & Hien Nguyen
 * @brief the circumference node of my thesis at my university, Ho Chi Minh University of Technology.
 * @version 1
 * @date 2024-03-30
 */
#include <chrono>
#include <cmath>
#include <functional>
#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"

#define LINEAR_VELOCITY 0.5
#define RADIUS 0.7
#define SAMPLE_ANGLE (15.0 * M_PI / 180.0) // 100ms

class CircumferenceNode : public rclcpp::Node {
 public:
  CircumferenceNode() : Node("circumference_node"), flag(0.0) {
    subscription_flag_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
      "/flag", 10, std::bind(&CircumferenceNode::flag_callback, this, std::placeholders::_1));

    publisher_reference_map_ = this->create_publisher<std_msgs::msg::Float64MultiArray>("/reference_map", 10);
    // timer_ = this->create_wall_timer(std::chrono::milliseconds(SAMPLE_TIME), std::bind(&StraightLineNode::timer_callback, this));
  }

 private:
  // void timer_callback() {
  void flag_callback(const std_msgs::msg::Float64MultiArray::SharedPtr msg) {
    if (msg->layout.data_offset == 777 && msg->data.size() == 1) {
      flag = msg->data[0];
      // push values to debug
      // RCLCPP_INFO(this->get_logger(), "Received flag = %lf", flag);

      auto message = std_msgs::msg::Float64MultiArray();
      message.data.resize(2);
      message.data[0] = RADIUS * std::sin(SAMPLE_ANGLE * flag);
      message.data[1] = -RADIUS * std::cos(SAMPLE_ANGLE * flag) +RADIUS;
      message.layout.data_offset = 666;
      // push values to debug
      // RCLCPP_INFO(this->get_logger(), "Reference map: x = %lf, y = %lf", message.data[0], message.data[1]);
      publisher_reference_map_->publish(message);
    } else {
      RCLCPP_ERROR(this->get_logger(), "Invalid message format or size of /flag topic");
    }
  }
  double flag;
  rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr subscription_flag_;
  rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr publisher_reference_map_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<CircumferenceNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
