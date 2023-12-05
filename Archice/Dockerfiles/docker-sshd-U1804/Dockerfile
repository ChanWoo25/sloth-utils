ARG BASE_IMAGE=ubuntu:18.04
# -----------------

FROM ${BASE_IMAGE}

LABEL AUTHOR="Chanwoo Lee" EMAIL="leechanwoo25@gmail.com" \
      Description="Image for accessing docker container on ubuntu server"

RUN apt-get update \
&& apt-get install -y openssh-server net-tools \
&& apt-get clean \
&& rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/* \
&& mkdir /var/run/sshd \
&& mkdir /root/.ssh

# Set your root password by '1234'
RUN echo 'root:root'|chpasswd

# Properly set "sshd_config"
RUN sed -ri 's/^#?PermitRootLogin\s+.*/PermitRootLogin yes/' /etc/ssh/sshd_config
# RUN sed -ri 's/UsePAM yes/# UsePAM yes/g' /etc/ssh/sshd_config

EXPOSE 22

CMD ["/usr/sbin/sshd", "-D"]
