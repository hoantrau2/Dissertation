#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include <chrono>
#include <functional>
#include <memory>
#include <string>

using namespace std::chrono_literals;

class PIDNode : public rclcpp::Node {
public:
  PIDNode() : Node("pid_node") {
    subscription_actual_angle_ =
        this->create_subscription<std_msgs::msg::Float64MultiArray>(
            "/actual_angle", 10,
            std::bind(&PIDNode::actual_angle_callback, this, _1));

    subscription_velocity_fuzzy_ =
        this->create_subscription<std_msgs::msg::Float64MultiArray>(
            "/velocity_fuzzy", 10,
            std::bind(&PIDNode::velocity_fuzzy_callback, this, _1));

    publisher_desired_angle_ =
        this->create_publisher<std_msgs::msg::Float64MultiArray>(
            "/desired_angle", 10);
    timer_ = this->create_wall_timer(
        500ms, std::bind(&PIDNode::timer_callback,
                         this)); // use create_wall_timer to timer, timer 500ms
                                 // call timer_callback
  }

private:
  void timer_callback() {
    auto message = std_msgs::msg::Float64MultiArray();
    message.data.push_back(12.3);
    message.data.push_back(12.3);
    message.data.push_back(12.3);
    message.data.push_back(12.3);
    publisher_desired_angle_->publish(message);
  }
  void
  actual_angle_callback(const std_msgs::msg::Float64MultiArray::SharedPtr msg) {
    // Handle actual angle data
    RCLCPP_INFO(this->get_logger(), "Received actual angle");
    // Your logic here
    RCLCPP_INFO(this->get_logger(), "actual angle of motor 1: %f",
                msg->data[0]);
    RCLCPP_INFO(this->get_logger(), "actual angle of motor 2: %f",
                msg->data[1]);
    RCLCPP_INFO(this->get_logger(), "actual angle of motor 3: %f",
                msg->data[2]);
    RCLCPP_INFO(this->get_logger(), "actual angle of motor 4: %f",
                msg->data[3]);
  }

  void velocity_fuzzy_callback(
      const std_msgs::msg::Float64MultiArray::SharedPtr msg) {
    // Handle fuzzy velocity data
    RCLCPP_INFO(this->get_logger(), "Received fuzzy velocity");
    // Your logic here
  }

  rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr
      subscription_actual_angle_;
  rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr
      subscription_velocity_fuzzy_;
  rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr
      publisher_desired_angle_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<PIDNode>());
  rclcpp::shutdown();
  return 0;
}
