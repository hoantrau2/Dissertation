from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, ExecuteProcess, TimerAction
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='bbb_package', 
            executable='data_processing_node',
            output='screen',
            on_exit=[ExecuteProcess(
                cmd=["echo", "data_processing_node initialized"],
                output='screen'
            )]
        ),

        Node(
            
            package='bbb_package', 
            executable='straight_line_node',
            output='screen',
            on_exit=[ExecuteProcess(
                cmd=["echo", "straight_line_node initialized"],
                output='screen'
            )]
        ),
    ])