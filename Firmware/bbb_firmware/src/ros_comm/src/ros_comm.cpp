#include "ros_comm/ros_comm.h"


void init_ros_comm (NodeComponents *node_components, rcl_node_t *node, rclc_executor_t *executor){
     stdio_init_all();

    // Set up Micro-ROS serial transport
    rmw_uros_set_custom_transport(
        true, NULL, pico_serial_transport_open, pico_serial_transport_close,
        pico_serial_transport_write, pico_serial_transport_read);

    // Initialize the Node and Micro-ROS support
    rclc_support_t support;
    rcl_allocator_t allocator;
    allocator = rcl_get_default_allocator();
    rclc_support_init(&support, 0, NULL, &allocator);


    rclc_node_init_default(node, "pico_node", "", &support);

    // Initialize Publisher
    rclc_publisher_init_default(&(node_components->publisher), node, ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist), "pico_publisher_topic_test");

    // Initialize Subscriber
    rclc_subscription_init_default(&(node_components->subscription), node, ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist), "/cmd_vel");


    rclc_executor_init(executor, &support.context, 2, &allocator);
}
void clean_up (NodeComponents *node_components, rcl_node_t *node){
     // Clean up
    rcl_subscription_fini(&(node_components->subscription), node);
    rcl_publisher_fini(&(node_components->publisher), node);
    rcl_node_fini(node);
}