/**
 * @file motor_driver.h
 * @author Hien Nguyen
 * @brief Motor_driver module is used in the BamBooBot under minht57lab
 * @version 0.1
 * @date 2023-09-03
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef MOTOR_DRIVER__H
#define MOTOR_DRIVER__H

#include "config/config.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"

using namespace bbb::config;

#define WRAP 4999 // fpwm = fc/5000 (fc 125Mhz) = 25kHz
#define LEFT 0
#define RIGHT 1

// Find out which PWM slice is connected to PWMx_PIN
const uint PWM1_SLICE = pwm_gpio_to_slice_num(MotorFL_1.h_bridge.pwm);
const uint PWM2_SLICE = pwm_gpio_to_slice_num(MotorRL_2.h_bridge.pwm);
const uint PWM3_SLICE = pwm_gpio_to_slice_num(MotorFR_3.h_bridge.pwm);
const uint PWM4_SLICE = pwm_gpio_to_slice_num(MotorRR_4.h_bridge.pwm);

void gpio_out_init(uint pin);
void pwm_init_one_wheel(uint pin, uint slice_num);
void pwm_run(uint pin, uint slice_num, float duty);
void pwm_init();
void pwm_forward(uint direct);
void pwm_reverse(uint direct);
void pwm_stop(uint direct);
void pwm_run_m1(float duty);
void pwm_run_m2(float duty);
void pwm_run_m3(float duty);
void pwm_run_m4(float duty);

#endif /* MOTOR_DRIVER__H */
