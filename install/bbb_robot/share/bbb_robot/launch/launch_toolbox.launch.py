
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='slam_toolbox',
            executable='async_slam_toolbox_node',
            name='async_slam_toolbox_node',
            output='screen',
            remappings=[
                ('use_sim_time', 'false')  
            ],
            parameters=[
                {'params_file': './src/bbb_robot/config/mapper_params_online_async.yaml'},
                {'use_sim_time': False}  
            ],

        )
    ])