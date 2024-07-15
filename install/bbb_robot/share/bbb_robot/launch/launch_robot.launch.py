import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node

def generate_launch_description():
    package_name = 'bbb_robot'
    rsp = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([os.path.join(
            get_package_share_directory(package_name), 'launch', 'rsp.launch.py'
        )]), launch_arguments={'use_sim_time': 'false', 'use_ros2_control': 'false'}.items()  #Force sim time to be enabled
    )


    return LaunchDescription([
        Node(
            package='rplidar_ros',
            executable='rplidar_composition',
            output='screen',
            parameters=[{
                'serial_port': '/dev/serial/by-path/platform-70090000.xusb-usb-0:2.4:1.0-port0',
                'frame_id': 'lidar2D_frame',
                'angle_compensate': True,
                'scan_mode': 'Standard'
            }]
        ),
        rsp,
        Node(
            package='ros2_laser_scan_matcher', executable='laser_scan_matcher', output='screen', 
            parameters=[{ 'publish_tf': True, 'laser_frame': 'lidar2D_frame', 'base_frame': 'base_footprint'}]),
    ])

# ros2 launch bbb_robot launch_robot.launch.py
# ros2 launch bbb_robot launch_toolbox.launch.py
# ls /dev/serial/by-path/