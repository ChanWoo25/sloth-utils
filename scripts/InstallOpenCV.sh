#! /bin/bash

export DEBIAN_FRONTEND=noninteractive

cd ~

sudo apt-get update &&
sudo apt-get dist-upgrade -y &&
sudo apt-get install -y --allow-downgrades --allow-change-held-packages --no-install-recommends \
      cmake build-essential git \
      gfortran libprotobuf-dev protobuf-compiler \
      libblas-dev libopenblas-dev liblapack-dev liblapacke-dev \
      libjpeg-dev libpng-dev libtiff-dev libtbb-dev libgtk2.0-dev pkg-config \
      ffmpeg libavcodec-dev libavformat-dev libswscale-dev libxvidcore-dev libx264-dev libxine2-dev \
      libgoogle-glog-dev libgflags-dev libatlas-base-dev libeigen3-dev libsuitesparse-dev libgl1-mesa-dev &&
sudo apt-get clean &&
sudo apt-get autoremove -y &&

# Install Ceres
export CERES_VERSION=1.14.0
cd ~ &&
git clone https://ceres-solver.googlesource.com/ceres-solver &&
cd ceres-solver &&
git checkout ${CERES_VERSION} &&
mkdir build &&
cd build &&
cmake .. &&
make -j$(nproc) install && ldconfig && cd ~ &&
rm -rf ceres-solver

# Install OpenCV
# Ceres 2.1.0 has some new function that build issue occurs when building sfm
export OPENCV_VERSION=3.3.0
cd ~
# git config --global http.sslverify false &&
git clone https://github.com/opencv/opencv.git --branch ${OPENCV_VERSION} --single-branch
git clone https://github.com/opencv/opencv_contrib.git --branch ${OPENCV_VERSION} --single-branch

cd opencv
mkdir build && cd build

# atmost packages will be detected automatically
cmake -D CMAKE_BUILD_TYPE=RELEASE \
        -D CMAKE_INSTALL_PREFIX=/usr/local \
        -D OPENCV_ENABLE_NONFREE=ON \
        -D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib/modules \
        .. &&
make -j$(nproc) install && ldconfig &&
rm -rf ~/opencv*

### Docker segment
# Install OpenCV & Ceres Dependencies
# ENV DEBIAN_FRONTEND=noninteractive
# RUN cd ~ \
# &&  apt update && apt-get upgrade -y \
# &&  apt install -y --allow-downgrades --allow-change-held-packages --no-install-recommends \
#       cmake build-essential wget curl unzip git vim openssh-server openssh-client \
#       gfortran libprotobuf-dev protobuf-compiler \
#       libblas-dev liblapack-dev liblapacke-dev \
#       libjpeg-dev libpng-dev libtiff-dev libtbb-dev libgtk2.0-dev pkg-config \
#       ffmpeg libavcodec-dev libavformat-dev libswscale-dev libxvidcore-dev libx264-dev libxine2-dev
#       libgoogle-glog-dev libgflags-dev libatlas-base-dev libeigen3-dev libsuitesparse-dev \
# &&  apt-get clean && apt-get autoremove -y \
# &&  rm -rf /var/lib/apt/lists/*

# # Install Ceres
# ARG CERES_VERSION=1.14.0
# RUN cd ~ \
# &&  git clone https://ceres-solver.googlesource.com/ceres-solver \
# &&  cd ceres-solver \
# &&  git checkout ${CERES_VERSION} \
# &&  mkdir build && cd build \
# &&  cmake .. \
# &&  make -j$(nproc) install && ldconfig \
# &&  rm -rf ~/ceres-solver

# # Install OpenCV
# ARG OPENCV_VERSION=3.4.18
# RUN cd ~ \
# &&  git config --global http.sslverify false \
# &&  git clone https://github.com/opencv/opencv.git --branch ${OPENCV_VERSION} --single-branch \
# &&  git clone https://github.com/opencv/opencv_contrib.git --branch ${OPENCV_VERSION} --single-branch \
# &&  cd opencv \
# &&  mkdir build && cd build \
# # atmost packages will be detected automatically
# &&  cmake -D CMAKE_BUILD_TYPE=RELEASE \
#         -D CMAKE_INSTALL_PREFIX=/usr/local \
#         -D OPENCV_ENABLE_NONFREE=ON \
#         -D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib/modules \
#         .. \
# &&  make -j$(nproc) install && ldconfig \
# &&  rm -rf ~/opencv*
