/**
 * @file battery.cpp
 * @author Tri PHAN
 * @brief battery module is used in the BamBooBot under minht57lab
 * @version 0.1
 * @date 2023-08-09
 *
 */

#ifndef BATTERY__H
#define BATTERY__H

#include "config/config.h"
#include "hardware/adc.h"

using namespace bbb::config;
// namespace bbb {
// namespace io {

// class Battery {
//  private:
//  public:
//   Battery(const config::GPIOConfig config);
//   ~Battery();

//   bool GetBatteryPercentage(float& value);
// };

// }; // namespace io
// }; // namespace bbb
void adc_init_h(const AdcConfig bat);
float adc_read_h();

#endif /* BATTERY__H */
