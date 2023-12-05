FROM nvidia/cudagl:11.3.1-devel-ubuntu20.04

# Tips
# - If you use WSL2, set 'export LIBGL_ALWAYS_INDIRECT=0' into '~/.bashrc'
# - Otherwise, set 'export LIBGL_ALWAYS_INDIRECT=1' into '~/.bashrc'
ENV DEBIAN_FRONTEND=noninteractive

# Install OpenCV & Ceres Dependencies
RUN cd ~ &&\
 apt-key adv --fetch-keys https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2004/x86_64/3bf863cc.pub &&\
 apt update && apt dist-upgrade -y &&\
 echo "export LIBGL_ALWAYS_INDIRECT=1" >> /root/.bashrc &&\
 apt clean && apt autoremove -y &&\
 rm -rf /var/lib/apt/lists/*

RUN cd ~ &&\
 apt install -y --allow-downgrades --allow-change-held-packages --no-install-recommends \
  lsb-release wget curl vim git unzip software-properties-common \
  openssh-server openssh-client \
  build-essential cmake ninja-build pkg-config \
  gfortran gnupg gnupg2 libprotobuf-dev protobuf-compiler &&\
 apt clean && apt autoremove -y &&\
 rm -rf /var/lib/apt/lists/*

# For various packages dependency (ex: opencv & pcl)
RUN cd ~ &&\
 apt install -y --allow-downgrades --allow-change-held-packages --no-install-recommends \
  libeigen3-dev libflann-dev libboost-all-dev \
  libblas-dev liblapack-dev liblapacke-dev libfmt-dev tzdata dirmngr  \
  libjpeg-dev libpng-dev libtiff-dev libtbb-dev libgtk2.0-dev mesa-utils libgl1-mesa-glx  \
  ffmpeg libavcodec-dev libavformat-dev libswscale-dev libxvidcore-dev libx264-dev libxine2-dev \
  libatlas-base-dev libsuitesparse-dev \
  tzdata dirmngr &&\
 apt clean && apt autoremove -y &&\
 rm -rf /var/lib/apt/lists/*

# Install Clang & Clangd
# - version 10 is default for Ubuntu 20.04
RUN cd ~ &&\
 wget https://apt.llvm.org/llvm.sh &&\
 chmod +x llvm.sh && ./llvm.sh 10 &&\
 apt update && apt install -y clang clangd &&\
 echo "export CC=/usr/bin/clang"    >> ~/.bashrc &&\
 echo "export CXX=/usr/bin/clang++" >> ~/.bashrc &&\
 source ~/.bashrc &&\
 apt clean && apt autoremove -y &&\
 rm -rf /var/lib/apt/lists/*

RUN cd ~ &&\
 echo 'Etc/UTC' > /etc/timezone &&\
 echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros1-latest.list &&\
 apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654 &&\
 export LANG=C.UTF-8 LC_ALL=C.UTF-8 &&\
 apt update &&\
 apt install -y --no-install-recommends ros-noetic-desktop-full &&\
 apt clean && apt autoremove -y &&\
 rm -rf /var/lib/apt/lists/*

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

# Install Latest version of FMT
RUN cd ~ &&\
 export FMT_VERSION=10.1.1 &&\
 git clone --single-branch -b ${FMT_VERSION} https://github.com/fmtlib/fmt.git  &&\
 cd fmt && cmake -B build && cd build && make -j6 install &&\
 rm -rf ~/fmt

# Install Miniconda3
# - If you wanna initialize, do "~/miniconda3/bin/conda init bash && source ~/.bashrc"
# - Checkout "https://stackoverflow.com/questions/54429210/how-do-i-prevent-conda-from-activating-the-base-environment-by-default"
RUN cd ~ &&\
 mkdir -p ~/miniconda3 &&\
 wget https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh -O ~/miniconda3/miniconda.sh &&\
 bash ~/miniconda3/miniconda.sh -b -u -p ~/miniconda3 &&\
 rm -rf ~/miniconda3/miniconda.sh
#  echo "auto_activate_base: false" >> ~/.condarc

# Unset Envs
ENV DEBIAN_FRONTEND=

# Install Ceres
# RUN cd ~ &&\
#  apt update &&\
#  apt install -y --no-install-recommends libgflags-dev libgoogle-glog-dev &&\
#  export CERES_VERSION=2.1.0 &&\
#  git config --global http.sslverify false &&\
#  git clone https://ceres-solver.googlesource.com/ceres-solver &&\
#  cd ceres-solver &&\
#  git checkout ${CERES_VERSION} &&\
#  mkdir build && cd build &&\
#  cmake .. &&\
#  make -j$(nproc) install && ldconfig &&\
#  rm -rf ~/ceres-solver

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
