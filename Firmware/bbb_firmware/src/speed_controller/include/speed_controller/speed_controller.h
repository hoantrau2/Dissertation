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

#define UK_MAX 0.7
#define KP_1 0.7
#define KI_1 0.7
#define KD_1 0.00
#define KP_2 0.7
#define KI_2 0.7
#define KD_2 0.00
#define KP_3 0.7
#define KI_3 0.7
#define KD_3 0.00
#define KP_4 0.7
#define KI_4 0.7
#define KD_4 0.00

// float v; // m/s
// float w; // rad/s
typedef struct {
  float Kp;
  float Ki;
  float Kd;
  float ek_1;
  float ek_2;
  float uk_1;
} PID_t;

float PID_controller(float sp, float pv, PID_t *pid);
void init_pid(PID_t *pid, float kp, float ki, float kd);
#endif /* SPEED_CONTROLLER__H */