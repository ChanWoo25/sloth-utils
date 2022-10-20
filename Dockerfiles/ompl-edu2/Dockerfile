FROM nvidia/cuda:11.0.3-runtime-ubuntu18.04


# Install the basic(1/2) packages for Ubuntu 18.04
RUN apt-get update &&\
    apt-get install -y --allow-downgrades --allow-change-held-packages --no-install-recommends \
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
    wget\
    unzip &&\
    apt-get clean && apt-get autoremove -y

# Install the basic(2/2) packages for Ubuntu 18.04 (a little bit optional ones)
RUN apt-get update &&\
    apt-get install -y \
    rsync\
    python\
    yasm\
    checkinstall\
    doxygen\
    xorg-dev\
    libglew-dev\
    libgl1-mesa-glx\
    pypy pypy-dev &&\
    apt-get clean && apt-get autoremove -y


RUN wget https://ompl.kavrakilab.org/core/install-ompl-ubuntu.sh &&\
    chmod u+x install-ompl-ubuntu.sh &&\
    ./install-ompl-ubuntu.sh --app --python &&\
    rm install-ompl-ubuntu.sh

# This line makes {user==leecw} can get Container's root authorization. Replace 1234 to your password.
RUN useradd -m leecw && yes light25 | passwd leecw

# Configure Container's Default Working Directory
WORKDIR "/root"