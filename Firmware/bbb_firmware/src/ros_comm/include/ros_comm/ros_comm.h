#ifndef UROS__COMMUNICATION__H
#define UROS__COMMUNICATION__H

#include "pico/stdlib.h"
#include "pico_uart_transports.h"
#include <rcl/error_handling.h>
#include <rcl/rcl.h>
#include <rclc/executor.h>
#include <rclc/rclc.h>
#include <rmw_microros/rmw_microros.h>
#include <geometry_msgs/msg/twist.h>
#include <stdio.h>

// Define a structure to hold the publisher and subscriber objects
typedef struct
{
    rcl_publisher_t publisher;
    rcl_subscription_t subscription;
    geometry_msgs__msg__Twist msg;
} NodeComponents;

void init_ros_comm (NodeComponents *node_components, rcl_node_t *node, rclc_executor_t *executor);
void clean_up (NodeComponents *node_components, rcl_node_t *node);

#endif /* UROS__COMMUNICATION__H */
