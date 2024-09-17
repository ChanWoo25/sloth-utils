#! /bin/bash
# Ref: https://github.com/antonmedv/countdown

export VERSION=1.0.0
wget https://github.com/antonmedv/countdown/releases/download/v1.0.0/countdown_linux_amd64 -O countdown
chmod +x countdown
sudo mv countdown /usr/local/bin
