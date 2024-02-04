#!/bin/bash
#########################################################
# SYSTEM VAR
#########################################################
ubuntu_version_full=$(lsb_release -r)
ubuntu_version=$(cut -f2 <<<"$ubuntu_version_full")
x=${DEFAULT_X}
y=${DEFAULT_Y}
z=${DEFAULT_Z}
yaw=${DEFAULT_YAW}

SIM_CHOICE=$1
HEADLESS=$2

__byobu() {
    session=$1
    window_no=$2
    name=$3
    cmd=$4
    target_ros_master=$5
    # If No Session
    if ! (byobu list-session | grep -q "$session"); then
        echo " NO SESSION - CREATING NEW ONE"
        byobu new-session -d -s $session
    fi

    byobu new-window -t $session:$window_no
    byobu rename-window -t $session:$window_no "$name"
    byobu select-window -t $session:$window_no
    echo "Apply Command : " $cmd " on window : " $window_no
    byobu send-keys -t $session:$window_no "$cmd" C-m
}

byobu_bash() {
    session=$1
    window_no=$2
    name=$3
    cmd=$4
    __byobu $1 $2 $3 "$cmd"
}

#########################################################
# FUNCTIONS
#########################################################

kill_instance() {
    byobu kill-server
    sleep 1s
}

open_byobu_session() {
    session_name=$1
    launch_terminal byobu attach-session -t $session_name
}


#########################################################
# MAIN
#########################################################
echo "[STARTING ROS2 Nodes]"
kill_instance

source ~/robot_setup.bash

# Robot Setup
byobu_bash CORE 1 XACRO "ros2 launch isl2_create3_bringup tf_static.launch.py"

# Backend Session
byobu_bash HW 1 LIDAR "ros2 launch isl2_create3_bringup laser.launch.py"
byobu_bash HW 2 JOY "ros2 launch isl2_create3_bringup joy.launch.py"

# Camera Session
byobu_bash CAMERA 1 CAM_SV "sh /home/khadas/camera_launch/1-launch_rkisp_demo.sh"
echo "Waiting Camera Driver to Spinning Up"
sleep 3
byobu_bash CAMERA 2 GSCAM "ros2 launch isl2_create3_bringup cam.launch.xml"

# open_byobu_session CORE
# byobu_bash RVIZ 0 rviz "rviz -d ~/obodroid/sr1/sr1_robot/src/bringup/sr1_bringup/rviz/obo_default.rviz"
exit
