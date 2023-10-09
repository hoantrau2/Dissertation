#include "ros_comm/ros_comm.h"
#include <functional>

namespace bbb {
namespace uros {

RosComm::RosComm() {
  Init();
}

RosComm::~RosComm() {
}

void RosComm::Init() {
  rmw_uros_set_custom_transport(
    true,
    NULL,
    pico_serial_transport_open,
    pico_serial_transport_close,
    pico_serial_transport_write,
    pico_serial_transport_read);

  allocator = rcl_get_default_allocator();

  rcl_ret_t ret = rmw_uros_ping_agent(timeout_ms, attempts);

  if (ret != RCL_RET_OK) {
    // Unreachable agent, exiting program.
    return;
  }

  rclc_support_init(&support, 0, NULL, &allocator);

  rclc_node_init_default(&node, "pico_node", "", &support);
  rclc_publisher_init_default(
    &publisher,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
    "pico_publisher");

  rclc_executor_init(&executor, &support.context, 1, &allocator);

  msg.data = 0;
  initialized = true;
}

void RosComm::SendMsg() {
  rcl_ret_t ret = rcl_publish(&publisher, &msg, NULL);
  msg.data++;
}

void RosComm::ProcessLoop() {
  rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));
}

}; // namespace uros
}; // namespace bbb