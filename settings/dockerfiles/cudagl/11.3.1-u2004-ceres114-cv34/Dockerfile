# Author: Chanwoo Lee (leechanwoo25@gmail.com)
# Update: 2024. 01. 15.
# Note: write when building LARVIO (https://github.com/PetWorm/LARVIO/tree/master)
FROM nvidia/cudagl:11.3.1-devel-ubuntu20.04

# [Note]
# - If you use WSL2, set 'export LIBGL_ALWAYS_INDIRECT=0' into '~/.bashrc'
# - Otherwise, set 'export LIBGL_ALWAYS_INDIRECT=1' into '~/.bashrc'
ENV DEBIAN_FRONTEND=noninteractive N_WORKER=12

RUN cd ~ &&\
 apt-key adv --fetch-keys https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2004/x86_64/3bf863cc.pub &&\
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

##########################
# Install Clang & Clangd #
##########################
# - version 10 is default for Ubuntu 20.04
RUN cd ~ &&\
 wget https://apt.llvm.org/llvm.sh &&\
 chmod +x llvm.sh && ./llvm.sh 10 &&\
 apt update && apt install -y clang clangd &&\
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

##################
# Install OpenCV #
##################
RUN export OPENCV_VERSION=3.4.18 &&\
 cd ~ && git config --global http.sslverify false &&\
 git clone https://github.com/opencv/opencv.git --branch ${OPENCV_VERSION} --single-branch &&\
 git clone https://github.com/opencv/opencv_contrib.git --branch ${OPENCV_VERSION} --single-branch &&\
 cd opencv &&\
 mkdir build && cd build &&\
 # atmost packages will be detected automatically
 cmake \
  -D CMAKE_BUILD_TYPE=RELEASE \
  -D CMAKE_INSTALL_PREFIX=/usr/local \
  -D OPENCV_ENABLE_NONFREE=ON \
  -D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib/modules \
  .. &&\
 make -j${N_WORKER} install && ldconfig &&\
 rm -rf ~/opencv*

# Unset Envs
ENV DEBIAN_FRONTEND= N_WORKER=

# Etc
RUN \
 echo "export CC=clang"    >> ~/.bashrc &&\
 echo "export CXX=clang++" >> ~/.bashrc
