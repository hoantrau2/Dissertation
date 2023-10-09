#include "config/config.h"

namespace bbb {
namespace config {

const struct MotorConfig MotorFL_1 = {
  .h_bridge = {.pwm = 9, .dir = 6, .not_dir = 8},
  .encoder = {.cha = 16, .chb = 17},
};

const struct MotorConfig MotorFR_3 = {
  .h_bridge = {.pwm = 11, .dir = 4, .not_dir = 5},
  .encoder = {.cha = 14, .chb = 15},
};

const struct MotorConfig MotorRL_2 = {
  .h_bridge = {.pwm = 7, .dir = 6, .not_dir = 8},
  .encoder = {.cha = 18, .chb = 19},
};

const struct MotorConfig MotorRR_4 = {
  .h_bridge = {.pwm = 3, .dir = 4, .not_dir = 5},
  .encoder = {.cha = 12, .chb = 13},
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

const struct GPIOConfig BatteryVolt = {
  .pin = 23,
  .config = GPIOConfigState::Analog,
};

} // namespace config
} // namespace bbb
