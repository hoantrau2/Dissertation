/**
 * @file buzzer.cpp
 * @author Tri PHAN
 * @brief Buzzer module is used in the BamBooBot under minht57lab
 * @version 0.1
 * @date 2023-07-06
 *
 */

#ifndef IO__BUZZER__H
#define IO__BUZZER__H

#include <stdint.h>
#include "config/config.h"
#include "pico/stdlib.h"

using namespace bbb::config;

// namespace bbb {
// namespace io {
// class Buzzer {
//  public:
//   enum State {
//     ON = 1,
//     OFF = 0,
//     FREQUENCY
//   };

//   Buzzer(const config::GPIOConfig config);
//   ~Buzzer();
//   void SetState(const State state, const uint8_t freq = 0, const uint8_t timeout_s = 0);

//  private:
// };
// }; // namespace io
// }; // namespace bbb
void buzzer_init();
void buzzer_ring();
void buzzer_off();

#endif /* IO__BUZZER__H */
