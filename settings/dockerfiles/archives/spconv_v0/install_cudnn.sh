#! /bin/bash

cd /root/Archive/cudnn-10.2-linux-x64-v7.6.5.32
cp cuda/include/cudnn.h /usr/local/cuda/include
cp cuda/lib64/libcudnn* /usr/local/cuda/lib64
chmod a+r /usr/local/cuda/include/cudnn.h /usr/local/cuda/lib64/libcudnn*
cd ~
