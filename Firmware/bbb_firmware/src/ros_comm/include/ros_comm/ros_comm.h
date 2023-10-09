#ifndef UROS__COMMUNICATION__H
#define UROS__COMMUNICATION__H

#include <stdio.h>

#include <rcl/error_handling.h>
#include <rcl/rcl.h>
#include <rclc/executor.h>
#include <rclc/rclc.h>
#include <rmw_microros/rmw_microros.h>
#include <std_msgs/msg/int32.h>

#include "pico/stdlib.h"
#include "pico_uart_transports.h"

namespace bbb {
namespace uros {

class RosComm {
 private:
  bool initialized = false;

  rcl_publisher_t publisher;
  std_msgs__msg__Int32 msg;

  rcl_timer_t timer;
  rcl_node_t node;
  rcl_allocator_t allocator;
  rclc_support_t support;
  rclc_executor_t executor;

  // Wait for agent successful ping for 2 minutes.
  const int timeout_ms = 1000;
  const uint8_t attempts = 120;

 public:
  RosComm();
  ~RosComm();
  void Init();
  void SendMsg();
  void ProcessLoop();
};

}; // namespace uros
}; // namespace bbb

#endif /* UROS__COMMUNICATION__H */
