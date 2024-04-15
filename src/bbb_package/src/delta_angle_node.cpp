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
#include <cmath>

class FuzzyNodeTest : public rclcpp::Node {
 public:
  FuzzyNodeTest() : Node("delta_angle_node"){
    // start_time_ = std::chrono::steady_clock::now();
    publisher_desired_velocities_ = this->create_publisher<std_msgs::msg::Float64MultiArray>("/delta_angle", 3);
    timer_ = this->create_wall_timer(std::chrono::milliseconds(50), std::bind(&FuzzyNodeTest::timer_callback, this));
  }

 private:
  void timer_callback() {
    // Publish message with reference map
    // auto current_time = std::chrono::steady_clock::now();
    // auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time_).count() / 1000.0; // convert ms to s
 
    auto message = std_msgs::msg::Float64MultiArray();
    message.data.resize(1); // Set size of data vector to 
    message.layout.data_offset = 555;
      //    if (elapsed_time <= 5.0) {
      // message.data[0] = 30.0;
      // } else if (elapsed_time <= 20.0) {
      //   message.data[0] = 90.0;
      // // } else if (elapsed_time <= 30.0) {
      // //   message.data[0] = 1.3;
      // //   message.data[1] = 1.3;
      // } else {
        message.data[0] = 30.0;
      // }

      // // sine
      // static int cnt = 0;
      // cnt = cnt + 1;
      // if(cnt > 360){
      //   cnt = 0;
      // }
      // message.data[0] = 30*sin(cnt*3.14/180);

    RCLCPP_INFO(this->get_logger(), "delta angle = %lf  ", message.data[0]);
    publisher_desired_velocities_->publish(message);
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr publisher_desired_velocities_;
  // std::chrono::steady_clock::time_point start_time_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<FuzzyNodeTest>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}