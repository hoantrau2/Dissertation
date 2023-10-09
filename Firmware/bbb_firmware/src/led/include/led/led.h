/**
 * @file led.cpp
 * @author Tri PHAN
 * @brief Led module is used in the BamBooBot under minht57lab
 * @version 0.1
 * @date 2023-07-06
 *
 */
#ifndef __LED__H
#define __LED__H

#include <stdint.h>
#include "config/config.h"

namespace bbb {
namespace io {

class Led {
 public:
  enum State {
    ON = 0,
    OFF,
    FREQUENCY
  };

  Led(const config::GPIOConfig config);
  ~Led();
  void SetState(const State state, const uint8_t freq = 0, const uint8_t timeout_s = 0);
};

}; // namespace io
}; // namespace bbb

#endif /* __LED__H */
