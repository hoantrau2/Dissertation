// "" This module was completed ""//
/**
 * @file read_IMU.cpp
 * @author Hoan Duong & Hien Nguyen
 * @brief the IMU node of my thesis at my university, Ho Chi Minh University of Technology.
 * @version 1
 * @date 2024-03-29
 */

#include "serial/serial.h"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include <math.h>
#define SAMPLE_TIME 10

int counter = 0;
double init_yaw = 0;
class SerialNode : public rclcpp::Node {
public:
    SerialNode() : Node("IMU_node"), port_("/dev/ttyUSB0"), baud_(115200 * 2), data_size_(71) {
        try {
            serial_ = std::make_shared<serial::Serial>(port_, baud_, serial::Timeout::simpleTimeout(20));
            if (!serial_->isOpen()) {
                RCLCPP_ERROR(get_logger(), "Failed to open serial port.");
            } else {
                RCLCPP_INFO(get_logger(), "Serial port opened successfully.");
                
                // resetIMU();
                // no_mag_IMU();
                calibrateIMU();
                publisher_angle_IMU_ = create_publisher<std_msgs::msg::Float64MultiArray>("/angle_IMU", 10);
              
                timer_ = create_wall_timer(std::chrono::milliseconds(SAMPLE_TIME), std::bind(&SerialNode::timer_callback, this));
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
    void resetIMU() {
        uint8_t data_reset[7] = {'$', 'R', 'E', 'S', 'E', 'T', '\n'};
        serial_->write(data_reset, 7U);
        RCLCPP_INFO(get_logger(), "Reset successfully.");
    }
    void no_mag_IMU() {
        uint8_t data_mag_1[9] = {'$', 'A', 'L', 'P', 'H', 'A', ' ','1', '\n'};
        serial_->write(data_mag_1, 9U);
        RCLCPP_INFO(get_logger(), "config no mag");

        uint8_t data_mag_2[9] = {'$', 'A', 'L', 'P', 'H', 'T', ' ','1', '\n'};
        serial_->write(data_mag_2, 9U);
        RCLCPP_INFO(get_logger(), "config no mag successfully");
    }

    // double deg2rad (double x){
    //     double y;
    //     y = x*PI/180;
    //     return y;
    // }
    // double rad2deg (double x){
    //     double y;
    //     y = x*180/PI;
    //     return y;
    // }
    // void transformation(double init_yaw,double *new_yaw){
    //     init_yaw = deg2rad(init_yaw);
    //     *new_yaw = deg2rad(*new_yaw);
    //     *new_yaw = acos(cos(init_yaw)*cos(*new_yaw)+sin(init_yaw)*sin(*new_yaw));
    //     *new_yaw = rad2deg(*new_yaw);
    // }

    void timer_callback() {
        if (serial_->available() >= data_size_) {
            std::string data = serial_->readline(100, "\r\n");

            // Extracting yaw substring (starting at index 16, length 7)
            std::string yaw_str;
            double yaw ;
            if (data.size() >= 16 + 7) {
                yaw_str = data.substr(16, 7);
                yaw = std::strtod(yaw_str.c_str(), nullptr) * 0.001;
            } else {RCLCPP_ERROR(this->get_logger(), "yaw error ");}
            
            // std::string yaw_str = data.substr(16, 7);
            // double yaw = std::strtod(yaw_str.c_str(), 0) * 0.001;

            // std::string roll_str = data.substr(0, 7);
            // double roll = std::strtod(roll_str.c_str(), 0) * 0.001;

            // std::string pitch_str = data.substr(8, 7);
            // double pitch = std::strtod(pitch_str.c_str(), 0) * 0.001;

            // transformation frame

            counter ++;
            if (10<counter && counter<21){
                init_yaw = init_yaw + yaw;
                RCLCPP_INFO(this->get_logger(), "init_yaw_0 = %lf ", init_yaw);
            }else if (counter == 21){
                init_yaw = init_yaw/10;
                RCLCPP_INFO(this->get_logger(), "init_yaw_1 = %lf ", init_yaw);
            } else {
                // RCLCPP_INFO(this->get_logger(), "init_yaw_2 = %lf ", init_yaw);
                // transformation(init_yaw, &yaw);
                // RCLCPP_INFO(this->get_logger(), "%lf ", yaw);
                yaw = yaw - init_yaw;
                if (yaw < 0){
                    yaw = yaw + 360;
                }
                auto message = std_msgs::msg::Float64MultiArray();
                message.data.resize(1); 
                message.data[0] = yaw;
                message.layout.data_offset = 444;
                // RCLCPP_INFO(this->get_logger(), "yaw = %lf   roll = %lf    pitch = %lf", yaw, roll, pitch);
                 RCLCPP_INFO(this->get_logger(), "yaw = %lf ", yaw);
                publisher_angle_IMU_->publish(message);
            }
        }
    }
};

int main(int argc, char *argv[]) {
   
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SerialNode>());
    rclcpp::shutdown();
    return 0;
}