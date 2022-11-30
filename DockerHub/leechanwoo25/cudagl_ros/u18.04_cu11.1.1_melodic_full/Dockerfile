FROM nvidia/cudagl:11.1.1-devel-ubuntu18.04

# Install OpenCV & Ceres Dependencies
RUN export DEBIAN_FRONTEND=noninteractive && cd ~ &&\
 # For fixing broken cuda apt package list
 apt-key adv --fetch-keys https://developer.download.nvidia.com/compute/cuda/repos/ubuntu1804/x86_64/3bf863cc.pub &&\
 apt update && apt dist-upgrade -y &&\
 apt install -y --allow-downgrades --allow-change-held-packages --no-install-recommends \
  build-essential wget curl unzip git vim openssh-server openssh-client \
  gfortran libprotobuf-dev protobuf-compiler \
  libblas-dev liblapack-dev liblapacke-dev \
  libjpeg-dev libpng-dev libtiff-dev libtbb-dev libgtk2.0-dev mesa-utils libgl1-mesa-glx pkg-config \
  ffmpeg libavcodec-dev libavformat-dev libswscale-dev libxvidcore-dev libx264-dev libxine2-dev \
  libgoogle-glog-dev libgflags-dev libatlas-base-dev libeigen3-dev libsuitesparse-dev &&\
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

RUN echo 'Etc/UTC' > /etc/timezone &&\
 ln -s /usr/share/zoneinfo/Etc/UTC /etc/localtime &&\
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
 apt-get install -y --no-install-recommends ros-melodic-desktop=1.4.1-0* &&\
 apt-get install -y --no-install-recommends ros-melodic-desktop-full=1.4.1-0* &&\
 rm -rf /var/lib/apt/lists/*


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

# # Install Python 3 & Pytorch
# RUN cd ~ && apt update &&\
#  apt install -y --allow-downgrades --allow-change-held-packages --no-install-recommends \
#   python3-dev python3-pip python3-setuptools vlc &&\
#  python3 -m pip install --upgrade pip &&\
#  python3 -m pip install --upgrade pillow wheel numpy pandas seaborn scipy matplotlib nbformat &&\
#  python3 -m pip install torch==1.8.2 torchvision==0.9.2 torchaudio==0.8.2 --extra-index-url https://download.pytorch.org/whl/lts/1.8/cu111 &&\
#  apt-get clean && apt-get autoremove -y &&\
#  rm -rf /var/lib/apt/lists/*

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

# # Install Open3D
# RUN export OPEN3D_VERSION=v0.16.1 &&\
#  cd ~ && apt update &&\
#  apt install -y --allow-downgrades --allow-change-held-packages --no-install-recommends \
#   # Open3D
#   xorg-dev libxcb-shm0 libglu1-mesa-dev \
#   # Filament build-from-source
#   clang-7 libc++-7-dev libc++abi-7-dev \
#   libsdl2-dev ninja-build libxi-dev \
#   # Headless rendering
#   libosmesa6-dev &&\
#  git config --global http.sslverify false &&\
#  git clone https://github.com/isl-org/Open3D --branch ${OPEN3D_VERSION} --single-branch &&\
#  cd Open3D && mkdir build && cd build &&\
#  cmake \
#   -DBUILD_PYTHON_MODULE=ON \
#   -DPython3_ROOT=/usr/bin/python3 \
#   -DCMAKE_INSTALL_PREFIX=/usr/local/open3d_install \
#   -DBUILD_SHARED_LIBS=ON \
#   .. &&\
#  make install -j $(nproc) &&\
#  apt-get clean && apt-get autoremove -y &&\
#  rm -rf /var/lib/apt/lists/*
#  # After install this, refer here "https://github.com/isl-org/open3d-cmake-find-package" to link open3d libs with your project
