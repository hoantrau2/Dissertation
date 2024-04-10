// "" This module has been provisionally completed ""
/**
 * @file fuzzy_longitudinal_controllers.cpp
 * @author Hoan Duong & Hien Nguyen
 * @brief the controller node of my thesis at my university, Ho Chi Minh University of Technology.
 * @version 1
 * @date 2024-04-04
 */

#include <algorithm>
#include <chrono>
#include <cmath>
#include <functional>
#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"

#define SAMPLE_TIME 100
#define VMAX 1.0
#define DELTAMAX 100 * 3.14 / 180

struct Error {
  double NB, NS, ZE, PS, PB;
};

struct Error_dot {
  double NE, ZE, PO;
};

struct U_dot {
  double NB, NM, NS, ZE, PS, PM, PB;
};

//  Structure for PI Fuzzy Controller Parameters
struct PI_FUZZY_t {
  double Ke;
  double Ke_dot;
  double Ku;
  double uk_1;
  double ek_1;
  double ek_2;
};

PI_FUZZY_t pi_fuzzy; // global variable

static double mfTriang(double x, double a, double b, double c);
static double mfTrap(double x, double a, double b, double c, double d);
double run_fuzzy(double x1, double x2);
void limit_range(double *x);
void init_PI_fuzzy();
double PI_fuzzy(double sp, double pv);

using namespace std::chrono_literals;
// Fuzzy Node Class
class FuzzyLongitudinalControllersNode : public rclcpp::Node {
 public:
  FuzzyLongitudinalControllersNode() : Node("controller_node"), deltaAngle(0.0) {
    // Subscription to Delta Angle Topic
    subscription_delta_angle_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
      "/delta_angle", 10, std::bind(&FuzzyLongitudinalControllersNode::delta_angle_callback, this, std::placeholders::_1));

    // Publisher for desired velocities
    publisher_desired_velocities_ = this->create_publisher<std_msgs::msg::Float64MultiArray>(
      "/desired_velocities", 10);

    // Timer for Periodic Execution
    timer_ = this->create_wall_timer(std::chrono::milliseconds(SAMPLE_TIME), std::bind(&FuzzyLongitudinalControllersNode::timer_callback, this));
  }

 private:
  void timer_callback() {
    double linearVelovity;
    double omega = PI_fuzzy(deltaAngle, 0.0);
    if (abs(deltaAngle) >= DELTAMAX)
      linearVelovity = 0.0;
    else
      linearVelovity = VMAX * (1 - deltaAngle / DELTAMAX);
    // publish message with desired velocity
    auto message = std_msgs::msg::Float64MultiArray();
    message.data.resize(2); // Set size of data vector to 4
    message.data[0] = omega;
    message.data[1] = linearVelovity;
    // push values to debug
    RCLCPP_INFO(this->get_logger(), "omega = %lf linear velocity = %lf", message.data[0], message.data[1]);
    RCLCPP_INFO(this->get_logger(), "pi_fuzzy = %lf  %lf  %lf  %lf  %lf  %lf", pi_fuzzy.Ke, pi_fuzzy.Ke_dot, pi_fuzzy.Ku, pi_fuzzy.uk_1, pi_fuzzy.ek_1, pi_fuzzy.ek_2);
    message.layout.data_offset = 333;
    publisher_desired_velocities_->publish(message);
  }

  void
  delta_angle_callback(const std_msgs::msg::Float64MultiArray::SharedPtr msg) {
    // Handle delta angle
    if (msg->layout.data_offset == 555 && msg->data.size() == 1) {
      deltaAngle = msg->data[0]; //radian
      // push values to debug
       RCLCPP_INFO(this->get_logger(), "Received angle of stanley = %lf", msg->data[0]);
    } else {
      RCLCPP_ERROR(this->get_logger(), "Invalid message format or size of /delta_angle topic");
    }
  }

  double deltaAngle;
  rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr subscription_delta_angle_;
  rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr publisher_desired_velocities_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[]) {
  init_PI_fuzzy();
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<FuzzyLongitudinalControllersNode>());
  rclcpp::shutdown();
  return 0;
}

static double mfTriang(double x, double a, double b, double c) {
  double out;

  if (x < a) {
    out = 0;
  } else if ((x >= a) && (x <= b)) {
    out = (x - a) / (b - a);
  } else if ((x >= b) && (x <= c)) {
    out = (c - x) / (c - b);
  } else {
    out = 0;
  }

  return out;
}

static double mfTrap(double x, double a, double b, double c, double d) {
  double out;

  if (x < a) {
    out = 0;
  } else if ((x >= a) && (x <= b)) {
    if (a == b) {
      out = 1;
    } else {
      out = (x - a) / (b - a);
    }
  } else if ((x >= b) && (x <= c)) {
    out = 1;
  } else if ((x >= c) && (x <= d)) {
    if (c == d) {
      out = 1;
    } else {
      out = (d - x) / (d - c);
    }
  } else {
    out = 0;
  }

  return out;
}

