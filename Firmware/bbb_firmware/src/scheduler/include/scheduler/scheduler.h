/**
 * @file buzzer.cpp
 * @author Tri PHAN
 * @brief Buzzer module is used in the BamBooBot under minht57lab
 * @version 0.1
 * @date 2023-07-06
 *
 */

#ifndef IO__SCHEDULER__H
#define IO__SCHEDULER__H

#include <stdint.h>
#include "config/config.h"

namespace bbb {
namespace io {
class Buzzer {
 public:
  enum State {
    ON = 0,
    OFF,
    FREQUENCY
  };

  Buzzer(const config::GPIOConfig config);
  ~Buzzer();
  void SetState(const State state, const uint8_t freq = 0, const uint8_t timeout_s = 0);

 private:
};
}; // namespace io
}; // namespace bbb

#endif /* IO__SCHEDULER__H */
