FROM nvidia/cudagl:11.1.1-devel-ubuntu20.04

## Notice! If you use WSL2, set "export LIBGL_ALWAYS_INDIRECT=0"
RUN export DEBIAN_FRONTEND=noninteractive

# Install OpenCV & Ceres Dependencies
RUN cd ~ &&\
 apt-key adv --fetch-keys https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2004/x86_64/3bf863cc.pub &&\
 apt update && apt dist-upgrade -y

RUN export DEBIAN_FRONTEND=noninteractive &&\
 apt install -y --allow-downgrades --allow-change-held-packages --no-install-recommends \
  build-essential wget curl cmake unzip git vim openssh-server openssh-client \
  gfortran libprotobuf-dev protobuf-compiler \
  libblas-dev liblapack-dev liblapacke-dev libfmt-dev tzdata dirmngr gnupg2 \
  libjpeg-dev libpng-dev libtiff-dev libtbb-dev libgtk2.0-dev mesa-utils libgl1-mesa-glx pkg-config \
  ffmpeg libavcodec-dev libavformat-dev libswscale-dev libxvidcore-dev libx264-dev libxine2-dev \
  libgflags-dev libatlas-base-dev libsuitesparse-dev libeigen3-dev &&\
 echo "export LIBGL_ALWAYS_INDIRECT=1" >> /root/.bashrc &&\
 apt-get clean && apt-get autoremove -y &&\
 rm -rf /var/lib/apt/lists/*


# Install Ceres
RUN cd ~ &&\
 apt update &&\
 apt install -y --no-install-recommends libgflags-dev libgoogle-glog-dev &&\
 export CERES_VERSION=2.1.0 &&\
 git config --global http.sslverify false &&\
 git clone https://ceres-solver.googlesource.com/ceres-solver &&\
 cd ceres-solver &&\
 git checkout ${CERES_VERSION} &&\
 mkdir build && cd build &&\
 cmake .. &&\
 make -j$(nproc) install && ldconfig &&\
 rm -rf ~/ceres-solver

RUN echo 'Etc/UTC' > /etc/timezone &&\
 apt-get install -q -y --no-install-recommends tzdata dirmngr gnupg2

RUN apt install -y lsb-release &&\
 echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros1-latest.list &&\
 apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654 &&\
 export LANG=C.UTF-8 LC_ALL=C.UTF-8 &&\
 apt-get update &&\
 apt-get install -y --no-install-recommends ros-noetic-desktop-full

RUN \
 apt-get install --no-install-recommends -y \
  python3-dev \
  python3-pip \
  python3-rosdep \
  python3-rosinstall \
  python3-rosinstall-generator \
  python3-wstool \
  python3-vcstool \
  python3-vcstools \
  python3-catkin-tools \
  software-properties-common \
  bash-completion&&\
 rosdep init && rosdep update --rosdistro noetic

# RUN apt-get update &&\
#  apt-get install -y --no-install-recommends ros-noetic-robot &&\
#  apt-get install -y --no-install-recommends ros-noetic-desktop &&\
#  apt-get install -y --no-install-recommends ros-noetic-desktop-full
#  rm -rf /var/lib/apt/lists/*

##################
# Install OpenCV #
##################
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
