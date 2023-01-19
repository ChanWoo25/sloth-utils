FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive \
    LIBGL_ALWAYS_INDIRECT=1

RUN apt update && apt dist-upgrade -y && apt clean && apt autoremove -y

# Basic
RUN apt install -y --allow-downgrades --allow-change-held-packages --no-install-recommends \
  build-essential wget curl unzip git vim \
  openssh-server openssh-client

# Coding dependencies
RUN apt install -y \
  gfortran libprotobuf-dev protobuf-compiler \
  libblas-dev liblapack-dev liblapacke-dev \
  libjpeg-dev libpng-dev libtiff-dev libtbb-dev libgtk2.0-dev mesa-utils libgl1-mesa-glx pkg-config \
  ffmpeg libavcodec-dev libavformat-dev libswscale-dev libxvidcore-dev libx264-dev libxine2-dev \
  libgoogle-glog-dev libgflags-dev libatlas-base-dev libeigen3-dev libsuitesparse-dev

# For prophesee OpenEB except for libopencv-dev
# ref: https://github.com/prophesee-ai/openeb
RUN apt install -y \
  apt-utils build-essential software-properties-common wget unzip curl git cmake \
  googletest libgtest-dev libboost-all-dev libusb-1.0-0-dev \
  libglew-dev libglfw3-dev libcanberra-gtk-module ffmpeg

ENV CMAKE_VERSION=3.24.3
RUN echo "check_certificate = off" >> ~/.wgetrc &&\
 wget -O cmake.sh https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION}/cmake-${CMAKE_VERSION}-Linux-x86_64.sh &&\
 chmod +x cmake.sh &&\
 bash cmake.sh --prefix=/usr/local --exclude-subdir &&\
 rm cmake.sh

ENV CERES_VERSION=1.14.0
RUN cd ~ &&\
 git config --global http.sslverify false &&\
 git clone https://ceres-solver.googlesource.com/ceres-solver &&\
 cd ceres-solver &&\
 git checkout ${CERES_VERSION} &&\
 mkdir build && cd build &&\
 cmake .. &&\
 make -j$(nproc) install && ldconfig &&\
 rm -rf ~/ceres-solver

ENV LANG=C.UTF-8 \
    LC_ALL=C.UTF-8 \
    ROS_DISTRO=noetic
RUN sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list' &&\
 curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | apt-key add - &&\
 apt update &&\
 apt install -y ros-${ROS_DISTRO}-desktop-full

RUN echo "source /opt/ros/noetic/setup.bash" >> ~/.bashrc &&\
#  . ~/.bashrc &&\
 apt-get install --no-install-recommends -y \
  python3-rosdep python3-rosinstall python3-rosinstall-generator \
  python3-wstool python3-vcstools build-essential software-properties-common &&\
 rosdep init && rosdep update --rosdistro ${ROS_DISTRO}

# # Install OpenCV
# RUN export OPENCV_VERSION=3.4.18 &&\
#  cd ~ && git config --global http.sslverify false &&\
#  git clone https://github.com/opencv/opencv.git --branch ${OPENCV_VERSION} --single-branch &&\
#  git clone https://github.com/opencv/opencv_contrib.git --branch ${OPENCV_VERSION} --single-branch &&\
#  cd opencv &&\
#  mkdir build && cd build &&\
#  # atmost packages will be detected automatically
#  cmake \
#   -D CMAKE_BUILD_TYPE=RELEASE \
#   -D CMAKE_INSTALL_PREFIX=/usr/local \
#   -D OPENCV_ENABLE_NONFREE=ON \
#   -D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib/modules \
#   .. &&\
#  make -j$(nproc) install && ldconfig &&\
#  rm -rf ~/opencv*

# Install ccache
RUN cd ~ && git clone https://github.com/ccache/ccache.git &&\
 cd ccache && git checkout v4.6 -b 4.6 &&\
 mkdir build && cd build &&\
 cmake \
  -DZSTD_FROM_INTERNET=ON \
  -DHIREDIS_FROM_INTERNET=ON \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_INSTALL_PREFIX=/usr/local \
  .. &&\
 make -j$(nproc) install &&\
 cd && rm -rf ccache
