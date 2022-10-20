# This Image already includes cudatoolkit 10.2 & cudnn 7
FROM nvidia/cuda:11.0.3-cudnn8-runtime-ubuntu18.04

RUN apt-get update \
  && apt-get install -y ssh \
    build-essential \
    gcc \
    g++ \
    gdb \
    clang \
    cmake \
    rsync \
    tar \
    python \
    apt-utils\
    git\
    curl\
    vim\
    cmake\
    pkg-config\
    unzip\
    yasm\
    checkinstall\
    iptables &&\
    apt-get clean && apt-get autoremove -y

# This line makes {user==leecw} can get Container's root authorization. Replace 1234 to your password.
RUN useradd -m leecw && yes 1234 | passwd leecw


# OpenCV Dependency
ENV PYTHON_VERSION=3.6
RUN apt-get update &&\
    apt-get install -y --allow-downgrades --allow-change-held-packages --no-install-recommends\
        libjpeg-dev libpng-dev libtiff-dev\
        libavcodec-dev libavformat-dev libswscale-dev libavresample-dev\
        libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev\
        libxvidcore-dev x264 libx264-dev libfaac-dev libmp3lame-dev libtheora-dev\
        libfaac-dev libmp3lame-dev libvorbis-dev\
        libopencore-amrnb-dev libopencore-amrwb-dev\
        libdc1394-22 libdc1394-22-dev libxine2-dev libv4l-dev v4l-utils &&\
        cd /usr/include/linux &&\
        ln -s -f ../libv4l1-videodev.h videodev.h &&\
        cd ~ &&\
    apt-get install -y --allow-downgrades --allow-change-held-packages --no-install-recommends\
        libgtk-3-dev\
        python3 python3-dev python3-pip &&\
    pip3 install -U pip setuptools &&\
    pip --no-cache-dir install -U future wheel protobuf typing numpy &&\
    apt-get install -y --allow-downgrades --allow-change-held-packages --no-install-recommends\
        libtbb-dev\
        libatlas-base-dev gfortran\
        libprotobuf-dev protobuf-compiler\
        libgoogle-glog-dev libgflags-dev\
        libgphoto2-dev libeigen3-dev libhdf5-dev doxygen &&\
    apt-get clean && apt-get autoremove -y


# Install opencv
ARG OPENCV_VERSION=3.4.13
RUN cd /opt/ &&\
    git clone https://github.com/opencv/opencv.git --branch ${OPENCV_VERSION} --single-branch &&\
    git clone https://github.com/opencv/opencv_contrib.git --branch ${OPENCV_VERSION} --single-branch &&\
    cd opencv &&\
    mkdir build &&\
    cd build &&\
    cmake \
        -DCMAKE_BUILD_TYPE=RELEASE \
        -DOPENCV_EXTRA_MODULES_PATH=/opt/opencv_contrib/modules \
        -DCMAKE_INSTALL_PREFIX=/usr/local \
        -DOPENCV_ENABLE_NONFREE=ON \
        -DWITH_CUDA=ON \
        -DENABLE_FAST_MATH=ON \
        -DCUDA_FAST_MATH=ON \
        -DWITH_CUBLAS=ON \
        .. &&\
    make -j$(nproc) &&\
    make install &&\
    ldconfig &&\
    cd &&\
    rm -rf /opt/opencv*
    
# 시작 작업디렉토리를 지정
WORKDIR "/home"