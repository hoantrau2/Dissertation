/**
 * @file controllers_node.cpp
 * @author Hoan Duong & Hien Nguyen
 * @brief the controllers node of my thesis at my university, Ho Chi Minh University of Technology.
 * @version 1
 * @date 2024-03-27
 */

#include <algorithm>
#include <chrono>
#include <cmath>
#include <functional>
#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"

#define VMAX 2.0
#define K1 0.8
#define K2 3
#define SAMPLE_TIME 100
#define STEP_DISTANCE 0.2
#define VAMMXX 0.3

struct Error {
  double NB, NS, ZE, PS, PB;
};

struct Error_dot {
  double NE, ZE, PO;
};

struct U_dot {
  double NB, NM, NS, ZE, PS, PM, PB;
};

//  Structure for M_PI Fuzzy Controller Parameters
struct PD_FUZZY_t {
  double Ke;
  double Ke_dot;
  double Ku;
  double uk_1;
  double ek_1;
  double ek_2;
  double a;
  double b;
  double c;
};

PD_FUZZY_t pd_fuzzy; // global variable

static double mfTriang(double x, double a, double b, double c);
static double mfTrap(double x, double a, double b, double c, double d);
double run_fuzzy(double x1, double x2);
void limit_range(double *x);
void limit_range_0(double *x) ;
void init_PD_fuzzy();
double PD_fuzzy(double sp, double pv);
double linear_velocity(double deltaDistance, double deltaAngle);

using namespace std::chrono_literals;
// Controllers Node Class
class ControllersNode : public rclcpp::Node {
 public:
  ControllersNode() : Node("controllers_node"), deltaDistance(0.0), deltaAngle(0.0) {
    // Subscription to Delta Topic
    subscription_delta_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
      "/delta", 10, std::bind(&ControllersNode::delta_callback, this, std::placeholders::_1));

    // Publisher for desired Velocities
    publisher_desired_velocities_ = this->create_publisher<std_msgs::msg::Float64MultiArray>("/desired_velocities", 10);
    timer_ = this->create_wall_timer(std::chrono::milliseconds(SAMPLE_TIME), std::bind(&ControllersNode::timer_callback, this)); // use create_wall_timer to timer 500ms
    RCLCPP_ERROR(get_logger(), "controllers_node initialized.");
  }

 private:
  void timer_callback() {
    double output_anguler = PD_fuzzy(deltaAngle, 0);
  //  double output_velocity = linear_velocity(deltaDistance, deltaAngle);
    // push values to debug
    // RCLCPP_INFO(this->get_logger(), "input of pd_fuzzy = %lf  %lf", deltaAngle, angleIMU);
    // RCLCPP_INFO(this->get_logger(), "pd_fuzzy = %lf  %lf  %lf  %lf  %lf  %lf", pd_fuzzy.Ke, pd_fuzzy.Ke_dot, pd_fuzzy.Ku, pd_fuzzy.uk_1, pd_fuzzy.ek_1, pd_fuzzy.ek_2);
    // publish message with desired velocity
    auto message = std_msgs::msg::Float64MultiArray();
    message.data.resize(2);            // Set size of data vector to 2
    message.data[0] = output_anguler;  // rad/2
    message.data[1] = VAMMXX; // m/s
    // RCLCPP_INFO(this->get_logger(), "omega = %lf velocity  = %lf", message.data[0], message.data[1]);
    message.layout.data_offset = 333;
    publisher_desired_velocities_->publish(message);
  }

  void delta_callback(const std_msgs::msg::Float64MultiArray::SharedPtr msg) {
    if (msg->layout.data_offset == 555 && msg->data.size() == 2) {
      deltaAngle = msg->data[0];    // radian
      deltaDistance = msg->data[1]; // meters
      // RCLCPP_INFO(this->get_logger(), "Received angle of stanley = %lf", msg->data[0]);
    } else {
      RCLCPP_ERROR(this->get_logger(), "Invalid message format or size");
    }
  }
  double deltaDistance;
  double deltaAngle;
  rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr subscription_delta_;
  rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr publisher_desired_velocities_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[]) {
  init_PD_fuzzy();
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ControllersNode>());
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
  sum_beta_y = -pd_fuzzy.c * u_dot.NB + -pd_fuzzy.b * u_dot.NM + -pd_fuzzy.a * u_dot.NS + 0 * u_dot.ZE + pd_fuzzy.a * u_dot.PS + pd_fuzzy.b * u_dot.PM + pd_fuzzy.c * u_dot.PB;
  out = sum_beta_y / sum_beta;

  return out;
}

void limit_range(double *x) {
  if (*x > 1)
    *x = 1;
  else if (*x < -1)
    *x = -1;
}

void limit_range_0(double *x) {
  if (*x > 1)
    *x = 1;
  else if (*x < 0)
    *x = 0;
}

double PD_fuzzy(double sp, double pv) {
  double ek, uk;
  double P_part, D_part;
  ek = sp - pv;

  if (ek < -M_PI) {
    ek = ek + 2 * M_PI;
  }
  if (ek > M_PI) {
    ek = ek - 2 * M_PI;
  }
  P_part = pd_fuzzy.Ke * ek;
  limit_range(&P_part);

  D_part = pd_fuzzy.Ke_dot * (ek - pd_fuzzy.ek_2) / (SAMPLE_TIME * 1e-3);
  limit_range(&D_part);

  uk = run_fuzzy(P_part, D_part);
  // uk = pd_fuzzy.uk_1 + u_dot * SAMPLE_TIME * 1e-3;

  limit_range(&uk);
  pd_fuzzy.uk_1 = uk;
  pd_fuzzy.ek_2 = pd_fuzzy.ek_1;
  pd_fuzzy.ek_1 = ek;
  uk = pd_fuzzy.Ku * uk; // control delta veclocity
  return uk;
}
void init_PD_fuzzy() {
  pd_fuzzy.Ke = 0.159;
  pd_fuzzy.Ke_dot = 3.123;
  pd_fuzzy.Ku = 11.0; // 2*Vmax/Wheelbase =2*2.1/0.2469 = 17.0109356
  pd_fuzzy.uk_1 = 0;
  pd_fuzzy.ek_1 = 0;
  pd_fuzzy.ek_2 = 0;
  pd_fuzzy.a = 0.15;
  pd_fuzzy.b = 0.5;
  pd_fuzzy.c = 0.7;
}

double linear_velocity(double deltaDistance, double deltaAngle) {
  double deltaDistance_normal = deltaDistance / STEP_DISTANCE;
  limit_range_0(&deltaDistance_normal);
  double deltaAngle_normal = deltaAngle / M_PI;
  limit_range_0(&deltaAngle_normal);
  double delta_velocity = (-2 * deltaAngle_normal + 1) + ((K1 + 1) * deltaDistance_normal - 1);
  return ((VMAX / K2) * (delta_velocity + 1));
}