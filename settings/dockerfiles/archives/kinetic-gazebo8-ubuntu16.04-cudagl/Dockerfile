FROM nvidia/cudagl:10.2-runtime-ubuntu16.04

LABEL Author="leechanwoo25@gmail.com"
LABEL Description="This docker image is CUDA 10.2 based Ubuntu 16.04 \
                   with ros-kinetic-desktop-full & Gazebo8"
LABEL version="1.0"

# -------------------- Install required (&useful) packages --------------------
RUN apt-get update && apt-get install -y \
software-properties-common python-software-properties \
lsb-release \
mesa-utils \
wget git curl vim \
python-rosdep python-rosinstall \
python3-pip python-pip \
build-essential \
net-tools iputils-ping \
&& apt-get clean

# -------------------- ROS-Kinetic Desktop Full Image --------------------
# Install ROS
RUN sh -c 'echo "deb http://packages.ros.org/ros/ubuntu xenial main" > /etc/apt/sources.list.d/ros-latest.list' \
    && apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654 \
    && apt-get update && apt-get install -y ros-kinetic-desktop-full \
 	&& rm -rf /var/lib/apt/lists/* && pip install catkin_tools
# Configure ROS
RUN rosdep init && rosdep fix-permissions && rosdep update \
    && echo "source /opt/ros/kinetic/setup.bash" >> /root/.bashrc \
    && echo "source /usr/share/gazebo/setup.sh" >> /root/.bashrc

# -------------------- Gazebo 8  --------------------
# Setup osrfoundation repository keys
RUN apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys D2486D2DD83DB69272AFE98867170598AF249743 \
    && . /etc/os-release \
    && . /etc/lsb-release \
    && echo "deb http://packages.osrfoundation.org/gazebo/$ID-stable $DISTRIB_CODENAME main" > /etc/apt/sources.list.d/gazebo-latest.list

# Remove Gazebo installed with ROS-Kinetic full
RUN apt-get purge gazebo* -y \
    && apt-get update -y && apt-get upgrade -y && apt-get install -y \
	gazebo8 \
	ros-kinetic-gazebo8-ros-pkgs \
	ros-kinetic-gazebo8-ros-control \
    ros-kinetic-turtlebot \
	&& apt-get clean


CMD ["/bin/bash"]
