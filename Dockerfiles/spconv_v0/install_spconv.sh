#! /bin/bash

# Install cudnn 7.6.5
cd /root/Archive/cudnn-10.2-linux-x64-v7.6.5.32
cp cuda/include/cudnn.h /usr/local/cuda/include
cp cuda/lib64/libcudnn* /usr/local/cuda/lib64
chmod a+r /usr/local/cuda/include/cudnn.h /usr/local/cuda/lib64/libcudnn*

# Install spconv
git clone --single-branch -b v1.2.1  https://github.com/traveller59/spconv.git
cd spconv
git submodule update --init --recursive
python3.7 setup.py bdist_wheel
cd ./dist
python3.7  -m pip install spconv-1.2.1-*.whl
cd ../..

# Install BtcDet
git clone https://github.com/Xharlie/BtcDet.git
cd BtcDet
python3.7 setup.py develop
