/**
 * @file sinusoidal_node.cpp
 * @author Hoan Duong
 * @brief the sinusoidal node of my thesis at my university,
 * Ho Chi Minh University of Technology.
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

#define LINEAR_VELOCITY 1.0
#define RADIUS 0.5

class SinusoidalNode : public rclcpp::Node {
 public:
  SinusoidalNode() : Node("sinusoidal_node"), x_position(0.0), y_position(0.0), yaw_angle(0.0) {
    start_time_ = std::chrono::steady_clock::now();
    publisher_reference_map_ = this->create_publisher<std_msgs::msg::Float64MultiArray>("/reference_map", 10);
    timer_ = this->create_wall_timer(std::chrono::milliseconds(10), std::bind(&SinusoidalNode::timer_callback, this));
  }

 private:
  void timer_callback() {
    auto current_time = std::chrono::steady_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time_).count() / 1000.0; // convert ms to s

    // Calculate position based on time and velocity
    if (elapsed_time <= 1.5) {
      x_position = LINEAR_VELOCITY * elapsed_time;
      y_position = 0.0;
      yaw_angle = 0.0;
    } else {
      x_position = LINEAR_VELOCITY * elapsed_time;
      y_position = RADIUS * std::sin(0.1 * 3.14 * (elapsed_time - 1.5));
      yaw_angle = std::atan2(y_position, x_position);
    }

    // Publish message with reference map
    auto message = std_msgs::msg::Float64MultiArray();
    message.data.resize(3); // Set size of data vector to 3
    message.data[0] = x_position;
    message.data[1] = y_position;
    message.data[2] = yaw_angle;
    message.layout.data_offset = 333;
    RCLCPP_INFO(this->get_logger(), "%lf   %lf    %lf   %lf", message.data[0], message.data[1], message.data[2], (double)elapsed_time);
    publisher_reference_map_->publish(message);
  }

  double x_position, y_position, yaw_angle;
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr publisher_reference_map_;
  std::chrono::steady_clock::time_point start_time_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<SinusoidalNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
