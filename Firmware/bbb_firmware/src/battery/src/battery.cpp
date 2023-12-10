#include "battery/battery.h"

void adc_read_h(void *cxt) {
  Event_battery_t *bat_t = (Event_battery_t *)cxt;
  adc_init();
  adc_gpio_init(bat_t->config_bat.pin);
  adc_select_input(bat_t->config_bat.chanel);
  // 12-bit conversion, assume max value == ADC_VREF == 3.27 V
  const float conversion_factor = V_REF / (4096);
  bat_t->v_bat = adc_read();
  bat_t->v_bat = bat_t->v_bat * conversion_factor * GAIN + V_ZENNER;
  // uart_display(bat_t->v_bat);
}
