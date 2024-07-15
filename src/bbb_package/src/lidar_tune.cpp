
#include <cmath>
#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include "tf2_msgs/msg/tf_message.hpp"


class DataProcessingNode : public rclcpp::Node {
 public:
  DataProcessingNode()
    : Node("lidar_tune_node"), actual_position({0.0, 0.0}){
    setupSubscribersAndPublishers();
    RCLCPP_INFO(get_logger(), "Data processing node straight initialized.");
  }

 private:
  std::vector<double> actual_position;
  rclcpp::Subscription<tf2_msgs::msg::TFMessage>::SharedPtr subscription_tf_;
  rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr publisher_position_;

  void setupSubscribersAndPublishers() {
    subscription_tf_ = this->create_subscription<tf2_msgs::msg::TFMessage>(
      "/tf", 10, std::bind(&DataProcessingNode::tf_callback, this, std::placeholders::_1));

    publisher_position_ = this->create_publisher<std_msgs::msg::Float64MultiArray>("/position", 10);
  }

  void tf_callback(const tf2_msgs::msg::TFMessage::SharedPtr msg) {
    for (auto transform : msg->transforms) {
      if (transform.child_frame_id == "base_footprint") {
         actual_position[0]= -transform.transform.translation.x;
         actual_position[1] = transform.transform.translation.y;
          auto message2 = std_msgs::msg::Float64MultiArray();
         message2.data.resize(2);
         message2.data[0] = actual_position[0];
         message2.data[1] = actual_position[1];
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