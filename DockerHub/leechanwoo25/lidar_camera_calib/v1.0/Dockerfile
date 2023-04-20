FROM nvidia/cudagl:11.1.1-devel-ubuntu18.04

## Notice! If you use WSL2, set "export LIBGL_ALWAYS_INDIRECT=0"

# Install OpenCV & Ceres Dependencies
RUN export DEBIAN_FRONTEND=noninteractive && cd ~ &&\
 # For fixing broken cuda apt package list
 apt-key adv --fetch-keys https://developer.download.nvidia.com/compute/cuda/repos/ubuntu1804/x86_64/3bf863cc.pub &&\
 apt update && apt dist-upgrade -y &&\
 apt install -y --allow-downgrades --allow-change-held-packages --no-install-recommends \
  build-essential wget curl unzip git vim openssh-server openssh-client \
  gfortran libprotobuf-dev protobuf-compiler \
  libblas-dev liblapack-dev liblapacke-dev libfmt-dev tzdata dirmngr gnupg2 \
  libjpeg-dev libpng-dev libtiff-dev libtbb-dev libgtk2.0-dev mesa-utils libgl1-mesa-glx pkg-config \
  ffmpeg libavcodec-dev libavformat-dev libswscale-dev libxvidcore-dev libx264-dev libxine2-dev \
  libgflags-dev libatlas-base-dev libsuitesparse-dev &&\
 echo "export LIBGL_ALWAYS_INDIRECT=1" >> /root/.bashrc &&\
 apt-get clean && apt-get autoremove -y &&\
 rm -rf /var/lib/apt/lists/*

# Install CMake
RUN export CMAKE_VERSION=3.24.3 DEBIAN_FRONTEND=noninteractive &&\
 echo "check_certificate = off" >> ~/.wgetrc &&\
 wget -O cmake.sh https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION}/cmake-${CMAKE_VERSION}-Linux-x86_64.sh &&\
 chmod +x cmake.sh &&\
 bash cmake.sh --prefix=/usr/local --exclude-subdir &&\
 rm cmake.sh

# Install glog
RUN cd ~ &&\
 export GLOG_VERSION=v0.6.0 &&\
 git config --global http.sslverify false &&\
 git clone https://github.com/google/glog.git --single-branch -b ${GLOG_VERSION} &&\
 cd glog &&\
 mkdir build && cd build &&\
 cmake .. &&\
 make -j8 install && ldconfig &&\
 cd ~ && rm -rf glog

# Install Eigen
RUN cd &&\
 export EIGEN_VERSION=3.3.9 &&\
 git clone -b ${EIGEN_VERSION} --single-branch https://gitlab.com/libeigen/eigen.git &&\
 cd eigen &&\
 mkdir build && cd build &&\
 cmake .. && make -j8 install && ldconfig && \
 cd && rm -rf eigen

# Install Ceres
RUN cd ~ &&\
 export CERES_VERSION=1.14.0 &&\
 git config --global http.sslverify false &&\
 git clone https://ceres-solver.googlesource.com/ceres-solver &&\
 cd ceres-solver &&\
 git checkout ${CERES_VERSION} &&\
 mkdir build && cd build &&\
 cmake .. &&\
 make -j$(nproc) install && ldconfig &&\
 rm -rf ~/ceres-solver

## Install ROS
RUN echo 'Etc/UTC' > /etc/timezone &&\
#  ln -s /usr/share/zoneinfo/Etc/UTC /etc/localtime &&\
 apt-get update &&\
 apt-get install -q -y --no-install-recommends tzdata dirmngr gnupg2 &&\
 rm -rf /var/lib/apt/lists/*
RUN echo "deb http://packages.ros.org/ros/ubuntu bionic main" > /etc/apt/sources.list.d/ros1-latest.list &&\
 apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654
ENV LANG=C.UTF-8 LC_ALL=C.UTF-8 ROS_DISTRO=melodic
RUN apt-get update &&\
 apt-get install -y --no-install-recommends ros-melodic-ros-core=1.4.1-0* &&\
 apt-get install --no-install-recommends -y python-rosdep python-rosinstall python-vcstools &&\
 rm -rf /var/lib/apt/lists/* &&\
 rosdep init && rosdep update --rosdistro $ROS_DISTRO
RUN apt-get update &&\
 apt-get install -y --no-install-recommends ros-melodic-robot=1.4.1-0* &&\
#  apt-get install -y --no-install-recommends ros-melodic-desktop=1.4.1-0* &&\
#  apt-get install -y --no-install-recommends ros-melodic-desktop-full=1.4.1-0* &&\
 rm -rf /var/lib/apt/lists/*
RUN apt-get update &&\
 apt-get install -y --no-install-recommends \
  python-catkin-tools \
  python-vcstool \
  software-properties-common &&\
 rm -rf /var/lib/apt/lists/*

## Install OpenCV
# RUN export OPENCV_VERSION=3.4.16 &&\
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

## Install ccache
# RUN cd ~ && git clone https://github.com/ccache/ccache.git &&\
#  cd ccache && git checkout v4.6 -b 4.6 &&\
#  mkdir build && cd build &&\
#  cmake \
#   -DZSTD_FROM_INTERNET=ON \
#   -DHIREDIS_FROM_INTERNET=ON \
#   -DCMAKE_BUILD_TYPE=Release \
#   -DCMAKE_INSTALL_PREFIX=/usr/local \
#   .. &&\
#  make -j$(nproc) install &&\
#  cd && rm -rf ccache

RUN apt-get update &&\
 apt-get install -y --no-install-recommends \
  ros-melodic-cv-bridge \
  ros-melodic-tf \
  ros-melodic-message-filters \
  ros-melodic-image-transport* &&\
 rm -rf /var/lib/apt/lists/*

## Install Livox SDK
RUN cd ~ &&\
 git clone https://github.com/Livox-SDK/Livox-SDK.git &&\
 cd Livox-SDK &&\
 cd build && cmake .. && make -j4 install &&\
 cd ~ & rm -rf Livox-SDK

## PCL dependency
RUN apt-get update &&\
 apt-get install -y --no-install-recommends \
  ros-melodic-pcl-ros libcgal-dev pcl-tools &&\
 rm -rf /var/lib/apt/lists/*

## Install Livox ROS Driver
RUN cd ~ && mkdir -p ws_livox/src && cd ws_livox/src &&\
 git clone https://github.com/Livox-SDK/livox_ros_driver.git &&\
 . /opt/ros/melodic/setup.sh &&\
 cd .. && catkin_make

## Clone R3Live
# cd ~/catkin_ws/src
# git clone https://github.com/hku-mars/r3live.git
# cd ../
# catkin_make
# source ~/catkin_ws/devel/setup.bash
