# Author: Chanwoo Lee (leechanwoo25@gmail.com)
# Last modified: 2024.03.09 - 16:00
FROM nvidia/cudagl:11.3.1-devel-ubuntu18.04

# [Note]
# - If you use WSL2, set 'export LIBGL_ALWAYS_INDIRECT=0' into '~/.bashrc'
# - Otherwise, set 'export LIBGL_ALWAYS_INDIRECT=1' into '~/.bashrc'
ENV DEBIAN_FRONTEND=noninteractive N_WORKER=8

RUN cd ~ &&\
 apt-key adv --fetch-keys https://developer.download.nvidia.com/compute/cuda/repos/ubuntu1804/x86_64/3bf863cc.pub &&\
 apt update && apt dist-upgrade -y &&\
 echo "export LIBGL_ALWAYS_INDIRECT=1" >> /root/.bashrc &&\
 apt clean && apt autoremove -y &&\
 rm -rf /var/lib/apt/lists/*

##############
# Essentials #
##############
RUN cd ~ &&\
 apt update &&\
 apt install -y --allow-downgrades --allow-change-held-packages --no-install-recommends \
  lsb-release wget curl vim git unzip software-properties-common \
  openssh-server openssh-client \
  build-essential cmake ninja-build pkg-config \
  gfortran gnupg gnupg2 libprotobuf-dev protobuf-compiler &&\
 apt clean && apt autoremove -y &&\
 rm -rf /var/lib/apt/lists/*

########################
# Dependencies: Part 1 #
########################
RUN cd ~ &&\
 apt update &&\
 apt install -y --allow-downgrades --allow-change-held-packages --no-install-recommends \
  libeigen3-dev libflann-dev libboost-all-dev \
  libblas-dev liblapack-dev liblapacke-dev tzdata dirmngr  \
  libjpeg-dev libpng-dev libtiff-dev libtbb-dev &&\
 apt clean && apt autoremove -y &&\
 rm -rf /var/lib/apt/lists/*

########################
# Dependencies: Part 2 #
########################
RUN cd ~ &&\
 apt update &&\
 apt install -y --allow-downgrades --allow-change-held-packages --no-install-recommends \
  libgtk2.0-dev mesa-utils libgl1-mesa-glx libhdf5-dev \
  ffmpeg libavcodec-dev libavformat-dev libswscale-dev libxvidcore-dev libx264-dev libxine2-dev \
  libatlas-base-dev libsuitesparse-dev \
  tzdata dirmngr &&\
 apt clean && apt autoremove -y &&\
 rm -rf /var/lib/apt/lists/*

#################
# Install Ceres #
#################
RUN export CERES_VERSION=1.14.0 &&\
 apt update &&\
 apt install -y --no-install-recommends libgflags-dev libgoogle-glog-dev &&\
 apt clean && apt autoremove -y &&\
 rm -rf /var/lib/apt/lists/* &&\
 cd ~ &&\
 git config --global http.sslverify false &&\
 git clone --single-branch -b ${CERES_VERSION} \
   https://ceres-solver.googlesource.com/ceres-solver &&\
 cd ceres-solver &&\
 mkdir build && cd build &&\
 cmake .. &&\
 make -j${N_WORKER} install && ldconfig &&\
 rm -rf ~/ceres-solver

###################
# Install Melodic #
###################
RUN cd ~ &&\
 echo 'Etc/UTC' > /etc/timezone &&\
 echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros1-latest.list &&\
 curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | apt-key add - &&\
 export LANG=C.UTF-8 LC_ALL=C.UTF-8 &&\
 apt update &&\
 apt install -y --no-install-recommends ros-melodic-desktop-full &&\
 apt clean && apt autoremove -y &&\
 rm -rf /var/lib/apt/lists/*
RUN cd ~ &&\
 apt update &&\
 apt install --no-install-recommends -y \
  python-dev \
  python-pip \
  python-rosdep \
  python-rosinstall \
  python-rosinstall-generator \
  python-wstool \
  python-vcstool \
  python-vcstools \
  python-catkin-tools \
  bash-completion &&\
 rosdep init && rosdep update --rosdistro melodic &&\
 apt clean && apt autoremove -y &&\
 rm -rf /var/lib/apt/lists/*

# Unset Envs
ENV DEBIAN_FRONTEND= N_WORKER=
