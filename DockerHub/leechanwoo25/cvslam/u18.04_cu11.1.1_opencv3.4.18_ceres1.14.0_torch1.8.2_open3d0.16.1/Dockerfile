FROM nvidia/cudagl:11.1.1-devel-ubuntu18.04

# Install OpenCV & Ceres Dependencies
ENV DEBIAN_FRONTEND=noninteractive
RUN cd ~ &&\
 apt-key adv --fetch-keys https://developer.download.nvidia.com/compute/cuda/repos/ubuntu1804/x86_64/3bf863cc.pub &&\
#  apt update && apt install wget &&\
#  wget https://developer.download.nvidia.com/compute/cuda/repos/ubuntu1804/x86_64/cuda-keyring_1.0-1_all.deb &&\
#  dpkg -i cuda-keyring_1.0-1_all.deb &&\
#  sed -i '/developer\.download\.nvidia\.com\/compute\/cuda\/repos/d' /etc/apt/sources.list.d/* &&\
#  sed -i '/developer\.download\.nvidia\.com\/compute\/machine-learning\/repos/d' /etc/apt/sources.list.d/* &&\
 apt update && apt dist-upgrade -y &&\
 apt install -y --allow-downgrades --allow-change-held-packages --no-install-recommends \
  build-essential wget curl unzip git vim openssh-server openssh-client \
  gfortran libprotobuf-dev protobuf-compiler \
  libblas-dev liblapack-dev liblapacke-dev \
  libjpeg-dev libpng-dev libtiff-dev libtbb-dev libgtk2.0-dev mesa-utils libgl1-mesa-glx pkg-config \
  ffmpeg libavcodec-dev libavformat-dev libswscale-dev libxvidcore-dev libx264-dev libxine2-dev \
  libgoogle-glog-dev libgflags-dev libatlas-base-dev libeigen3-dev libsuitesparse-dev &&\
 export "export LIBGL_ALWAYS_INDIRECT=1" >> /root/.bashrc &&\
 apt-get clean && apt-get autoremove -y &&\
 rm -rf /var/lib/apt/lists/*

ARG CMAKE_VERSION=3.24.3 DEBIAN_FRONTEND=noninteractive
RUN wget -O cmake.sh https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION}/cmake-${CMAKE_VERSION}-Linux-x86_64.sh &&\
 chmod +x cmake.sh &&\
 bash cmake.sh --prefix=/usr/local --exclude-subdir &&\
 rm cmake.sh

# Install Ceres
ARG CERES_VERSION=1.14.0
RUN cd ~ \
&&  git config --global http.sslverify false \
&&  git clone https://ceres-solver.googlesource.com/ceres-solver \
&&  cd ceres-solver \
&&  git checkout ${CERES_VERSION} \
&&  mkdir build && cd build \
&&  cmake .. \
&&  make -j$(nproc) install && ldconfig \
&&  rm -rf ~/ceres-solver

# Install OpenCV
ARG OPENCV_VERSION=3.4.18
RUN cd ~ \
&&  git config --global http.sslverify false \
&&  git clone https://github.com/opencv/opencv.git --branch ${OPENCV_VERSION} --single-branch \
&&  git clone https://github.com/opencv/opencv_contrib.git --branch ${OPENCV_VERSION} --single-branch \
&&  cd opencv \
&&  mkdir build && cd build \
# atmost packages will be detected automatically
&&  cmake -D CMAKE_BUILD_TYPE=RELEASE \
        -D CMAKE_INSTALL_PREFIX=/usr/local \
        -D OPENCV_ENABLE_NONFREE=ON \
        -D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib/modules \
        .. \
&&  make -j$(nproc) install && ldconfig \
&&  rm -rf ~/opencv*

# Install Python 3 & Pytorch
RUN cd ~ \
&&  apt update \
&&  apt install -y --allow-downgrades --allow-change-held-packages --no-install-recommends \
      python3-dev python3-pip python3-setuptools vlc &&\
 python3 -m pip install --upgrade pip &&\
 python3 -m pip install --upgrade pillow &&\
 python3 -m pip install wheel numpy pandas seaborn scipy matplotlib &&\
 python3 -m pip install torch==1.8.2 torchvision==0.9.2 torchaudio==0.8.2 --extra-index-url https://download.pytorch.org/whl/lts/1.8/cu111 &&\
 apt-get clean && apt-get autoremove -y &&\
 rm -rf /var/lib/apt/lists/*

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

# Install Open3D
ARG OPEN3D_VERSION=v0.16.1
RUN cd ~ && apt update &&\
 apt install -y --allow-downgrades --allow-change-held-packages --no-install-recommends \
  # Open3D
  xorg-dev libxcb-shm0 libglu1-mesa-dev python3-dev \
  # Filament build-from-source
  clang-7 libc++-7-dev libc++abi-7-dev \
  libsdl2-dev ninja-build libxi-dev \
  # Headless rendering
  libosmesa6-dev &&\
 git config --global http.sslverify false &&\
 git clone https://github.com/isl-org/Open3D --branch ${OPEN3D_VERSION} --single-branch &&\
 cd Open3D && mkdir build && cd build &&\
 cmake \
  -DBUILD_PYTHON_MODULE=ON \
  -DPython3_ROOT=/usr/bin/python3 \
  -DCMAKE_INSTALL_PREFIX=/root/open3d_install \
  -DBUILD_SHARED_LIBS=ON \
  .. &&\
 make install -j $(nproc) &&\
 make install-pip-package &&\
 cd && rm -rf Open3D &&\
 apt-get clean && apt-get autoremove -y &&\
 rm -rf /var/lib/apt/lists/*
 # After install this, refer here "https://github.com/isl-org/open3d-cmake-find-package" to link open3d libs with your project

### CMake OpenCV Configuration Output should like below ...
# -- General configuration for OpenCV 3.4.18 =====================================
# --   Version control:               3.4.18
# --
# --   Platform:
# --     Timestamp:                   2022-10-20T05:30:07Z
# --     Host:                        Linux 5.15.0-48-generic x86_64
# --     CMake:                       3.16.3
# --     CMake generator:             Unix Makefiles
# --     CMake build tool:            /usr/bin/make
# --     Configuration:               RELEASE
# --
# --   CPU/HW features:
# --     Baseline:                    SSE SSE2 SSE3
# --       requested:                 SSE3
# --     Dispatched code generation:  SSE4_1 SSE4_2 FP16 AVX AVX2 AVX512_SKX
# --       requested:                 SSE4_1 SSE4_2 AVX FP16 AVX2 AVX512_SKX
# --       SSE4_1 (16 files):         + SSSE3 SSE4_1
# --       SSE4_2 (2 files):          + SSSE3 SSE4_1 POPCNT SSE4_2
# --       FP16 (1 files):            + SSSE3 SSE4_1 POPCNT SSE4_2 FP16 AVX
# --       AVX (6 files):             + SSSE3 SSE4_1 POPCNT SSE4_2 AVX
# --       AVX2 (30 files):           + SSSE3 SSE4_1 POPCNT SSE4_2 FP16 FMA3 AVX AVX2
# --       AVX512_SKX (7 files):      + SSSE3 SSE4_1 POPCNT SSE4_2 FP16 FMA3 AVX AVX2 AVX_512F AVX512_COMMON AVX512_SKX
# --
# --   C/C++:
# --     Built as dynamic libs?:      YES
# --     C++11:                       YES
# --     C++ Compiler:                /usr/bin/c++  (ver 9.4.0)
# --     C++ flags (Release):         -fsigned-char -W -Wall -Wreturn-type -Wnon-virtual-dtor -Waddress -Wsequence-point -Wformat -Wformat-security -Wmissing-declarations -Wundef -Winit-self -Wpointer-arith -Wshadow -Wsign-promo -Wuninitialized -Wsuggest-override -Wno-delete-non-virtual-dtor -Wno-comment -Wimplicit-fallthrough=3 -Wno-strict-overflow -fdiagnostics-show-option -Wno-long-long -pthread -fomit-frame-pointer -ffunction-sections -fdata-sections  -msse -msse2 -msse3 -fvisibility=hidden -fvisibility-inlines-hidden -O3 -DNDEBUG  -DNDEBUG
# --     C++ flags (Debug):           -fsigned-char -W -Wall -Wreturn-type -Wnon-virtual-dtor -Waddress -Wsequence-point -Wformat -Wformat-security -Wmissing-declarations -Wundef -Winit-self -Wpointer-arith -Wshadow -Wsign-promo -Wuninitialized -Wsuggest-override -Wno-delete-non-virtual-dtor -Wno-comment -Wimplicit-fallthrough=3 -Wno-strict-overflow -fdiagnostics-show-option -Wno-long-long -pthread -fomit-frame-pointer -ffunction-sections -fdata-sections  -msse -msse2 -msse3 -fvisibility=hidden -fvisibility-inlines-hidden -g  -O0 -DDEBUG -D_DEBUG
# --     C Compiler:                  /usr/bin/cc
# --     C flags (Release):           -fsigned-char -W -Wall -Wreturn-type -Waddress -Wsequence-point -Wformat -Wformat-security -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Winit-self -Wpointer-arith -Wshadow -Wuninitialized -Wno-comment -Wimplicit-fallthrough=3 -Wno-strict-overflow -fdiagnostics-show-option -Wno-long-long -pthread -fomit-frame-pointer -ffunction-sections -fdata-sections  -msse -msse2 -msse3 -fvisibility=hidden -O3 -DNDEBUG  -DNDEBUG
# --     C flags (Debug):             -fsigned-char -W -Wall -Wreturn-type -Waddress -Wsequence-point -Wformat -Wformat-security -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Winit-self -Wpointer-arith -Wshadow -Wuninitialized -Wno-comment -Wimplicit-fallthrough=3 -Wno-strict-overflow -fdiagnostics-show-option -Wno-long-long -pthread -fomit-frame-pointer -ffunction-sections -fdata-sections  -msse -msse2 -msse3 -fvisibility=hidden -g  -O0 -DDEBUG -D_DEBUG
# --     Linker flags (Release):      -Wl,--exclude-libs,libippicv.a -Wl,--exclude-libs,libippiw.a   -Wl,--gc-sections -Wl,--as-needed -Wl,--no-undefined
# --     Linker flags (Debug):        -Wl,--exclude-libs,libippicv.a -Wl,--exclude-libs,libippiw.a   -Wl,--gc-sections -Wl,--as-needed -Wl,--no-undefined
# --     ccache:                      NO
# --     Precompiled headers:         NO
# --     Extra dependencies:          dl m pthread rt
# --     3rdparty dependencies:
# --
# --   OpenCV modules:
# --     To be built:                 calib3d core dnn features2d flann highgui imgcodecs imgproc ml objdetect photo python3 shape stitching superres ts video videoio videostab
# --     Disabled:                    world
# --     Disabled by dependency:      -
# --     Unavailable:                 cudaarithm cudabgsegm cudacodec cudafeatures2d cudafilters cudaimgproc cudalegacy cudaobjdetect cudaoptflow cudastereo cudawarping cudev java python2 viz
# --     Applications:                tests perf_tests apps
# --     Documentation:               NO
# --     Non-free algorithms:         YES
# --
# --   GUI:
# --     GTK+:                        YES (ver 2.24.32)
# --       GThread :                  YES (ver 2.64.6)
# --       GtkGlExt:                  NO
# --     VTK support:                 NO
# --
# --   Media I/O:
# --     ZLib:                        /usr/lib/x86_64-linux-gnu/libz.so (ver 1.2.11)
# --     JPEG:                        /usr/lib/x86_64-linux-gnu/libjpeg.so (ver 80)
# --     WEBP:                        build (ver encoder: 0x020f)
# --     PNG:                         /usr/lib/x86_64-linux-gnu/libpng.so (ver 1.6.37)
# --     TIFF:                        /usr/lib/x86_64-linux-gnu/libtiff.so (ver 42 / 4.1.0)
# --     JPEG 2000:                   build (ver 1.900.1)
# --     OpenEXR:                     build (ver 2.3.0)
# --     HDR:                         YES
# --     SUNRASTER:                   YES
# --     PXM:                         YES
# --
# --   Video I/O:
# --     DC1394:                      NO
# --     FFMPEG:                      YES
# --       avcodec:                   YES (ver 58.54.100)
# --       avformat:                  YES (ver 58.29.100)
# --       avutil:                    YES (ver 56.31.100)
# --       swscale:                   YES (ver 5.5.100)
# --       avresample:                NO
# --     GStreamer:                   NO
# --     libv4l/libv4l2:              NO
# --     v4l/v4l2:                    linux/videodev2.h
# --
# --   Parallel framework:            pthreads
# --
# --   Trace:                         YES (with Intel ITT)
# --
# --   Other third-party libraries:
# --     Intel IPP:                   2020.0.0 Gold [2020.0.0]
# --            at:                   /root/opencv/build/3rdparty/ippicv/ippicv_lnx/icv
# --     Intel IPP IW:                sources (2020.0.0)
# --               at:                /root/opencv/build/3rdparty/ippicv/ippicv_lnx/iw
# --     Lapack:                      YES (/usr/lib/x86_64-linux-gnu/liblapack.so /usr/lib/x86_64-linux-gnu/libcblas.so /usr/lib/x86_64-linux-gnu/libatlas.so)
# --     Eigen:                       YES (ver 3.3.7)
# --     Custom HAL:                  NO
# --     Protobuf:                    build (3.5.1)
# --
# --   OpenCL:                        YES (no extra features)
# --     Include path:                /root/opencv/3rdparty/include/opencl/1.2
# --     Link libraries:              Dynamic load
# --
# --   Python 3:
# --     Interpreter:                 /usr/bin/python3 (ver 3.8.10)
# --     Libraries:                   /usr/lib/x86_64-linux-gnu/libpython3.8.so (ver 3.8.10)
# --     numpy:                       /usr/local/lib/python3.8/dist-packages/numpy/core/include (ver 1.23.3)
# --     install path:                lib/python3.8/site-packages/cv2/python-3.8
# --
# --   Python (for build):            /usr/bin/python3
# --
# --   Java:
# --     ant:                         NO
# --     JNI:                         NO
# --     Java wrappers:               NO
# --     Java tests:                  NO
# --
# --   Install to:                    /usr/local
# -- -----------------------------------------------------------------
# --
# -- Configuring done
# -- Generating done
# -- Build files have been written to: /root/opencv/build
