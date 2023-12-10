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
#include "uart_display/uart_display.h"

using namespace bbb::config;

#define V_REF 3.27
#define V_ZENNER 11.8
#define GAIN 2

typedef struct {
  AdcConfig config_bat;
  float v_bat;
} Event_battery_t;

void adc_read_h(void *cxt);

#endif /* BATTERY__H */
