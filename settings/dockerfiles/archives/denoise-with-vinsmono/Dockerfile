FROM nvidia/cudagl:10.2-devel-ubuntu16.04

LABEL AUTHOR="Chanwoo Lee" EMAIL="leechanwoo25@gmail.com" \
      Description="Supports cuda 10.2 with OpenGL through libglvnd on Ubuntu 16.04. \
                   Supports denoise-imu-gyro with python3.5"

# Ignore user-interative warning while installing some packages
ENV DEBIAN_FRONTEND=noninteractive \
    QT_X11_NO_MITSHM=1 \
    CERES_VERSION="1.12.0" \
    CATKIN_WS=/root/catkin_ws

# Install Basic packages +
# Install the latest cmake version & glog library
RUN apt-get update && apt-get -y upgrade && \
apt-get install -y --no-install-recommends \
  git wget curl unzip \
&& apt-get -y autoremove && apt clean \
&& rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

RUN cd && wget -O cmake.sh https://github.com/Kitware/CMake/releases/download/v3.22.2/cmake-3.22.2-linux-x86_64.sh \
&& chmod +x cmake.sh \
&& bash cmake.sh --prefix=/usr/local --exclude-subdir \
&& rm cmake.sh \
&& git clone https://github.com/google/glog.git \
&& cd glog && cmake -S . -B build -G "Unix Makefiles" \
&& cmake --build build && cmake --build build --target install \
&& cd .. && rm -rf glog

RUN sh -c 'echo "deb http://packages.ros.org/ros/ubuntu xenial main" > /etc/apt/sources.list.d/ros-latest.list' \
&& curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | apt-key add - \
&& apt-get update && apt-get install -y ros-kinetic-desktop \
&& echo "source /opt/ros/kinetic/setup.bash" >> ~/.bashrc \
&& apt-get install -y --no-install-recommends \
  python-rosdep python-rosinstall \
  python-rosinstall-generator python-wstool \
  libatlas-base-dev \
  libeigen3-dev \
  libsuitesparse-dev \
  python-catkin-tools \
  ros-kinetic-cv-bridge \
  ros-kinetic-image-transport \
  ros-kinetic-message-filters \
  ros-kinetic-tf \
&& rosdep init && rosdep update \
&& apt-get -y autoremove && apt clean \
&& rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

RUN cd /root \
&& git clone https://ceres-solver.googlesource.com/ceres-solver \
&& cd ceres-solver \
&& git checkout tags/${CERES_VERSION} \
&& mkdir build && cd build && cmake .. \
&& make && make install && cd /root && rm -rf ceres-solver

RUN apt-get update && apt-get install -y --no-install-recommends \
    python3 python3-dev python3-pip \
&& apt-get -y autoremove && apt clean \
&& rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

RUN python3 -m pip install --upgrade pip==20.3.4 \
&& python3 -m pip install -U wheel setuptools \
&& python3 -m pip install numpy torch==1.5.1 torchvision==0.6.1 \
  scipy matplotlib datetime termcolor pyyaml tensorboard

WORKDIR /root
