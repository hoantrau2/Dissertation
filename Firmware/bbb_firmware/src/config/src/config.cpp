#include "config/config.h"

namespace bbb {
namespace config {

const struct VehicleConfig Bbb_parameter = {
  .wheel_diameter = 0.0625,
  .two_wheel_dist = 0.2469,
};

const struct MotorConfig MotorFL_1 = {
  .h_bridge = {.pwm_a = 2, .pwm_b = 3},
  .encoder = {.cha = 16, .chb = 17, .pules_one_round = PPR},
};

const struct MotorConfig MotorFR_3 = {
  .h_bridge = {.pwm_a = 6, .pwm_b = 7},
  .encoder = {.cha = 14, .chb = 15, .pules_one_round = PPR},
};

const struct MotorConfig MotorRL_2 = {
  .h_bridge = {.pwm_a = 4, .pwm_b = 5},
  .encoder = {.cha = 18, .chb = 19, .pules_one_round = PPR},
};

const struct MotorConfig MotorRR_4 = {
  .h_bridge = {.pwm_a = 8, .pwm_b = 9},
  .encoder = {.cha = 12, .chb = 13, .pules_one_round = PPR},
};

const struct I2CDevice IMU = {
  .sda = 9,
  .scl = 10,
};

const struct I2CDevice OLed = {
  .sda = 19,
  .scl = 20,
};

const struct GPIOConfig Button = {
  .pin = 21,
  .config = GPIOConfigState::Input,
};

const struct GPIOConfig Led = {
  .pin = 22,
  .config = GPIOConfigState::Output,
};

const struct GPIOConfig Buzzer = {
  .pin = 28,
  .config = GPIOConfigState::Output,
};

const struct AdcConfig BatteryVoltControl = {
  .pin = 26,
  .chanel = 0,
};

const struct AdcConfig BatteryVoltMotor = {
  .pin = 27,
  .chanel = 1,
};

} // namespace config
} // namespace bbb
