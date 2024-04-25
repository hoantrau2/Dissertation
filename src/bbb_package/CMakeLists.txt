cmake_minimum_required(VERSION 3.5)
project(bbb_package)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(serial REQUIRED)
find_package(tf2_msgs REQUIRED)

add_executable(read_IMU src/read_IMU.cpp)
ament_target_dependencies(read_IMU rclcpp std_msgs geometry_msgs serial)

add_executable(read_lidar src/read_lidar.cpp)
ament_target_dependencies(read_lidar rclcpp std_msgs tf2_msgs)

add_executable(pid_node src/pid_node.cpp)
ament_target_dependencies(pid_node rclcpp std_msgs)

add_executable(delta_angle_node src/delta_angle_node.cpp)
ament_target_dependencies(delta_angle_node rclcpp std_msgs)

add_executable(tune_fuzzy_node src/tune_fuzzy_node.cpp)
ament_target_dependencies(tune_fuzzy_node rclcpp std_msgs)

add_executable(straight_line_node src/straight_line_node.cpp)
ament_target_dependencies(straight_line_node rclcpp std_msgs)

add_executable(circumference_node src/circumference_node.cpp)
ament_target_dependencies(circumference_node rclcpp std_msgs)

add_executable(sinusoidal_node src/sinusoidal_node.cpp)
ament_target_dependencies(sinusoidal_node rclcpp std_msgs)

add_executable(tune_node src/tune_node.cpp)
ament_target_dependencies(tune_node rclcpp std_msgs)

add_executable(fuzzy_longitudinal_controllers src/fuzzy_longitudinal_controllers.cpp)
ament_target_dependencies(fuzzy_longitudinal_controllers rclcpp std_msgs)

add_executable(stanley_node src/stanley_node.cpp)
ament_target_dependencies(stanley_node rclcpp std_msgs tf2_msgs)

add_executable(controllers_node src/controllers_node.cpp)
ament_target_dependencies(controllers_node rclcpp std_msgs)

add_executable(data_processing_node src/data_processing_node.cpp)
ament_target_dependencies(data_processing_node rclcpp std_msgs tf2_msgs)
add_executable(data_processing_node_straight src/data_processing_node_straight.cpp)
ament_target_dependencies(data_processing_node_straight rclcpp std_msgs tf2_msgs)


# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

install(TARGETS
  read_IMU
  read_lidar
  pid_node
  tune_fuzzy_node
  straight_line_node
  circumference_node
  sinusoidal_node
  tune_node
  delta_angle_node
  fuzzy_longitudinal_controllers
  stanley_node
  controllers_node
  data_processing_node_straight
  DESTINATION lib/${PROJECT_NAME}/
)
 install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
