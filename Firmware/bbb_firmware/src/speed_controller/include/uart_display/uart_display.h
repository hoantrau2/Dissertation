/**
 * @file uart_display.h
 * @author Hien Nguyen
 * @brief Uart_display module is used test
 * @version 0.1
 * @date 2023-09-03
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef UART_DISPLAY__H
#define UART_DISPLAY__H

// #include <stdio.h>
#include "hardware/gpio.h"
#include "hardware/uart.h"

#define UART_ID uart0
#define BAUD_RATE 115200
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY UART_PARITY_NONE
#define UART_TX 0

void uart_init_h();

#endif /*UART_DISPLAY__H*/