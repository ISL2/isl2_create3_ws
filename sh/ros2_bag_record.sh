source ~/ROS/isl2_create3/install/local_setup.sh
ros2 bag record --start-paused /tf /tf_static /odom /scan /v4l/camera/image_raw/compressed
