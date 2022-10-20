# This Image already includes cudatoolkit 10.2 & cudnn 7
FROM ubuntu:bionic

# Installing basic useful packages in Ubuntu and Converting Python Setting from 3.6 to 3.7
RUN apt-get update && apt-get upgrade -y &&\
    apt-get install -y\
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

# Install OpenCV without CUDA
ARG OPENCV_VERSION=3.4.13
RUN cd ~ &&\
    git clone https://github.com/opencv/opencv.git --branch ${OPENCV_VERSION} --single-branch &&\
    git clone https://github.com/opencv/opencv_contrib.git --branch ${OPENCV_VERSION} --single-branch &&\
    cd opencv &&\
    mkdir build &&\
    cd build &&\
    cmake -D CMAKE_BUILD_TYPE=RELEASE \
        -D CMAKE_INSTALL_PREFIX=/usr/local \
        -D WITH_TBB=ON \
        -D ENABLE_FAST_MATH=ON \
        -D WITH_V4L=ON \
        -D WITH_QT=OFF \
        -D WITH_OPENGL=ON \
        -D WITH_OPENCL=ON \
        -D OPENCV_ENABLE_NONFREE=ON \
        -D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib/modules \
        -D BUILD_EXAMPLES=ON .. &&\
    make -j"$(nproc)" && \
    make install && \
    ldconfig && \
    rm -rf ~/opencv*