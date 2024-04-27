from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, ExecuteProcess, TimerAction
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='rplidar_ros', 
            executable='rplidar_composition', 
            output='screen',
            parameters=[{
                'serial_port': '/dev/serial/by-path/platform-70090000.xusb-usb-0:2.2:1.0-port0',
                #  'serial_port': '/dev/ttyUSB0',
                'frame_id': 'lidar',
                'angle_compensate': True,
                'scan_mode': 'Standard' 
            }]
        ),

        Node(
            package='ros2_laser_scan_matcher', 
            executable='laser_scan_matcher', 
            output='screen', 
            parameters=[{
                'publish_tf': True,
                'laser_frame': 'lidar',
                'base_frame': 'base_footprint'
            }]
        ),

        Node(
            package='tf2_ros', 
            executable='static_transform_publisher', 
            arguments=["0", "0", "0.5", "0", "0", "0", "base_footprint", "lidar"]
        ),

        # Delayed execution nodes
        # TimerAction(
        #     actions=[
        #         Node(
        #             package='bbb_package', 
        #             executable='read_IMU',
        #             output='screen',
        #             on_exit=[ExecuteProcess(
        #                 cmd=["echo", "IMU_node initialized"],
        #                 output='screen'
        #             )]
        #         )
        #     ],
        #     period=6.0
        # ),

        Node(
            package='bbb_package', 
            executable='tune_node',
            output='screen',
            on_exit=[ExecuteProcess(
                cmd=["echo", "tune_node initialized"],
                output='screen'
            )]
        ),

        TimerAction(
            actions=[
                Node(
                    package='bbb_package', 
                    executable='controllers_node',
                    output='screen',
                    on_exit=[ExecuteProcess(
                        cmd=["echo", "controllers_node initialized"],
                        output='screen'
                    )]
                )
            ],
            period=6.0, 
        ),
    ])


#    TUTORIAL TUNING FUZZY PARAMETERS
    
#     ////////////pico-w
# sudo systemctl restart snapd
# snap interface serial-port
# sudo snap connect micro-xrce-dds-agent:serial-port snapd:pico-2
# export ROS_DOMAIN_ID=0
# sudo micro-xrce-dds-agent serial --dev /dev/ttyACM0 baudrade=115200

# ////// ubuntu 
#     export ROS_DOMAIN_ID=0
#     source ./install/setup.bash
#     colcon build --packages-select bbb_package  
  #ros2 launch bbb_package thesis.launch.py 
# ros2 run bbb_package read_IMU
# ros2 run bbb_package data_processing_node_straight
# ros2 run bbb_package pid_node












# ////// ubuntu 
#     export ROS_DOMAIN_ID=0
#     source ./install/setup.bash
#     colcon build --packages-select bbb_package
#     colcon build --packages-select tune_package
# ros2 run bbb_package data_processing_node_straight


    # ros2 run bbb_package read_IMU
    # ros2 run bbb_package pid_node
    # ros2 run bbb_package tune_node
    # ros2 run bbb_package tune_fuzzy_node
    # ros2 run bbb_package delta_angle_node

    #ros2 launch bbb_package thesis.launch.py
    #ros2 launch tune_package tune.launch.py
    # ros2 run bbb_package read_IMU
    # ros2 launch slam_toolbox online_async_launch.py params_file:=./src/bbb_robot/config/mapper_params_online_async.yaml use_sim_time:=false
    # ros2 run tf2_tools view_frames
    #colcon build --packages-select bbb_package
    #https://answers.ros.org/question/372752/static_transform_publisher-in-ros2-launch-file/
    #https://github.com/AlexKaravaev/csm
    #https://github.com/AlexKaravaev/ros2_laser_scan_matcher
    # ros2 run rplidar_ros rplidar_composition --ros-args -p serial_port:=/dev/serial/by-path/platform-70090000.xusb-usb-0:2.1:1.0-port0 -p frame_id:=laser_frame -p angle_compensate:=true -p scan_mode:=Standard

             
    
         
