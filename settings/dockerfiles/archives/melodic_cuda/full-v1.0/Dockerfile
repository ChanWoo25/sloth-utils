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

# Install Eigen
RUN cd &&\
 export EIGEN_VERSION=3.3.9 &&\
 git clone -b ${EIGEN_VERSION} --single-branch https://gitlab.com/libeigen/eigen.git &&\
 cd eigen &&\
 mkdir build && cd build &&\
 cmake .. && make -j8 install && ldconfig && \
 cd && rm -rf eigen

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

ARG USERNAME=leecw
ARG USER_UID=1000
ARG USER_GID=$USER_UID

# Create a non-root user
ENV DEBIAN_FRONTEND=noninteractive
RUN groupadd --gid $USER_GID $USERNAME \
  && useradd -s /bin/bash --uid $USER_UID --gid $USER_GID -m $USERNAME \
  # [Optional] Add sudo support for the non-root user
  && apt-get update \
  && apt-get install -y sudo git-core bash-completion \
  && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME\
  && chmod 0440 /etc/sudoers.d/$USERNAME \
  # Cleanup
  && rm -rf /var/lib/apt/lists/* \
  && echo "if [ -f /opt/ros/${ROS_DISTRO}/setup.bash ]; then source /opt/ros/${ROS_DISTRO}/setup.bash; fi" >> /home/$USERNAME/.bashrc
ENV DEBIAN_FRONTEND=
