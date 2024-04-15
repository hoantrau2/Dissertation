from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, ExecuteProcess
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='rplidar_ros', 
            executable='rplidar_composition', 
            output='screen',
            parameters=[{
                'serial_port': '/dev/serial/by-path/platform-70090000.xusb-usb-0:2.3:1.0-port0',
                'frame_id': 'lidar',
                'angle_compensate': True,
                'scan_mode': 'Standard' }
            ]
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

    ])

    #ros2 launch bbb_package rplidar.launch.py
    # ros2 launch slam_toolbox online_async_launch.py params_file:=./src/bbb_robot/config/mapper_params_online_async.yaml use_sim_time:=false
    # ros2 run tf2_tools view_frames
    #colcon build --packages-select bbb_package
    #https://answers.ros.org/question/372752/static_transform_publisher-in-ros2-launch-file/
    #https://github.com/AlexKaravaev/csm
    #https://github.com/AlexKaravaev/ros2_laser_scan_matcher
             
    
         
