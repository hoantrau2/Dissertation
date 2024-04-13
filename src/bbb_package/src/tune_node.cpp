#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include <fstream>

class TuneNode : public rclcpp::Node
{
public:
    TuneNode() : Node("tune_node")
    {
        subscription_fuzzy_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
            "/desired_velocities", 10, std::bind(&TuneNode::fuzzy_callback, this, std::placeholders::_1));

        // Open a file to log data
        log_file_fuzzy_.open("data_fuzzy.txt", std::ofstream::out | std::ofstream::app);
    }

private:
       void fuzzy_callback (const std_msgs::msg::Float64MultiArray::SharedPtr msg) 
    {
        if (msg->layout.data_offset == 333 && msg->data.size() == 6) {
            for (const auto& data : msg->data) {
                log_file_fuzzy_ << data << " ";
            }
            log_file_fuzzy_ << std::endl;
        }
    }
    rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr subscription_fuzzy_;
    std::ofstream log_file_fuzzy_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TuneNode>());
    rclcpp::shutdown();
    return 0;
}
