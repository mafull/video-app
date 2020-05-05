# docker build -f base.Dockerfile . -t cpp-build-base

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

# websocketd
RUN apt-get install -y \
        unzip \
        wget && \
    wget -q -O /tmp/websocketd.zip https://github.com/joewalnes/websocketd/releases/download/v0.3.0/websocketd-0.3.0-linux_amd64.zip && \
    unzip /tmp/websocketd.zip -d /tmp/websocketd && \
    mv /tmp/websocketd/websocketd /usr/bin

# OpenCV
# https://docs.opencv.org/master/d7/d9f/tutorial_linux_install.html
# http://www.codebind.com/linux-tutorials/install-opencv-ubuntu-18-04-lts-c-cpp-linux/
RUN apt-get install -y \
        build-essential \
        cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev \
        python-dev python-numpy && \
        #libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev && \
    cd /opt && \
    git clone https://github.com/opencv/opencv.git && \
    git clone https://github.com/opencv/opencv_contrib.git && \
    cd opencv && \
    mkdir release && cd release && \
    cmake BUILD_TIFF=ON -D WITH_CUDA=OFF -D ENABLE_AVX=OFF -D WITH_OPENGL=OFF -D WITH_OPENCL=OFF -D WITH_IPP=OFF -D WITH_TBB=ON -D BUILD_TBB=ON -D WITH_EIGEN=OFF -D WITH_V4L=OFF -D WITH_VTK=OFF -D BUILD_TESTS=OFF -D BUILD_PERF_TESTS=OFF -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D OPENCV_EXTRA_MODULES_PATH=/opt/opencv_contrib/modules .. && \
    make -j4 && \
    make install

CMD ["/bin/bash"]
