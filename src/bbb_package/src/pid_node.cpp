/**
 * @file pid_node.cpp
 * @author Hoan Duong
 * @brief the pid_node of my thesis at my university, Ho Chi Minh University of
 * Technology.
 * @version 1
 * @date 2024-03-27
 */
#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"

#define UK_MAX 0.95
#define SAMPLE_TIME 100 // in milliseconds
#define RADIUS 0.03446

using namespace std::chrono_literals;

// Complete definition of PID_t structure
typedef struct {
  double Kp;
  double Ki;
  double Kd;
  double ek_1;
  double ek_2;
  double uk_1;
} PID_t;

// Function prototypes
void init_pid(PID_t *pid, double kp, double ki, double kd);
double PID_controller(double sp, double pv, PID_t *pid);

// Define a class for controlling motors using PID controllers
class MotorController {
 public:
  MotorController() {
    // Initialize PID controllers for each motor
    for (int i = 0; i < 4; ++i) {
      PID_t pid;
      init_pid(&pid, Kp[i], Ki[i], Kd[i]);
      pid_controllers.push_back(pid);
    }
  }
  // Method to update motor speeds based on setpoints and current values
  std::vector<double> updateMotors(const std::vector<double> &setpoints, const std::vector<double> &currentValues) {
    std::vector<double> outputs;
    for (int i = 0; i < 4; ++i) {
      outputs.push_back(PID_controller(setpoints[i], currentValues[i], &pid_controllers[i]));
    }
    return outputs;
  }
 private:
  // Define PID parameters for each motor
  const double Kp[4] = {0.2, 0.2, 0.2, 0.2};
  const double Ki[4] = {0.7, 0.7, 0.7, 0.7};
  const double Kd[4] = {0.0, 0.0, 0.0, 0.0};
  // Vector to store PID controllers for each motor
  std::vector<PID_t> pid_controllers;
};
MotorController motorController; // global class variable

// Function to calculate PID control signal
double PID_controller(double sp, double pv, PID_t *pid) {
  double ek, uk; // uk: - UK_MAX->UK_MAX
  ek = sp - pv;
  uk = pid->uk_1 + pid->Kp * (ek - pid->ek_1) +
       pid->Ki * SAMPLE_TIME * 1e-3 * (ek + pid->ek_1) * 0.5 +
       pid->Kd * (ek - 2 * pid->ek_1 + pid->ek_2) / (SAMPLE_TIME * 1e-3);

  if (uk > UK_MAX)
    uk = UK_MAX;
  else if (uk < -UK_MAX)
    uk = -UK_MAX;

  pid->uk_1 = uk;
  pid->ek_2 = pid->ek_1;
  pid->ek_1 = ek;

  return uk;
}
// Function to initialize PID controller parameters
void init_pid(PID_t *pid, double kp, double ki, double kd) {
  pid->Kp = kp;
  pid->Ki = ki;
  pid->Kd = kd;
  pid->uk_1 = 0.0;
  pid->ek_1 = 0.0;
  pid->ek_2 = 0.0;
}

class PIDNode : public rclcpp::Node {
 public:
  PIDNode()
    : Node("pid_node"), currentValues({0.0, 0.0, 0.0, 0.0}), setPoints({0.0, 0.0, 0.0, 0.0}) {
    subscription_actual_angle_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
      "/actual_angle", 3, std::bind(&PIDNode::actual_angle_callback, this, std::placeholders::_1));

    subscription_velocity_fuzzy_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
      "/velocity_fuzzy", 3, std::bind(&PIDNode::velocity_fuzzy_callback, this, std::placeholders::_1));

    publisher_desired_angle_ = this->create_publisher<std_msgs::msg::Float64MultiArray>("/desired_angle", 3);

    timer_ = this->create_wall_timer(std::chrono::milliseconds(SAMPLE_TIME), std::bind(&PIDNode::timer_callback, this)); // use create_wall_timer to timer 500ms
  }

 private:
  void timer_callback() {
    std::vector<double> desiredAngles = motorController.updateMotors(setPoints, currentValues);
    // publish message with desired angles
    auto message = std_msgs::msg::Float64MultiArray();
    message.data.resize(4); // Set size of data vector to 4
    for (size_t i = 0; i < 4; ++i) {
      message.data[i] = desiredAngles[i];
    }
    RCLCPP_INFO(this->get_logger(), " motor1 = %lf   motor2 = %lf   motor3 = %lf   motor4 = %lf ", message.data[0], message.data[1], message.data[2], message.data[3]);
    message.layout.data_offset = 111;
    publisher_desired_angle_->publish(message);
  }

  void
  actual_angle_callback(const std_msgs::msg::Float64MultiArray::SharedPtr msg) {
    if (msg->layout.data_offset == 222 && msg->data.size() == 4) {
      // Handle actual angle data
      for (size_t i = 0; i < 4; ++i) {
        currentValues[i] = msg->data[i];
      }
    RCLCPP_INFO(this->get_logger(), " actual1 = %lf   actual2 = %lf   actual3 = %lf   actual4 = %lf ", currentValues[0], currentValues[1], currentValues[2], currentValues[3]);
    } 
    else {
      RCLCPP_ERROR(this->get_logger(), "Invalid message format or size");
    }
  }

  void velocity_fuzzy_callback(
    const std_msgs::msg::Float64MultiArray::SharedPtr msg) {
    // Handle fuzzy velocity data
    RCLCPP_INFO(this->get_logger(), "Received fuzzy velocity");
    if (msg->layout.data_offset == 333 && msg->data.size() == 2) {
      RCLCPP_INFO(this->get_logger(), " Received fuzzy velocity %lf   %lf ", msg->data[0], msg->data[1]);
      setPoints[0] = setPoints[1] = msg->data[0] / RADIUS; // Vlef/R
      setPoints[2] = setPoints[3] = msg->data[1] / RADIUS; // Vright/R
    } else {
      RCLCPP_ERROR(this->get_logger(), "Invalid message format or size");
    }
  }
  std::vector<double> currentValues;
  std::vector<double> setPoints;
  rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr subscription_actual_angle_;
  rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr subscription_velocity_fuzzy_;
  rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr publisher_desired_angle_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<PIDNode>());
  rclcpp::shutdown();
  return 0;
}


