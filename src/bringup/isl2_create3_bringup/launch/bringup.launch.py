from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource

from ament_index_python.packages import get_package_share_directory

import os


def generate_launch_description():
    PACKAGE_NAME = 'isl2_create3_bringup'

    joy_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            os.path.join(get_package_share_directory(PACKAGE_NAME), 'launch'),
            '/joy.launch.py'
            ])
        )

    camera_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            os.path.join(get_package_share_directory(PACKAGE_NAME), 'launch'),
            '/camera.launch.py'
            ])
        )

    return LaunchDescription([
        joy_launch,
        camera_launch,
    ])
