# https://github.com/DavidAStevenson/cpp-helloworld-docker
FROM ubuntu:latest


# https://solarianprogrammer.com/2017/12/14/clang-in-docker-container-cpp-17-development/
RUN apt-get update && apt-get install -y \
    xz-utils \
    build-essential \
    curl \
    libc++1 \
&& rm -rf /var/lib/apt/lists/* \
&& curl -SL http://releases.llvm.org/9.0.0/clang+llvm-9.0.0-x86_64-linux-gnu-ubuntu-18.04.tar.xz | tar -xJC . \
&& mv clang+llvm-9.0.0-x86_64-linux-gnu-ubuntu-18.04 clang_9.0.0 \
&& echo 'export PATH=/clang_9.0.0/bin:$PATH' >> /root/.bashrc \
&& echo 'export LD_LIBRARY_PATH=/clang_9.0.0/lib:$LD_LIBRARY_PATH' >> /root/.bashrc

    #clang \
    #clang-format \
    #clang-tidy

COPY . /usr/src/video-app
WORKDIR /usr/src/video-app

SHELL ["/bin/bash", "-c"]
RUN source ~/.bashrc
# RUN clang-tidy src/* -- \
#     -std=c++17
RUN /clang_9.0.0/bin/clang++ \
    -std=c++17 \
    -stdlib=libc++ \
    -I src \
    src/*.cpp

CMD ["./a.out"]
# CMD ["/bin/bash"]
# CMD ["clang-tidy", "src/Test.cpp", "--", "-std=c++17", "&&", "cat", "src/Test.cpp"]
# CMD ["clang-format", "-i", "src/Test.cpp", "&&", "ls"]
#"src/Test.cpp"]
