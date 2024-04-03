#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include <fstream>

class TuneNode : public rclcpp::Node
{
public:
    TuneNode() : Node("tune_node")
    {
        subscription_tune_node_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
            "/actual_angle", 10, std::bind(&TuneNode::tune_node_callback, this, std::placeholders::_1));

        // Open a file to log data
        log_file_.open("data_v1.txt", std::ofstream::out | std::ofstream::app);
    }

private:
    void tune_node_callback(const std_msgs::msg::Float64MultiArray::SharedPtr msg) 
    {
        if (msg->layout.data_offset == 222 && msg->data.size() == 4) {
            for (const auto& data : msg->data) {
                log_file_ << data << " ";
            }
            log_file_ << std::endl;
        }
    }

    rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr subscription_tune_node_;
    std::ofstream log_file_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TuneNode>());
    rclcpp::shutdown();
    return 0;
}
