from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import IncludeLaunchDescription, DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration, TextSubstitution

from ament_index_python.packages import get_package_share_directory

import os


def generate_launch_description():
    joy_input_node = Node(
        package='joy',
        executable='joy_node',
        name='joy_input'
    )

    joy_twist_node = Node(
        package='teleop_twist_joy',
        executable='teleop_node',
        name='joy_twist',
        parameters=[{
            'axis_linear.x': 1,
            'axis_angular.yaw': 3,
            'enable_button': 5,
        }]
    )

    joy_controller = Node(
        package='isl2_create3_joy_control',
        executable='joy_controller',
        name='joy_controller'
    )

    return LaunchDescription([
        joy_input_node,
        joy_twist_node,
        joy_controller,
    ])
