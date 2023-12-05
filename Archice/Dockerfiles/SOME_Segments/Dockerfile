FROM ubuntu:18.04

# Install the basic(1/2) packages for Ubuntu 18.04
RUN apt-get update &&\
    apt-get install -y \
    apt-utils\
    pkg-config\
    ssh\
    gcc\
    g++\
    gdb\
    clang\
    build-essential\
    git\
    curl\
    cmake\
    tar\
    vim\
    unzip &&\
    apt-get clean && apt-get autoremove -y

# Install the basic(2/2) packages for Ubuntu 18.04 (a little bit optional ones)
RUN apt-get update &&\
    apt-get install -y \
    rsync\
    python\
    yasm\
    checkinstall &&\
    apt-get clean && apt-get autoremove -y

# Install latest 3.18.4 version of CMake Library
RUN wget -O cmake.sh https://github.com/Kitware/CMake/releases/download/v3.18.4/cmake-3.18.4-Linux-x86_64.sh &&\
    bash cmake.sh --prefix=/usr/local --exclude-subdir &&\
    rm cmake.sh