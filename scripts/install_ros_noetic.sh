#! /bin/bash

read -p "Option ('sudo' or 'dock'): " opt

if [[ $opt == "sudo" ]]; then
  export SUDO=${opt}
  echo "SUDO: $SUDO"
elif [[ $opt == "dock" ]]; then
  export SUDO=
  echo "SUDO: $SUDO"
else
  echo "Unvalid Option '${opt}'"
fi

$SUDO apt update && $SUDO apt install curl
$SUDO sh -c 'echo "Etc/UTC" > /etc/timezone'
$SUDO sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | $SUDO apt-key add -
$SUDO apt update
$SUDO apt install ros-noetic-desktop
$SUDO apt install --no-install-recommends -y \
  python3-dev \
  python3-pip \
  python3-rosdep \
  python3-rosinstall \
  python3-rosinstall-generator \
  python3-wstool \
  python3-vcstool \
  python3-vcstools \
  python3-catkin-tools \
  bash-completion && \
$SUDO rosdep init && \
rosdep update --rosdistro noetic

# $SUDO sh -c 'echo "source /opt/ros/noetic/setup.bash" >> ~/.bashrc'
# $SUDO sh -c 'echo "alias sb='source ~/.bashrc'" >> ~/.bashrc'
# $SUDO sh -c 'echo "alias ss='source devel/setup.bash'" >> ~/.bashrc'


