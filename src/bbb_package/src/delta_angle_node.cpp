// this node is used for tuning fuzzy parameters

/**
 * @file delta_angle_node.cpp
 * @author Hoan Duong & Hien Nguyen
 * @brief the delta_angle_node of my thesis at my university, Ho Chi Minh University of Technology.
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
  FuzzyNodeTest() : Node("delta_angle_node"), flag(0.0){
    publisher_flag_ = this->create_publisher<std_msgs::msg::Float64MultiArray>("/flag", 3);
    timer_ = this->create_wall_timer(std::chrono::milliseconds(100), std::bind(&FuzzyNodeTest::timer_callback, this));
  }

 private:
  void timer_callback() {
    // Publish message with reference map
      auto message = std_msgs::msg::Float64MultiArray();
      message.data.resize(1); // Set size of data vector to 4
      message.data[0] = flag;
      flag++;
      message.layout.data_offset = 777;
      publisher_flag_->publish(message);
  }
  double flag;
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr publisher_flag_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<FuzzyNodeTest>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}