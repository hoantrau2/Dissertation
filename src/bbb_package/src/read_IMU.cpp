/**
 * @file read_IMU.cpp
 * @author Hoan Duong
 * @brief the IMU_node of my thesis at my university, Ho Chi Minh University of
 * Technology.
 * @version 1
 * @date 2024-03-29
 */

#include "serial/serial.h"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"

class SerialNode : public rclcpp::Node {
public:
    SerialNode() : Node("IMU_node"), port_("/dev/ttyUSB0"), baud_(115200 * 2), data_size_(71) {
        try {
            serial_ = std::make_shared<serial::Serial>(port_, baud_, serial::Timeout::simpleTimeout(20));
            if (!serial_->isOpen()) {
                RCLCPP_ERROR(get_logger(), "Failed to open serial port.");
            } else {
                RCLCPP_INFO(get_logger(), "Serial port opened successfully.");
                calibrateIMU();
                publisher_angle_IMU_ = create_publisher<std_msgs::msg::Float64MultiArray>("/angle_IMU", 10);
                timer_ = create_wall_timer(std::chrono::milliseconds(100), std::bind(&SerialNode::timer_callback, this));
                RCLCPP_INFO(get_logger(), "Initialized IMU node");
            }
        } catch (const std::exception &e) {
            RCLCPP_ERROR(get_logger(), "Exception occurred while opening serial port: %s", e.what());
        }
    }

private:
    std::string port_;
    unsigned long baud_;
    size_t data_size_;
    std::shared_ptr<serial::Serial> serial_;
    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr publisher_angle_IMU_;
    rclcpp::TimerBase::SharedPtr timer_;

    void calibrateIMU() {
        uint8_t data_calib[7] = {'$', 'C', 'A', 'L', 'I', 'B', '\n'};
        serial_->write(data_calib, 7U);
        RCLCPP_INFO(get_logger(), "Calibed successfully.");
    }

    void timer_callback() {
        if (serial_->available() >= data_size_) {
            std::string data = serial_->readline(100, "\r\n");
            std::string yaw_str = data.substr(16, 7);
            double yaw = std::strtod(yaw_str.c_str(), 0) * 0.001;
            auto message = std_msgs::msg::Float64MultiArray();
            message.data.resize(1); 
            message.data[0] = yaw;
            message.layout.data_offset = 444;
            publisher_angle_IMU_->publish(message);
        }
    }
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SerialNode>());
    rclcpp::shutdown();
    return 0;
}