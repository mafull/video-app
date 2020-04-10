# docker build -f base.Dockerfile . -t cpp-build-base:0.1.0

FROM ubuntu:bionic

RUN apt-get update && \
    apt-get install -y software-properties-common && \
    add-apt-repository ppa:ubuntu-toolchain-r/test && \
    apt-get install -y \
        build-essential \
        git \
        cmake \
        autoconf \
        libtool \
        pkg-config \
        gcc-9 \
        g++-9 && \
    update-alternatives \
        --install /usr/bin/gcc gcc /usr/bin/gcc-9 60 \
        --slave /usr/bin/g++ g++ /usr/bin/g++-9

# CMD ["/bin/bash"]
