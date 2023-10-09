#include "display/display.h"

namespace bbb {
namespace display {

OLED::OLED(const config::I2CDevice config) {
  updated = false;
  Init(config);
  updated = true;
}

OLED::~OLED() {
}

void OLED::Init(const config::I2CDevice config) {
}

bool OLED::SetScreen(const Screen screen) {
  curr_screen_ = screen;
  return true;
}

// Note: The value that needs to update should be stored in a(n) queue/array and updated in the ProcessLoop method
bool OLED::UpdateValue(const ObjectID id, float value) {
  updated = false;
  return false;
}

// Note: Since I2C communication can be hung, the main loop may be stuck. Therefore, each method should have a timeout to prevent this scenario.
void OLED::ProcessLoop() {
  if (!updated) {
  }
}

} // namespace display
} // namespace bbb
