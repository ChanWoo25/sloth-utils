###########################################
# Base image
###########################################
FROM leechanwoo25/melodic_cuda:base

ENV DEBIAN_FRONTEND=noninteractive

# Install dev tools
RUN apt-get update && apt-get install -y \
    software-properties-common \
    python-catkin-tools \
    python-vcstool \
    python-rosdep \
    python-rosinstall \
    python-rosinstall-generator \
    python-wstool \
    python-pip \
    python-pep8 \
    python-autopep8 \
    pylint \
    build-essential \
    bash-completion \
  && rm -rf /var/lib/apt/lists/* \
  && rosdep init || echo "rosdep already initialized"

# Install the full release
RUN apt-get update && apt-get install -y \
  ros-melodic-desktop \
  && rm -rf /var/lib/apt/lists/*
ENV DEBIAN_FRONTEND=
