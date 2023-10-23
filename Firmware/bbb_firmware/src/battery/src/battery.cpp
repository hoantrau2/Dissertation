#include "battery/battery.h"

// namespace bbb {
// namespace io {

// Battery::Battery(const config::GPIOConfig config) {
// }

// Battery::~Battery() {
// }

// bool Battery::GetBatteryPercentage(float& value) {
//   value = 100.0f;
//   return true;
// }

// } // namespace io
// } // namespace bbb

void adc_init_h(const AdcConfig bat) {
  // stdio_init_all();
  adc_init();
  adc_gpio_init(bat.pin);
  adc_select_input(bat.chanel);
}

float adc_read_h() {
  // 12-bit conversion, assume max value == ADC_VREF == 3.27 V
  const float conversion_factor = 3.27f / (4096);
  uint16_t result = adc_read();
  return (result * conversion_factor);
}
