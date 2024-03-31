/**
 * @file fuzzy_node_test.cpp
 * @author Hoan Duong
 * @brief the pid_node of my thesis at my university, Ho Chi Minh University of
 * Technology.
 * @version 1
 * @date 2024-03-27
 */
#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"

class FuzzyNodeTest : public rclcpp::Node {
 public:
  FuzzyNodeTest() : Node("fuzzy_node_test"){
    publisher_velocity_fuzzy_ = this->create_publisher<std_msgs::msg::Float64MultiArray>("/velocity_fuzzy", 3);
    timer_ = this->create_wall_timer(std::chrono::milliseconds(10), std::bind(&FuzzyNodeTest::timer_callback, this));
  }

 private:
  void timer_callback() {
    // Publish message with reference map
    auto message = std_msgs::msg::Float64MultiArray();
    message.data.resize(2); // Set size of data vector to 3
    message.data[0] = 0.5;
    message.data[1] = 0.5;
    message.layout.data_offset = 333;
    RCLCPP_INFO(this->get_logger(), "%lf   %lf ", message.data[0], message.data[1]);
    publisher_velocity_fuzzy_->publish(message);
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr publisher_velocity_fuzzy_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<FuzzyNodeTest>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}