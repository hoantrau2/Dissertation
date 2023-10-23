/**
 * @file velocity_convertor.h
 * @author Hien Nguyen
 * @brief Velocity_convertor module is used in the BamBooBot under minht57lab
 * @version 0.1
 * @date 2023-09-03
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef VELOCCITY__H
#define VELOCCITY__H

#include <stdlib.h>
#include "encoder/encoder.h"
#include "motor_driver/motor_driver.h"
#include "speed_controller/speed_controller.h"
#include "uart_display/uart_display.h"

#define V_MAX 0.5  // m/s
#define V_MIN 0.01 // m/s
#define sgn(x) ((x) < 0 ? -1 : 1)
#define MOTOR_1 1
#define MOTOR_2 2
#define MOTOR_3 3
#define MOTOR_4 4

void control_motor(float v, float w);

#endif /*VELOCCITY__H*/