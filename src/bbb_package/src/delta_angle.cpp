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
  FuzzyNodeTest() : Node("delta_angle_node"), angleIMU(0.0){

    subscription_angle_IMU_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
      "/angle_IMU", 10, std::bind(&FuzzyNodeTest::angle_IMU_callback, this, std::placeholders::_1));

    start_time_ = std::chrono::steady_clock::now();
    publisher_delta_angle_ = this->create_publisher<std_msgs::msg::Float64MultiArray>("/delta_angle", 3);
    timer_ = this->create_wall_timer(std::chrono::milliseconds(100), std::bind(&FuzzyNodeTest::timer_callback, this));
  }

 private:
  void timer_callback() {
    // Publish message with reference map
    auto current_time = std::chrono::steady_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time_).count() / 1000.0; // convert ms to s
    double desired_angle;
    auto message = std_msgs::msg::Float64MultiArray();
    message.data.resize(2); // Set size of data vector to 
    message.layout.data_offset = 555;
         if (elapsed_time <= 3) desired_angle = M_PI/4 ;
         else if (elapsed_time <= 8.0) desired_angle = M_PI/4 ;
         else if (elapsed_time <= 11.0) desired_angle = M_PI/4 ;
         else if (elapsed_time <= 16.0)  desired_angle =  M_PI/4 ;
         else desired_angle =   M_PI/4;
    message.data[0] = desired_angle -angleIMU;
    message.data[1] = 0.3;
    RCLCPP_INFO(this->get_logger(), "desired angle = %lf, time = %lf  " ,desired_angle, elapsed_time );
    publisher_delta_angle_->publish(message);
  }

    void angle_IMU_callback(const std_msgs::msg::Float64MultiArray::SharedPtr msg) {
    if (msg->layout.data_offset == 444 && msg->data.size() == 1) {
      angleIMU = msg->data[0] * M_PI / 180.0; // Convert to radians
    } else {
      RCLCPP_ERROR(get_logger(), "Invalid message format or size of /angle_IMU topic");
    }
  }
  double angleIMU;
  rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr subscription_angle_IMU_;
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr publisher_delta_angle_;
  std::chrono::steady_clock::time_point start_time_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<FuzzyNodeTest>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}



