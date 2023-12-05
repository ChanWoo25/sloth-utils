# Cuda Toolkit version is following pytorch 1.8.2 LTS Version.
FROM nvidia/cudagl:11.1.1-devel-ubuntu18.04

# For fixing broken cuda apt package list
ARG DEBIAN_FRONTEND=noninteractive
RUN apt-key adv --fetch-keys https://developer.download.nvidia.com/compute/cuda/repos/ubuntu1804/x86_64/3bf863cc.pub &&\
    apt update && apt dist-upgrade -y &&\
    apt autoremove -y && apt clean

RUN apt install -y --allow-downgrades --allow-change-held-packages --no-install-recommends \
      build-essential wget curl unzip git vim openssh-server openssh-client \
      libgflags-dev vlc pkg-config \
      gfortran libprotobuf-dev protobuf-compiler \
      libblas-dev liblapack-dev liblapacke-dev \
      libfmt-dev tzdata dirmngr gnupg2 \
      libjpeg-dev libpng-dev libtiff-dev libtbb-dev libgtk2.0-dev \
      ffmpeg libavcodec-dev libavformat-dev libswscale-dev \
      libxvidcore-dev libx264-dev libxine2-dev \
      libatlas-base-dev libsuitesparse-dev \
      mesa-utils libgl1-mesa-glx freeglut3-dev libglfw3-dev libglew-dev  &&\
    apt autoremove -y && apt clean

# Install CMake version 3.16 or higher is required to build glog v0.6.0
ARG CMAKE_VERSION=3.24.3
RUN echo "check_certificate = off" >> ~/.wgetrc &&\
    wget -O cmake.sh https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION}/cmake-${CMAKE_VERSION}-Linux-x86_64.sh &&\
    chmod +x cmake.sh &&\
    bash cmake.sh --prefix=/usr/local --exclude-subdir &&\
    rm cmake.sh

# Install glog
ARG GLOG_VERSION=v0.6.0
RUN git config --global http.sslverify false &&\
    git clone https://github.com/google/glog.git --single-branch -b ${GLOG_VERSION} &&\
    cd glog &&\
    mkdir build && cd build &&\
    cmake .. &&\
    make -j4 install && ldconfig &&\
    cd && rm -rf glog

# Install Eigen
ARG EIGEN_VERSION=3.4.0
RUN git clone -b ${EIGEN_VERSION} \
              --single-branch \
              https://gitlab.com/libeigen/eigen.git &&\
    cd eigen &&\
    mkdir build && cd build &&\
    cmake .. && make -j8 install && ldconfig && \
    cd && rm -rf eigen

# Install OpenCV
ARG OPENCV_VERSION=3.4.19
RUN git config --global http.sslverify false &&\
    git clone https://github.com/opencv/opencv.git --branch ${OPENCV_VERSION} --single-branch &&\
    git clone https://github.com/opencv/opencv_contrib.git --branch ${OPENCV_VERSION} --single-branch &&\
    cd opencv && mkdir build && cd build &&\
    cmake \
      -D CMAKE_BUILD_TYPE=RELEASE \
      -D CMAKE_INSTALL_PREFIX="/usr/local" \
      -D OPENCV_ENABLE_NONFREE=ON \
      -D OPENCV_EXTRA_MODULES_PATH="../../opencv_contrib/modules" \
      .. &&\
    make -j8 install && ldconfig &&\
    cd && rm -rf opencv*

RUN apt install -y \
      python3-dev python3-pip &&\
    apt autoremove -y && apt clean

RUN echo "export LIBGL_ALWAYS_INDIRECT=1" >> /root/.bashrc
