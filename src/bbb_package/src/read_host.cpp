#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "std_msgs/msg/string.hpp"

using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node {
public:
  MinimalSubscriber() : Node("read_host") {
    subscription_ = this->create_subscription<geometry_msgs::msg::Twist>(
        "/cmd_vel", 10,
        std::bind(&MinimalSubscriber::topic_callback, this, _1));
  }
private:
  void
     topic_callback(const geometry_msgs::msg::Twist::SharedPtr msg) const {
     RCLCPP_INFO(this->get_logger(), "linear_x: %lf",msg->linear.x);
     RCLCPP_INFO(this->get_logger(), "angular_z: %lf",msg->angular.z);

  }
  rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr subscription_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}