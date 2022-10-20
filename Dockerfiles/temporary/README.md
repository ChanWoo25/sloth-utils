# Temporary sets

## cuDNN debian package installing은 8부터 지원

```Dockerfile
RUN export OS=ubuntu1804 cudnn_version=7.6.5 cuda_version=cuda10.2 \
&& wget https://developer.download.nvidia.com/compute/cuda/repos/${OSx86_64/cuda-${OS}.pin \
&& mv cuda-${OS}.pin /etc/apt/preferences.d/cuda-repository-pin-600 \
&& apt-key adv --fetch-keys https://developer.download.nvidia.com/computcuda/repos/${OS}/x86_64/7fa2af80.pub \
&& add-apt-repository "deb https://developer.download.nvidia.com/computcuda/repos/${OS}/x86_64/ /" \
&& apt-get update \
&& apt-get install libcudnn7=${cudnn_version}-1+${cuda_version} \
&& apt-get install libcudnn7-dev=${cudnn_version}-1+${cuda_version}
```
