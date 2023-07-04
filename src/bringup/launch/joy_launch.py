from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import IncludeLaunchDescription, DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration, TextSubstitution

from ament_index_python.packages import get_package_share_directory

import os


def generate_launch_description():
    joy_config = LaunchConfiguration('joy_config')
    config_filepath = LaunchConfiguration('config_filepath')

    return LaunchDescription([
        DeclareLaunchArgument('joy_config', default_value='joy_twist'),
        DeclareLaunchArgument(
            'config_filepath',
            default_value=[
                TextSubstitution(text=os.path.join(get_package_share_directory('bringup'), 'config', '')),
                joy_config, TextSubstitution(text='.config.yaml')
            ]
        ),
        Node(
            package='joy',
            namespace='joy',
            executable='joy_node',
            name='joy_input'
        ),
        Node(
            package='teleop_twist_joy',
            namespace='joy',
            executable='teleop_node',
            name='joy_twist',
            parameters=[config_filepath]
        ),
    ])
