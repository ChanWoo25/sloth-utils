###########################################
# Base image
###########################################
FROM nvidia/cudagl:11.1.1-devel-ubuntu18.04

ENV DEBIAN_FRONTEND=noninteractive

# Install language
RUN apt-key adv --fetch-keys https://developer.download.nvidia.com/compute/cuda/repos/ubuntu1804/x86_64/3bf863cc.pub \
  && apt-get update && apt dist-upgrade -y \
  && apt install -y --allow-downgrades --allow-change-held-packages --no-install-recommends \
      build-essential cmake wget curl unzip git vim openssh-server openssh-client \
      gfortran libprotobuf-dev protobuf-compiler \
      libblas-dev liblapack-dev liblapacke-dev libfmt-dev tzdata dirmngr gnupg2 \
      libjpeg-dev libpng-dev libtiff-dev libtbb-dev libgtk2.0-dev mesa-utils libgl1-mesa-glx pkg-config \
      ffmpeg libavcodec-dev libavformat-dev libswscale-dev libxvidcore-dev libx264-dev libxine2-dev \
      libgflags-dev libgoogle-glog-dev libatlas-base-dev libsuitesparse-dev \
      locales libglvnd0 \
      libgl1 libglx0 libegl1 \
      libxext6 libx11-6 \
  && locale-gen en_US.UTF-8 \
  && update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8 \
  && rm -rf /var/lib/apt/lists/*

ENV LANG en_US.UTF-8
# Env vars for the nvidia-container-runtime.
ENV NVIDIA_VISIBLE_DEVICES all
ENV NVIDIA_DRIVER_CAPABILITIES graphics,utility,compute
ENV QT_X11_NO_MITSHM 1

# Install timezone
RUN ln -fs /usr/share/zoneinfo/UTC /etc/localtime \
  && export DEBIAN_FRONTEND=noninteractive \
  && apt-get update \
  && apt-get install -y tzdata \
  && dpkg-reconfigure --frontend noninteractive tzdata \
  && rm -rf /var/lib/apt/lists/*

# Install ROS
RUN apt-get update && apt-get install -y \
    curl \
    dirmngr \
    gnupg2 \
    lsb-release \
    sudo \
  && sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list' \
  && curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | apt-key add - \
  && apt-get update && apt-get install -y \
    ros-melodic-ros-base \
  && rm -rf /var/lib/apt/lists/*

# Setup environment
ENV LD_LIBRARY_PATH=/opt/ros/melodic/lib
ENV ROS_DISTRO=melodic
ENV ROS_ROOT=/opt/ros/melodic/share/ros
ENV ROS_PACKAGE_PATH=/opt/ros/melodic/share
ENV ROS_MASTER_URI=http://localhost:11311
ENV ROS_PYTHON_VERSION=
ENV ROS_VERSION=1
ENV PATH=/opt/ros/melodic/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
ENV ROSLISP_PACKAGE_DIRECTORIES=
ENV PYTHONPATH=/opt/ros/melodic/lib/python2.7/dist-packages
ENV PKG_CONFIG_PATH=/opt/ros/melodic/lib/pkgconfig
ENV ROS_ETC_DIR=/opt/ros/melodic/etc/ros
ENV CMAKE_PREFIX_PATH=/opt/ros/melodic
ENV DEBIAN_FRONTEND=
