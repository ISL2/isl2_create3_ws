from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    camera_logitech_node = Node( # ros2 run v4l2_camera v4l2_camera_node --ros-args --param video_device:=/dev/video51
        package='v4l2_camera',
        executable='v4l2_camera_node',
        name='v4l2_camera_logitech',
        parameters=[{
            'video_device': '/dev/video51',
        }],
    )

    return LaunchDescription([
        camera_logitech_node,
    ])
