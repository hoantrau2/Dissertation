# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jetson/bbb_jetson_ws/src/bbb_package

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jetson/bbb_jetson_ws/build/bbb_package

# Include any dependencies generated for this target.
include CMakeFiles/read_host.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/read_host.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/read_host.dir/flags.make

CMakeFiles/read_host.dir/src/read_host.cpp.o: CMakeFiles/read_host.dir/flags.make
CMakeFiles/read_host.dir/src/read_host.cpp.o: /home/jetson/bbb_jetson_ws/src/bbb_package/src/read_host.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jetson/bbb_jetson_ws/build/bbb_package/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/read_host.dir/src/read_host.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/read_host.dir/src/read_host.cpp.o -c /home/jetson/bbb_jetson_ws/src/bbb_package/src/read_host.cpp

CMakeFiles/read_host.dir/src/read_host.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/read_host.dir/src/read_host.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jetson/bbb_jetson_ws/src/bbb_package/src/read_host.cpp > CMakeFiles/read_host.dir/src/read_host.cpp.i

CMakeFiles/read_host.dir/src/read_host.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/read_host.dir/src/read_host.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jetson/bbb_jetson_ws/src/bbb_package/src/read_host.cpp -o CMakeFiles/read_host.dir/src/read_host.cpp.s

# Object files for target read_host
read_host_OBJECTS = \
"CMakeFiles/read_host.dir/src/read_host.cpp.o"

# External object files for target read_host
read_host_EXTERNAL_OBJECTS =

read_host: CMakeFiles/read_host.dir/src/read_host.cpp.o
read_host: CMakeFiles/read_host.dir/build.make
read_host: /opt/ros/foxy/lib/librclcpp.so
read_host: /opt/ros/foxy/lib/libgeometry_msgs__rosidl_typesupport_introspection_c.so
read_host: /opt/ros/foxy/lib/libgeometry_msgs__rosidl_typesupport_c.so
read_host: /opt/ros/foxy/lib/libgeometry_msgs__rosidl_typesupport_introspection_cpp.so
read_host: /opt/ros/foxy/lib/libgeometry_msgs__rosidl_typesupport_cpp.so
read_host: /opt/ros/foxy/lib/liblibstatistics_collector.so
read_host: /opt/ros/foxy/lib/liblibstatistics_collector_test_msgs__rosidl_typesupport_introspection_c.so
read_host: /opt/ros/foxy/lib/liblibstatistics_collector_test_msgs__rosidl_generator_c.so
read_host: /opt/ros/foxy/lib/liblibstatistics_collector_test_msgs__rosidl_typesupport_c.so
read_host: /opt/ros/foxy/lib/liblibstatistics_collector_test_msgs__rosidl_typesupport_introspection_cpp.so
read_host: /opt/ros/foxy/lib/liblibstatistics_collector_test_msgs__rosidl_typesupport_cpp.so
read_host: /opt/ros/foxy/lib/librcl.so
read_host: /opt/ros/foxy/lib/librcl_interfaces__rosidl_typesupport_introspection_c.so
read_host: /opt/ros/foxy/lib/librcl_interfaces__rosidl_generator_c.so
read_host: /opt/ros/foxy/lib/librcl_interfaces__rosidl_typesupport_c.so
read_host: /opt/ros/foxy/lib/librcl_interfaces__rosidl_typesupport_introspection_cpp.so
read_host: /opt/ros/foxy/lib/librcl_interfaces__rosidl_typesupport_cpp.so
read_host: /opt/ros/foxy/lib/librmw_implementation.so
read_host: /opt/ros/foxy/lib/librmw.so
read_host: /opt/ros/foxy/lib/librcl_logging_spdlog.so
read_host: /usr/lib/aarch64-linux-gnu/libspdlog.so.1.5.0
read_host: /opt/ros/foxy/lib/librcl_yaml_param_parser.so
read_host: /opt/ros/foxy/lib/libyaml.so
read_host: /opt/ros/foxy/lib/librosgraph_msgs__rosidl_typesupport_introspection_c.so
read_host: /opt/ros/foxy/lib/librosgraph_msgs__rosidl_generator_c.so
read_host: /opt/ros/foxy/lib/librosgraph_msgs__rosidl_typesupport_c.so
read_host: /opt/ros/foxy/lib/librosgraph_msgs__rosidl_typesupport_introspection_cpp.so
read_host: /opt/ros/foxy/lib/librosgraph_msgs__rosidl_typesupport_cpp.so
read_host: /opt/ros/foxy/lib/libstatistics_msgs__rosidl_typesupport_introspection_c.so
read_host: /opt/ros/foxy/lib/libstatistics_msgs__rosidl_generator_c.so
read_host: /opt/ros/foxy/lib/libstatistics_msgs__rosidl_typesupport_c.so
read_host: /opt/ros/foxy/lib/libstatistics_msgs__rosidl_typesupport_introspection_cpp.so
read_host: /opt/ros/foxy/lib/libstatistics_msgs__rosidl_typesupport_cpp.so
read_host: /opt/ros/foxy/lib/libtracetools.so
read_host: /opt/ros/foxy/lib/libgeometry_msgs__rosidl_generator_c.so
read_host: /opt/ros/foxy/lib/libstd_msgs__rosidl_typesupport_introspection_c.so
read_host: /opt/ros/foxy/lib/libstd_msgs__rosidl_generator_c.so
read_host: /opt/ros/foxy/lib/libstd_msgs__rosidl_typesupport_c.so
read_host: /opt/ros/foxy/lib/libstd_msgs__rosidl_typesupport_introspection_cpp.so
read_host: /opt/ros/foxy/lib/libstd_msgs__rosidl_typesupport_cpp.so
read_host: /opt/ros/foxy/lib/libbuiltin_interfaces__rosidl_typesupport_introspection_c.so
read_host: /opt/ros/foxy/lib/libbuiltin_interfaces__rosidl_generator_c.so
read_host: /opt/ros/foxy/lib/libbuiltin_interfaces__rosidl_typesupport_c.so
read_host: /opt/ros/foxy/lib/libbuiltin_interfaces__rosidl_typesupport_introspection_cpp.so
read_host: /opt/ros/foxy/lib/librosidl_typesupport_introspection_cpp.so
read_host: /opt/ros/foxy/lib/librosidl_typesupport_introspection_c.so
read_host: /opt/ros/foxy/lib/libbuiltin_interfaces__rosidl_typesupport_cpp.so
read_host: /opt/ros/foxy/lib/librosidl_typesupport_cpp.so
read_host: /opt/ros/foxy/lib/librosidl_typesupport_c.so
read_host: /opt/ros/foxy/lib/librcpputils.so
read_host: /opt/ros/foxy/lib/librosidl_runtime_c.so
read_host: /opt/ros/foxy/lib/librcutils.so
read_host: CMakeFiles/read_host.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jetson/bbb_jetson_ws/build/bbb_package/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable read_host"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/read_host.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/read_host.dir/build: read_host

.PHONY : CMakeFiles/read_host.dir/build

CMakeFiles/read_host.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/read_host.dir/cmake_clean.cmake
.PHONY : CMakeFiles/read_host.dir/clean

CMakeFiles/read_host.dir/depend:
	cd /home/jetson/bbb_jetson_ws/build/bbb_package && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jetson/bbb_jetson_ws/src/bbb_package /home/jetson/bbb_jetson_ws/src/bbb_package /home/jetson/bbb_jetson_ws/build/bbb_package /home/jetson/bbb_jetson_ws/build/bbb_package /home/jetson/bbb_jetson_ws/build/bbb_package/CMakeFiles/read_host.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/read_host.dir/depend
