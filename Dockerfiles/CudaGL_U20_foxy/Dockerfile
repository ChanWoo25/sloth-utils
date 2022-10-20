ARG BASE_IMAGE=nvidia/cudagl:11.4.2-base-ubuntu20.04
ARG UNAME=leecw
# -----------------

FROM ${BASE_IMAGE}

LABEL AUTHOR="Chanwoo Lee" EMAIL="leechanwoo25@gmail.com" \
  Description="This docker image is CUDA 11.4.2 (OpenGL Support) based Ubuntu 20.04 with ros foxy" \
  version="1.0"

# DEBIAN_FRONTEND:설치시 사용자 입력을 요구하는 패키지의 경우, 패스하기 위함
ENV ROS_DISTRO=foxy ROS_ROOT=/opt/ros/foxy DEBIAN_FRONTEND=noninteractive

# 그래픽지원을 위한 mesa-dri 추가 + Install ROS foxy
RUN apt-get update && apt-get dist-upgrade -y && apt-get install -y --no-install-recommends \
  cmake build-essential ninja-build git \
  locales \
  curl unzip wget \
  gnupg2 \
  lsb-release \
  ca-certificates \
  vim \
  mesa-utils \
&& locale-gen en_US en_US.UTF-8 \
&& export LANG=en_US.UTF-8 && export PYTHONIOENCODING=utf-8 && locale \
&& update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8

RUN curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key  -o /usr/share/keyrings/ros-archive-keyring.gpg \
&& echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | tee /etc/apt/sources.list.d/ros2.list > /dev/null \
&& apt-get update && apt-get install -y ros-foxy-desktop \
&& apt-get install -y python3-rosdep python3-pip \
  python3-colcon-common-extensions python3-vcstool \
&& rosdep init && rosdep update \
&& pip3 install -U argcomplete \
&& apt-get autoremove --purge --yes \
&& apt-get clean \
&& echo "source /opt/ros/foxy/setup.bash" >> $HOME/.bashrc \
&& chmod +x /opt/ros/foxy/setup.* \
&& . /opt/ros/foxy/setup.sh
