#ifndef CONFIG__CONFIG__H
#define CONFIG__CONFIG__H

#include "stdint.h"

namespace bbb {
namespace config {

#define R 0.03446       // m
#define L 0.065         // m
#define PPR 1008        // 3*4*84 pules/round
#define SAMPLE_TIME 100 // ms

enum GPIOConfigState {
  Input = 0,
  Output,
  Analog
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
} EncoderConfig;

// H-Bridge configuration
typedef struct HBridgeConfig {
  uint32_t pwm;
  uint32_t dir;
  uint32_t not_dir;
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

extern const struct MotorConfig MotorFL_1;
extern const struct MotorConfig MotorRL_2;
extern const struct MotorConfig MotorFR_3;
extern const struct MotorConfig MotorRR_4;

} // namespace config
} // namespace bbb

#endif /* CONFIG__CONFIG__H */