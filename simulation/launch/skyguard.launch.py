from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(package='gazebo_ros', executable='gazebo', output='screen'),
        Node(package='skyguard_sim', executable='spawn_drone', output='screen'),
        Node(package='skyguard_controller', executable='follow_me_node', output='screen'),
    ])
