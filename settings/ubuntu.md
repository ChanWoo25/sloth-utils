# Ubuntu initial settigns

## Ubuntu 24.04

```bash
# 1. Default
sudo apt update && sudo apt dist-upgrade -y
sudo apt install -y build-essential cmake ninja-build wget curl git ncdu tree htop btop vim exfat-fuse lsb-release
#! /bin/bash

sudo apt update
sudo apt dist-upgrade -y
sudo apt install fcitx-hangul

-----------------------------

leecw@leecw:~$ sudo apt install build-essential cmake ninja-build wget curl git ncdu tree htop btop vim exfat-fuse lsb-release
Reading package lists... Done
Building dependency tree... Done
Reading state information... Done
wget is already the newest version (1.21.4-1ubuntu4.1).
wget set to manually installed.
lsb-release is already the newest version (12.0-2).
lsb-release set to manually installed.


```


## Ubuntu 20.04

```shell
sudo apt-get update &&
sudo apt-get dist-upgrade -y &&
sudo apt-get -y autoremove &&
sudo apt-get clean
sudo apt-get install -y nvidia-driver-470 fcitx-hangul
```

### Install language pkgs & set fcitx & Reboot

```shell
sudo apt install -y git wget curl build-essential cmake ninja-build exfat-* &&
sudo apt -y autoremove &&
git config --global user.email "leechanwoo25@gmail.com" &&
git config --global user.name "Chanwoo Lee" &&
ssh-keygen
```

### Additional

- Download & Install Chrome & Sync
- Download & Install Visual Studio Code at [Web Site](https://code.visualstudio.com/download)

## For Ubuntu 18.04

```shell
sudo apt update && sudo apt dist-upgrade -y &&
sudo apt -y autoremove &&
echo "blacklist nouveau modeset=0" >> blacklist-nouveau.conf &&
rm blacklist-nouveau.conf &&
echo "blacklist nouveau" >> blacklist-nouveau.conf &&
echo "options nouveau modeset=0" >> blacklist-nouveau.conf &&
sudo mv blacklist-nouveau.conf /etc/modprobe.d &&
sudo update-initramfs -u
```

> REBOOT and THEN

```shell
sudo apt install -y nvidia-driver-440 fcitx-hangul &&
sudo apt -y autoremove
// Do langauge install
```

> REBOOT and THEN

```shell
sudo apt install -y git wget build-essential ninja-build exfat-fuse exfat-utils &&
sudo apt -y autoremove &&
git config --global user.email "leechanwoo25@gmail.com" &&
git config --global user.name "Chanwoo Lee" &&
wget -O cmake.sh https://github.com/Kitware/CMake/releases/download/v3.20.3/cmake-3.20.3-linux-x86_64.sh &&
chmod +x cmake.sh &&
sudo bash cmake.sh --prefix=/usr/local --exclude-subdir &&
rm cmake.sh
```

## For Ubuntu 20.04
```shell
# No need to touch nouveau-stuffs.
sudo apt update &&
sudo apt dist-upgrade -y &&
sudo apt install -y nvidia-driver-470 fcitx-hangul
```
> Install language pkgs & Reboot
```shell
sudo apt install -y git wget build-essential cmake ninja-build exfat-* &&
sudo apt -y autoremove &&
git config --global user.email "leechanwoo25@gmail.com" &&
git config --global user.name "Chanwoo Lee"
```

---
Second, Download Visual Studio Code at [Web Site](https://code.visualstudio.com/download)
```shell
sudo dpkg -i ~/Downloads/code_xxx.deb
sudo apt-get install -f
```
