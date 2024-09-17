#!/bin/bash
set -e

# Source ROS setuo
source  /opt/ros/kinetic/setup.bash

# Source enviroment variables for Gazebo
source /usr/share/gazebo/setup.sh

exec "$@"
