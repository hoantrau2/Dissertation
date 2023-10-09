#include "battery/battery.h"

namespace bbb {
namespace io {

Battery::Battery(const config::GPIOConfig config) {
}

Battery::~Battery() {
}

bool Battery::GetBatteryPercentage(float& value) {
  value = 100.0f;
  return true;
}

} // namespace io
} // namespace bbb
