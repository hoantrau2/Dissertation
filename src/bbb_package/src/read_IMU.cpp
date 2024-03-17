#include <iostream>
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
                readSerialData();
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

    void readSerialData() {
        while (rclcpp::ok()) {
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

            RCLCPP_INFO(get_logger(), "roll: %f     pitch: %f       yaw: %f", roll, pitch, yaw);


			subdata.clear(); // Clear subdata
            
        
            }


        }
    }
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SerialNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}