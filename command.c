----commad with uros-pico
sudo systemctl restart snapd
snap interface serial-port
sudo snap connect micro-xrce-dds-agent:serial-port snapd:pico-1
export ROS_DOMAIN_ID=0
sudo micro-xrce-dds-agent serial --dev /dev/ttyACM0 baudrade=115200
ros2 run teleop_twist_keyboard teleop_twist_keyboard
#reference link: https://github.com/eProsima/Micro-XRCE-DDS-Agent

---- commad in rplidar.launch.py
    # ros2 launch slam_toolbox online_async_launch.py params_file:=./src/bbb_robot/config/mapper_params_online_async.yaml use_sim_time:=false
    # ros2 run tf2_tools view_frames


    # export ROS_DOMAIN_ID=0
    source ./install/setup.bash
    colcon build --packages-select bbb_package

ros2 run bbb_package pid_node
ros2 run bbb_package tune_node	
ros2 run bbb_package fuzzy_node_test

sudo systemctl restart snapd
snap interface serial-port
sudo snap connect micro-xrce-dds-agent:serial-port snapd:pico-1
sudo micro-xrce-dds-agent serial --dev /dev/ttyACM0 baudrade=115200
ros2 run bbb_package tune_node
colcon build --packages-select bbb_package


        # ros2 run tf2_tools view_frames
        
    #colcon build --packages-select bbb_package

    #ls /dev/serial/by
    #https://answers.ros.org/question/372752/static_transform_publisher-in-ros2-launch-file/
    #https://github.com/AlexKaravaev/csm
    #https://github.com/AlexKaravaev/ros2_laser_scan_matcher





    TUTORIAL TUNING FUZZY PARAMETERS
    
    ////////////pico-w
    sudo systemctl restart snapd
snap interface serial-port
sudo snap connect micro-xrce-dds-agent:serial-port snapd:pico-1
export ROS_DOMAIN_ID=0
sudo micro-xrce-dds-agent serial --dev /dev/ttyACM0 baudrade=115200

////// ubuntu 
    export ROS_DOMAIN_ID=0
    source ./install/setup.bash
    colcon build --packages-select bbb_package

    
    ros2 run bbb_package read_IMU
    ros2 run bbb_package pid_node
    ros2 run bbb_package tune_node
    ros2 run bbb_package tune_fuzzy_node
    ros2 run bbb_package delta_angle_node

