# Cuda Toolkit version is following pytorch 1.8.2 LTS Version.
FROM nvidia/cudagl:11.1.1-devel-ubuntu20.04

# For fixing broken cuda apt package list
ARG DEBIAN_FRONTEND=noninteractive
RUN \
 apt-key adv --fetch-keys https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2004/x86_64/3bf863cc.pub &&\
 apt update && apt dist-upgrade -y &&\
 apt autoremove -y && apt clean

RUN \
 apt install -y --no-install-recommends \
  build-essential wget curl cmake unzip git vim openssh-server openssh-client \
  gfortran libprotobuf-dev protobuf-compiler \
  libgflags-dev libgoogle-glog-dev vlc pkg-config &&\
 apt autoremove -y && apt clean

RUN \
 apt install -y --no-install-recommends \
  python3-dev python3-pip python3-setuptools &&\
 apt autoremove -y && apt clean

RUN \
 apt install -y --no-install-recommends \
  freeglut3-dev libglfw3-dev libglew-dev &&\
 apt autoremove -y && apt clean

# RUN export DEBIAN_FRONTEND=noninteractive &&\
#  apt install -y --allow-downgrades --allow-change-held-packages --no-install-recommends \
#   build-essential wget curl cmake unzip git vim openssh-server openssh-client \
#   gfortran libprotobuf-dev protobuf-compiler \
#   libblas-dev liblapack-dev liblapacke-dev libfmt-dev tzdata dirmngr gnupg2 \
#   libjpeg-dev libpng-dev libtiff-dev libtbb-dev libgtk2.0-dev mesa-utils libgl1-mesa-glx \
#   ffmpeg libavcodec-dev libavformat-dev libswscale-dev libxvidcore-dev libx264-dev libxine2-dev

# RUN \
#  apt install -y --allow-downgrades --allow-change-held-packages --no-install-recommends \
#   libatlas-base-dev libsuitesparse-dev \
#   freeglut3-dev libglfw3-dev libglew-dev &&\
#  apt autoremove -y && apt clean

# Install Python 3 & Pytorch
RUN \
 pip3 install -U pip &&\
 pip3 install -U pillow wheel numpy pandas seaborn scipy matplotlib nbformat &&\
 pip3 install torch==1.8.2 torchvision==0.9.2 torchaudio==0.8.2 \
  --extra-index-url https://download.pytorch.org/whl/lts/1.8/cu111

# RUN echo "export LIBGL_ALWAYS_INDIRECT=1" >> /root/.bashrc &&\
#     echo "check_certificate = off" >> ~/.wgetrc
