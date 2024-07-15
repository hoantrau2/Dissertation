/**
 * @file data_processing_node_circle.cpp
 * @author Hoan Duong & Hien Nguyen
 * @brief Data processing node circle for thesis project at Ho Chi Minh University of Technology.
 * @version 1
 * @date 2024-03-29
 */

#include <cmath>
#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include "tf2_msgs/msg/tf_message.hpp"

#define SAMPLE_TIME 100
#define Kp 2.1


#define Ksoft 0

#define R  1
#define COUNTER 550


class DataProcessingNode : public rclcpp::Node {
 public:
  DataProcessingNode()
    : Node("Stanley_node"), angleIMU(0.0), actual_position({0.0, 0.0}), pre_actual_position({0.0, 0.0}), index(0), pre_index (0), d_min(0.0), arctannn(0.0) {
    initializeArrays();
    setupSubscribersAndPublishers();
    setupTimer();
    RCLCPP_INFO(get_logger(), "Data processing node circle initialized.");
  }

 private:
  double angleIMU;
  std::vector<double> actual_position;
  std::vector<double> pre_actual_position;
  int index =0;
  int pre_index;
  double d_min, arctannn;
  double x[COUNTER];
  double y[COUNTER];
  double theta[COUNTER];
  rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr subscription_angle_IMU_;
  rclcpp::Subscription<tf2_msgs::msg::TFMessage>::SharedPtr subscription_tf_;
  rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr publisher_delta_;
  rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr publisher_position_;
  rclcpp::TimerBase::SharedPtr timer_;

  void initializeArrays() {
    x[0]=0;
    y[0]=0;
    theta[0]=0;
    for(int n = 1; n < COUNTER; n++){
    y[n] = R*(1-std::cos(0.01*M_PI*n));
    x[n] = R*std::sin(0.01*M_PI*n)*std::cos(0.01*M_PI*n);
    theta[n] = atan2(y[n]-y[n-1],x[n]-x[n-1]);
    // RCLCPP_INFO(this->get_logger(), "x[%d] = %lf, y[%d] = %lf, theta[%d] = %lf", n, x[n], n, y[n], n, theta[n]*180/M_PI);
     }
  }

  void setupSubscribersAndPublishers() {
    subscription_angle_IMU_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
      "/angle_IMU", 10, std::bind(&DataProcessingNode::angle_IMU_callback, this, std::placeholders::_1));

    subscription_tf_ = this->create_subscription<tf2_msgs::msg::TFMessage>(
      "/tf", 10, std::bind(&DataProcessingNode::tf_callback, this, std::placeholders::_1));

    publisher_delta_ = this->create_publisher<std_msgs::msg::Float64MultiArray>("/delta_angle", 10);
    publisher_position_ = this->create_publisher<std_msgs::msg::Float64MultiArray>("/robot_state", 10);
  }

  void setupTimer() {
    timer_ = this->create_wall_timer(std::chrono::milliseconds(SAMPLE_TIME), std::bind(&DataProcessingNode::timer_callback, this));
  }

  void timer_callback() {
    d_min = std::sqrt(std::pow((actual_position[0] - x[int(index)]), 2) + std::pow((actual_position[1] - y[int(index)]), 2));
     if (index <= 7) {
       for (int i = index + 1; i < std::min(index + 7, COUNTER); i++) {
      double d = std::sqrt(std::pow((actual_position[0] - x[i]), 2) + std::pow((actual_position[1] - y[i]), 2));
      if (d < d_min) {
        d_min = d;
        index = i;
      }
    }
     }
     else 
     {
       for (int i = index -7; i < std::min(index + 7, COUNTER); i++) {
      double d = std::sqrt(std::pow((actual_position[0] - x[i]), 2) + std::pow((actual_position[1] - y[i]), 2));
      if (d < d_min) {
        d_min = d;
        index = i;
      }
    }
     }

   

    

    //    if ((index == pre_index && index>20) || index - pre_index > 3) index = pre_index +1;
    // pre_index = index;


    double arctann = std::atan2(Kp * d_min, Ksoft + 0.3);
    if (arctann > 15 * M_PI / 180) arctann = 15 * M_PI / 180;

    auto message = std_msgs::msg::Float64MultiArray();
    message.data.resize(2);
    if (std::atan2(actual_position[1], actual_position[0]) - theta[int(index)] > 0)
    {
      message.data[0] = theta[int(index)] - angleIMU - arctann;
      arctannn = -arctann;
      //  message.data[0] = theta[int(index)] - angleIMU;
    // message.data[0] = 45 * M_PI / 180- angleIMU - arctann;
    }
    else
    {
      message.data[0] = theta[int(index)] - angleIMU + arctann;
      arctannn =  + arctann;
      // message.data[0] = theta[int(index)] - angleIMU;
    // message.data[0] = 45 * M_PI / 180- angleIMU - arctann;
    }
    message.data[1] = 0.3;
    message.layout.data_offset = 555;
    publisher_delta_->publish(message);
  }

  void angle_IMU_callback(const std_msgs::msg::Float64MultiArray::SharedPtr msg) {
    if (msg->layout.data_offset == 444 && msg->data.size() == 1) {
      angleIMU = msg->data[0] * M_PI / 180.0; // Convert to radians
    } else {
      RCLCPP_ERROR(get_logger(), "Invalid message format or size of /angle_IMU topic");
    }
  }

   void tf_callback(const tf2_msgs::msg::TFMessage::SharedPtr msg) {
    for (auto transform : msg->transforms) {
      if (transform.child_frame_id == "base_footprint") {
        double x_position = -transform.transform.translation.x;
        double y_position = transform.transform.translation.y;
        if (std::abs(x_position - pre_actual_position[0]) >0.5 ||std::abs(y_position - pre_actual_position[1])>0.5)
        {
           actual_position[0] =  pre_actual_position[0];
           actual_position[1] =  pre_actual_position[1];
        }
        else 
        {
          actual_position[0] =  x_position;
          actual_position[1] =  y_position;
        }


        pre_actual_position[0] =  actual_position[0];
        pre_actual_position[1] =  actual_position[1];

        auto message2 = std_msgs::msg::Float64MultiArray();
        message2.data.resize(8); // Set size of data vector to 4
        message2.data[0] = actual_position[0];
        message2.data[1] = actual_position[1]; 
        message2.data[2] = x[int(index)];
        message2.data[3] = y[int(index)];
        message2.data[4] = d_min;

        if (theta[int(index)] - angleIMU <-M_PI)
        message2.data[5] = (theta[int(index)] - angleIMU ) + 2*M_PI ;
        else if (theta[int(index)] - angleIMU >M_PI)
        message2.data[5] = (theta[int(index)] - angleIMU ) - 2*M_PI ;
        else message2.data[5] = theta[int(index)] - angleIMU  ;
        message2.data[6]=index;
        message2.data[7]=theta[int(index)];
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