#ifndef DISPLAY__OLED__H
#define DISPLAY__OLED__H

#include <stdint.h>
#include "config/config.h"

namespace bbb {
namespace display {

enum Screen {
  STARTUP = 0,
  TESTING,
  RUN,
  SHUTDOWN,
  FAIL
};

enum ObjectID {
  BATTERY,
  VEH_STATE,
  OR_ROLL,
  OR_PITCH,
  OR_YAW,
};

class OLED {
 private:
  void Init(const config::I2CDevice config);

  Screen curr_screen_;
  bool updated;

 public:
  OLED(const config::I2CDevice config);
  ~OLED();

  // Note that this method should be called in loop
  void ProcessLoop();

  bool SetScreen(const Screen screen);
  bool UpdateValue(const ObjectID id, float value);
};

}; // namespace display
}; // namespace bbb

#endif /* DISPLAY__OLED__H */
