#include "rclcpp/rclcpp.hpp"
#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <std_msgs/msg/float64.h> 
#include "tf2_msgs/msg/tf_message.hpp"
#include <cmath>


using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node {
public:
  MinimalSubscriber() : Node("sub_pub_lidar") {
    subscription_ = this->create_subscription<tf2_msgs::msg::TFMessage>(
        "/tf", 10,
        std::bind(&MinimalSubscriber::topic_callback, this, _1));
  }

private:
void topic_callback(const tf2_msgs::msg::TFMessage::SharedPtr msg) const {
    for (const auto& transform : msg->transforms) {
        // RCLCPP_INFO(this->get_logger(), "pos_x: %lf", transform.transform.translation.x);
        // RCLCPP_INFO(this->get_logger(), "pos_y: %lf", transform.transform.translation.y);
        // RCLCPP_INFO(this->get_logger(), "pos_z: %lf", transform.transform.translation.z);
        RCLCPP_INFO(this->get_logger(), "angular_z: %lf", transform.transform.rotation.z*180/M_PI);
        // RCLCPP_INFO(this->get_logger(), "angular_w: %lf", transform.transform.rotation.w);
    }
}
  rclcpp::Subscription<tf2_msgs::msg::TFMessage>::SharedPtr subscription_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}