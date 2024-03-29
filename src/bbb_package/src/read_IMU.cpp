/**
 * @file read_IMU.cpp
 * @author Hoan Duong & Hien Nguyen
 * @brief the IMU_node of my thesis at my university, Ho Chi Minh University of
 * Technology.
 * @version 1
 * @date 2024-03-29
 */

#include "serial/serial.h"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include <chrono>
#include <functional>
#include <memory>
#include <string>

class SerialNode : public rclcpp::Node {
public:
    SerialNode() : Node("IMU_node"), port_("/dev/ttyUSB0"), baud_(115200 * 2), data_size_(71) {
        try {
            serial_ = std::make_shared<serial::Serial>(port_, baud_, serial::Timeout::simpleTimeout(20));
            if (!serial_->isOpen()) {
                RCLCPP_ERROR(get_logger(), "Failed to open serial port.");
            } else {
                RCLCPP_INFO(get_logger(), "Serial port opened successfully.");
                // reset IMU
                // uint8_t data_reset[7];
                // data_reset[0] = '$';
                // data_reset[1] = 'R';
                // data_reset[2] = 'E';
                // data_reset[3] = 'S';
                // data_reset[4] = 'E';
                // data_reset[5] = 'T';
                // data_reset[6] = '\n';
                // serial_->write(data_reset,7U);
                // RCLCPP_INFO(get_logger(), "Reseted successfully.");
                // calib IMU
                uint8_t data_calib[7];
                data_calib[0] = '$';
                data_calib[1] = 'C';
                data_calib[2] = 'A';
                data_calib[3] = 'L';
                data_calib[4] = 'I';
                data_calib[5] = 'B';
                data_calib[6] = '\n';
                serial_->write(data_calib,7U);
                RCLCPP_INFO(get_logger(), "Calibed successfully.");
                // read data from IMU
                
                        publisher_angle_IMU_ =
        this->create_publisher<std_msgs::msg::Float64MultiArray>(
            "/angle_IMU", 10);
        timer_ = this->create_wall_timer(
        std::chrono::milliseconds(500), std::bind(&SerialNode::timer_callback,
                         this)); // use create_wall_timer to timer 500ms
         RCLCPP_INFO(get_logger(), "Initialize IMU node");
        //  readSerialData();
         RCLCPP_INFO(get_logger(), "start readSerialData");
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
    std::string data;
    std::vector<std::string> subdata;
    double roll, pitch, yaw, pre_yaw;

    // void readSerialData() {
    //     while (rclcpp::ok()) {
    //         // if (serial_->available() >= data_size_) {
    //         //     data = serial_->readline(100, "\r\n");
    //         // /********** Data Format ****************/
	// 		// /* |0x0A   roll   pitch   yaw    wx     wy     wz     ax     ay     az    0x0D| */
	// 		// /* |1byte 7bytes 7bytes 7bytes 7bytes 7bytes 7bytes 6bytes 6bytes 6bytes 1byte| */
	// 		// // NOTE: data  is not contain "Start Byte"-0x0A
	// 		// // Get string of roll, pitch, yaw
	// 		// std::string roll_str = data.substr(0,7); // roll_string is start at index 0, size = 7 bytes
	// 		// subdata.push_back(roll_str); 
	// 		// std::string pitch_str = data.substr(8,7); // roll_string is start at index 8, size = 7 bytes 
	// 		// subdata.push_back(pitch_str);
	// 		// std::string yaw_str = data.substr(16,7); // roll_string is start at index 16, size = 7 bytes
	// 		// subdata.push_back(yaw_str); 
			
	// 		// roll = (std::strtod(subdata[0].c_str(),0))*0.001;
	// 		// pitch = (std::strtod(subdata[1].c_str(),0))*0.001;
	// 		// yaw = (std::strtod(subdata[2].c_str(),0))*0.001;

    //         // //  RCLCPP_INFO(get_logger(), "roll: %f     pitch: %f       yaw: %f", roll, pitch, yaw);
             
	// 		// subdata.clear(); // Clear subdata
    //         // }
    //     }
    // }
      void timer_callback() {
                if (serial_->available() >= data_size_) {
                data = serial_->readline(100, "\r\n");
            /********** Data Format ****************/
			/* |0x0A   roll   pitch   yaw    wx     wy     wz     ax     ay     az    0x0D| */
			/* |1byte 7bytes 7bytes 7bytes 7bytes 7bytes 7bytes 6bytes 6bytes 6bytes 1byte| */
			// NOTE: data  is not contain "Start Byte"-0x0A
			// Get string of roll, pitch, yaw
			std::string roll_str = data.substr(0,7); // roll_string is start at index 0, size = 7 bytes
			subdata.push_back(roll_str); 
			std::string pitch_str = data.substr(8,7); // roll_string is start at index 8, size = 7 bytes 
			subdata.push_back(pitch_str);
			std::string yaw_str = data.substr(16,7); // roll_string is start at index 16, size = 7 bytes
			subdata.push_back(yaw_str); 
			
			roll = (std::strtod(subdata[0].c_str(),0))*0.001;
			pitch = (std::strtod(subdata[1].c_str(),0))*0.001;
			yaw = (std::strtod(subdata[2].c_str(),0))*0.001;

            //  RCLCPP_INFO(get_logger(), "roll: %f     pitch: %f       yaw: %f", roll, pitch, yaw);
                     auto message = std_msgs::msg::Float64MultiArray();
             message.data.resize(1); // Set size of data vector to 4
              message.data[0] = yaw;
             message.layout.data_offset = 333;
             publisher_angle_IMU_->publish(message);
			subdata.clear(); // Clear subdata
            }


  }
      rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr
      publisher_angle_IMU_;
      rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SerialNode>());
    rclcpp::shutdown();
    return 0;
}