#include "buzzer/buzzer.h"

// namespace bbb {
// namespace io {

// Buzzer::Buzzer(const config::GPIOConfig config) {
// }

// Buzzer::~Buzzer() {
// }

// void Buzzer::SetState(const State state, const uint8_t freq, const uint8_t timeout_s) {
// }

// } // namespace io
// } // namespace bbb

void buzzer_init() {
  gpio_init(Buzzer.pin);
  gpio_set_dir(Buzzer.pin, Buzzer.config);
}

void buzzer_ring() {
  gpio_put(Buzzer.pin, 1);
}

void buzzer_off() {
  gpio_put(Buzzer.pin, 0);
}
