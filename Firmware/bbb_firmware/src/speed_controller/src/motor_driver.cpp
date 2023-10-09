#include "motor_driver/motor_driver.h"

void gpio_out_init(uint pin) {
  gpio_init(pin);
  gpio_set_dir(pin, GPIO_OUT);
}

void pwm_init_one_wheel(uint pin, uint slice_num) {
  // Tell PWM1_PIN it is allocated to the PWM
  gpio_set_function(pin, GPIO_FUNC_PWM);

  // Set period of 5000 cycles (0 to 3 inclusive)
  // ==> fpwm = fc/5000  = 25kHz   (fc: 125Mhz, f_typ L298N: 25kHz )
  pwm_set_wrap(slice_num, WRAP);

  // Set the PWM running
  pwm_set_enabled(slice_num, true);
}
void pwm_run(uint pin, uint slice_num, float duty) {
  pwm_set_chan_level(slice_num, pin, (WRAP + 1) * duty);
}

void pwm_init() {
  gpio_out_init(MotorFR_3.h_bridge.dir);
  gpio_out_init(MotorFR_3.h_bridge.not_dir);
  gpio_out_init(MotorFL_1.h_bridge.dir);
  gpio_out_init(MotorFL_1.h_bridge.not_dir);

  pwm_get_default_config();
  pwm_init_one_wheel(MotorFL_1.h_bridge.pwm, PWM1_SLICE);
  pwm_init_one_wheel(MotorRL_2.h_bridge.pwm, PWM2_SLICE);
  pwm_init_one_wheel(MotorFR_3.h_bridge.pwm, PWM3_SLICE);
  pwm_init_one_wheel(MotorRR_4.h_bridge.pwm, PWM4_SLICE);
}

void pwm_forward(uint direct) {
  if (direct == LEFT) {
    gpio_put(MotorFL_1.h_bridge.dir, 1);
    gpio_put(MotorFL_1.h_bridge.not_dir, 0);
  }
  if (direct == RIGHT) {
    gpio_put(MotorFR_3.h_bridge.dir, 1);
    gpio_put(MotorFR_3.h_bridge.not_dir, 0);
  }
}

void pwm_reverse(uint direct) {
  if (direct == LEFT) {
    gpio_put(MotorFL_1.h_bridge.dir, 0);
    gpio_put(MotorFL_1.h_bridge.not_dir, 1);
  }
  if (direct == RIGHT) {
    gpio_put(MotorFR_3.h_bridge.dir, 0);
    gpio_put(MotorFR_3.h_bridge.not_dir, 1);
  }
}

void pwm_stop(uint direct) {
  if (direct == LEFT) {
    gpio_put(MotorFL_1.h_bridge.dir, 0);
    gpio_put(MotorFL_1.h_bridge.not_dir, 0);
  }
  if (direct == RIGHT) {
    gpio_put(MotorFR_3.h_bridge.dir, 0);
    gpio_put(MotorFR_3.h_bridge.not_dir, 0);
  }
}

void pwm_run_m1(float duty) { pwm_run(MotorFL_1.h_bridge.pwm, PWM1_SLICE, duty); } // 0->1
void pwm_run_m2(float duty) { pwm_run(MotorRL_2.h_bridge.pwm, PWM2_SLICE, duty); }
void pwm_run_m3(float duty) { pwm_run(MotorFR_3.h_bridge.pwm, PWM3_SLICE, duty); }
void pwm_run_m4(float duty) { pwm_run(MotorRR_4.h_bridge.pwm, PWM4_SLICE, duty); }