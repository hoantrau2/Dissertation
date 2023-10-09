#include "state_machine/state_machine.h"

namespace bbb {
namespace io {

State::State(const config::GPIOConfig config) {
}

State::~State() {
}

void State::SetState(const State state, const uint8_t freq, const uint8_t timeout_s) {
}

} // namespace io
} // namespace bbb