double run_fuzzy(double x1, double x2) {
  double out;
  double r[15]; // 15 value beta <=> 15 rule
  Error e;
  Error_dot e_dot;
  U_dot u_dot;

  // calculate anpha 1 (0->1)
  e.NB = mfTrap(x1, -2, -1, -0.22, -0.17);
  e.NS = mfTriang(x1, -0.22, -0.11, 0.001);
  e.ZE = mfTriang(x1, -0.11, 0, 0.11);
  e.PS = mfTriang(x1, 0.001, 0.11, 0.22);
  e.PB = mfTrap(x1, 0.17, 0.22, 1, 2);

  // calculate anpha 2 (0->1)
  e_dot.NE = mfTrap(x2, -2, -1, -0.22, -0.17);
  e_dot.ZE = mfTriang(x2, -0.4, 0, 0.4);
  e_dot.PO = mfTrap(x2, 0.17, 0.22, 1, 2);

  // calculate beta (0->1) base on MAX-MIN, "and" => MIN
  // e - e_dot - u_dot

  // NB-NE-NB
  r[0] = std::min(e.NB, e_dot.NE);
  // NB-ZE-NM
  r[1] = std::min(e.NB, e_dot.ZE);
  // NB-PO-NS
  r[2] = std::min(e.NB, e_dot.PO);
  // NS-NE-NM
  r[3] = std::min(e.NS, e_dot.NE);
  // NS-ZE-NS
  r[4] = std::min(e.NS, e_dot.ZE);
  // NS-PO-ZE
  r[5] = std::min(e.NS, e_dot.PO);
  // ZE-NE-NS
  r[6] = std::min(e.ZE, e_dot.NE);
  // ZE-ZE-ZE
  r[7] = std::min(e.ZE, e_dot.ZE);
  // ZE-PO-PS
  r[8] = std::min(e.ZE, e_dot.PO);
  // PS-NE-ZE
  r[9] = std::min(e.PS, e_dot.NE);
  // PS-ZE-PS
  r[10] = std::min(e.PS, e_dot.ZE);
  // PS-PO-PM
  r[11] = std::min(e.PS, e_dot.PO);
  // PB-NE-PS
  r[12] = std::min(e.PB, e_dot.NE);
  // PB-ZE-PM
  r[13] = std::min(e.PB, e_dot.ZE);
  // PB-PO-PB
  r[14] = std::min(e.PB, e_dot.PO);

  // Sugeno fuzzy system
  u_dot.NB = r[0];
  u_dot.NM = std::max(r[1], r[3]);
  u_dot.NS = std::max(std::max(r[2], r[4]), r[6]);
  u_dot.ZE = std::max(std::max(r[5], r[7]), r[9]);
  u_dot.PS = std::max(std::max(r[8], r[10]), r[12]);
  u_dot.PM = std::max(r[11], r[13]);
  u_dot.PB = r[14];

  // weighted average defuzzification method
  double sum_beta;
  double sum_beta_y;
  sum_beta = u_dot.NB + u_dot.NM + u_dot.NS + u_dot.ZE + u_dot.PS + u_dot.PM + u_dot.PB;
  sum_beta_y = -0.95 * u_dot.NB + -0.8 * u_dot.NM + -0.4 * u_dot.NS + 0 * u_dot.ZE + 0.4 * u_dot.PS + 0.8 * u_dot.PM + 0.95 * u_dot.PB;
  out = sum_beta_y / sum_beta;

  return out;
}

void limit_range(double *x) {
  if (*x > 1)
    *x = 1;
  else if (*x < -1)
    *x = -1;
}

double PI_fuzzy(double sp, double pv) {
  double ek, uk, u_dot;
  double P_part, D_part;
  ek = sp - pv;
  P_part = pi_fuzzy.Ke * ek;
  limit_range(&P_part);
  D_part = pi_fuzzy.Ke_dot * (ek - pi_fuzzy.ek_2) / (SAMPLE_TIME * 1e-3);
  limit_range(&D_part);

  u_dot = run_fuzzy(P_part, D_part);
  uk = pi_fuzzy.uk_1 + u_dot * SAMPLE_TIME * 1e-3;
  pi_fuzzy.uk_1 = uk;
  pi_fuzzy.ek_2 = pi_fuzzy.ek_1;
  pi_fuzzy.ek_1 = ek;
  uk = pi_fuzzy.Ku * uk; // control delta veclocity
  return uk;
}
void init_PI_fuzzy() {
  pi_fuzzy.Ke = 5;
  pi_fuzzy.Ke_dot = 4;
  pi_fuzzy.Ku = 14.0; // 2*Vmax/Wheelbase =2*2.1/0.2469 = 17.0109356
  pi_fuzzy.uk_1 = 0;
  pi_fuzzy.ek_1 = 0;
  pi_fuzzy.ek_2 = 0;
}