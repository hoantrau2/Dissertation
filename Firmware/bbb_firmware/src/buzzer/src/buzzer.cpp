#include "buzzer/buzzer.h"

namespace bbb {
namespace io {

Buzzer::Buzzer(const config::GPIOConfig config) {
}

Buzzer::~Buzzer() {
}

void Buzzer::SetState(const State state, const uint8_t freq, const uint8_t timeout_s) {
}

} // namespace io
} // namespace bbb
