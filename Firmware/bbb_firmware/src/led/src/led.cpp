#include "led/led.h"

namespace bbb {
namespace io {

Led::Led(const config::GPIOConfig config) {
}

Led::~Led() {
}

void Led::SetState(const State state, const uint8_t freq, const uint8_t timeout_s) {
}

} // namespace io
} // namespace bbb
