/**
 * @file speed_controller.h
 * @author Hien Nguyen
 * @brief Speed_controller module is used in the BamBooBot under minht57lab
 * @version 0.1
 * @date 2023-09-03
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef SPEED_CONTROLLER__H
#define SPEED_CONTROLLER__H

#include "config/config.h"

// float v; // m/s
// float w; // rad/s
typedef struct {
  float Kp = 2.0;
  float Ki = 0.0;
  float Kd = 0.0;
  float ek_1;
  float ek_2;
  float uk_1;
} PID_t;

float PID_controller(float sp, float pv, PID_t *pid);
#endif /* SPEED_CONTROLLER__H */