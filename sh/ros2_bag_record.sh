#source ~/ROS/isl2_create3/install/local_setup.sh
source $HOME/robot_setup.bash
#ros2 bag record /tf /tf_static /odom /scan /v4l/camera/image_raw/compressed
ros2 bag record /tf /tf_static /odom /scan /image/compressed --compression-mode file --compression-format zstd 
