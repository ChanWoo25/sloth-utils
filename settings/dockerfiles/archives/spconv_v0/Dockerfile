ARG BASE_IMAGE=nvidia/cudagl:10.2-devel-ubuntu18.04
# -----------------

FROM ${BASE_IMAGE}

LABEL AUTHOR="Chanwoo Lee" EMAIL="leechanwoo25@gmail.com" \
      Description="Supports cuda 10.2 with OpenGL through libglvnd on Ubuntu 18.04. \
                  python 3.7.4 is installed for spconv dependency"

# Ignore user-interative warning while installing some packages
ENV DEBIAN_FRONTEND=noninteractive

# Note that cmake is installed seperately for latest one.
# Also install libboost-all-dev for spconv
RUN apt-get update && apt-get upgrade -y \
&& apt-get install -y --no-install-recommends \
  wget curl git unzip build-essential ninja-build git vim \
  lsb-release ca-certificates mesa-utils \
&& apt -y autoremove && apt clean \
&& rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

# Install recent version of cmake for spconv dependency
RUN cd ~ \
&& wget -O cmake.sh https://github.com/Kitware/CMake/releases/download/v3.22.2/cmake-3.22.2-linux-x86_64.sh \
&& chmod +x cmake.sh && bash cmake.sh --prefix=/usr/local --exclude-subdir \
&& rm cmake.sh

# Install python 3.7 and some requirements
# (for spconv, we need at least 3.7.x python version)
RUN apt-get update \
&& apt-get install -y --no-install-recommends \
  apt-utils libboost-all-dev \
  python3.7 python3.7-dev \
  python3-pip python3-setuptools libjpeg-dev zlib1g-dev \
&& apt -y autoremove && apt clean \
&& rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

# Install torch and other dependencies for spconv
RUN python3.7 -m pip install wheel \
&& python3.7 -m pip install -U pip wheel setuptools \
&& python3.7 -m pip install \
  torch==1.8.2+cu102 torchvision==0.9.2+cu102 \
  torchaudio==0.8.2 -f https://download.pytorch.org/whl/lts/1.8/torch_lts.html \
&& python3.7 -m pip install Pillow numba tensorboardX easydict pyyaml scikit-image tqdm


      # set up thread number for building
RUN apt-get update && apt-get install -y \
  libatlas-base-dev \
  libeigen3-dev \
  libsuitesparse-dev \
  python-catkin-tools \
  ros-${ROS_DISTRO}-cv-bridge \
  ros-${ROS_DISTRO}-image-transport \
  ros-${ROS_DISTRO}-message-filters \
  ros-${ROS_DISTRO}-tf && \
  rm -rf /var/lib/apt/lists/* && \
  # Build and install Ceres
  git clone https://ceres-solver.googlesource.com/ceres-solver && \
  cd ceres-solver && \
  git checkout tags/${CERES_VERSION} && \
  mkdir build && cd build && \
  cmake .. && \
  make -j$(USE_PROC) install && \
  rm -rf ../../ceres-solver && \
  mkdir -p $CATKIN_WS/src/VINS-Mono/


WORKDIR /root
