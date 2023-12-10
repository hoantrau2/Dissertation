#include "uart_display/uart_display.h"

void uart_init_h() {
  uart_init(UART_ID, BAUD_RATE);
  gpio_set_function(UART_TX, GPIO_FUNC_UART);
}

void uart_display(float value) {
  char buff[100];
  sprintf(buff, "%f", value);
  // uart_puts(UART_ID, "pin_control =  ");
  uart_puts(UART_ID, buff);
  uart_puts(UART_ID, "\r\n");
}