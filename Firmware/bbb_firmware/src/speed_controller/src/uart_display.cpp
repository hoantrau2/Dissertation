#include "uart_display/uart_display.h"

void uart_init_h() {
  uart_init(UART_ID, BAUD_RATE);
  gpio_set_function(UART_TX, GPIO_FUNC_UART);
  uart_set_format(UART_ID, DATA_BITS, STOP_BITS, PARITY);
  uart_set_fifo_enabled(UART_ID, false);
}