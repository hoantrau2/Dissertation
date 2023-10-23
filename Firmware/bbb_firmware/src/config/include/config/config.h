#ifndef CONFIG__CONFIG__H
#define CONFIG__CONFIG__H

#include "stdint.h"

namespace bbb {
namespace config {

// #define R 0.03446       // m
// #define L 0.065         // m
// #define PPR 1008        // 3*4*84 pules/round
#define PPR 1320        // 30x11x4 pules/round
#define SAMPLE_TIME 100 // ms

enum GPIOConfigState {
  Input = 0,
  Output = 1,
  Analog = 2,
};

// GPIO configuration. This type is used for Button, LED,...
typedef struct GPIOConfig {
  uint32_t pin;
  GPIOConfigState config;
} GPIOConfig;

// Encoder configuration
typedef struct EncoderConfig {
  uint32_t cha;
  uint32_t chb;
  uint32_t pules_one_round;
} EncoderConfig;

// H-Bridge configuration
typedef struct HBridgeConfig {
  uint32_t pwm_a;
  uint32_t pwm_b;
} HBridgeConfig;

// Motor configuration
typedef struct MotorConfig {
  HBridgeConfig h_bridge;
  EncoderConfig encoder;
} MotorConfig;

typedef struct VehicleConfig {
  float wheel_diameter;
  float two_wheel_dist;
} VehicleConfig;

typedef struct I2CDevice {
  uint32_t sda;
  uint32_t scl;
} I2CDevice;

// Adc configuration
typedef struct AdcConfig {
  uint32_t pin;
  uint32_t chanel;
} AdcConfig;

extern const struct MotorConfig MotorFL_1;
extern const struct MotorConfig MotorRL_2;
extern const struct MotorConfig MotorFR_3;
extern const struct MotorConfig MotorRR_4;
extern const struct VehicleConfig Bbb_parameter;
extern const struct GPIOConfig Buzzer;
extern const struct AdcConfig BatteryVoltControl;
extern const struct AdcConfig BatteryVoltMotor;

} // namespace config
} // namespace bbb

#endif /* CONFIG__CONFIG__H */