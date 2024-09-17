FROM nvidia/cudagl:10.2-runtime-ubuntu16.04


ENV UBUNTU_RELEASE=xenial
RUN sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $UBUNTU_RELEASE main" > /etc/apt/sources.list.d/ros-latest.list'
RUN apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654

RUN apt-get update && apt-get install -y \
    ros-kinetic-desktop-full

RUN apt-get update && apt-get install -y \
    git wget curl vim\
    ros-kinetic-turtlebot \
 && rm -rf /var/lib/apt/lists/*
