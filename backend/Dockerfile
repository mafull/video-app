# docker build . -t video-app
# docker run --rm -it video-app

## STAGE 1 ##

FROM cpp-build-base AS build

WORKDIR /src

COPY CMakeLists.txt src/* ./

RUN cmake . && make


## STAGE 2 ##

# Ideally, run from base Ubuntu - currently get a linker error
# https://askubuntu.com/questions/575505/glibcxx-3-4-20-not-found-how-to-fix-this-error
# FROM ubuntu:bionic
FROM cpp-build-base

WORKDIR /opt/video-app

COPY --from=build /src/video-app ./

EXPOSE 8080
# CMD ["/bin/bash"]
CMD ["websocketd", "-devconsole", "--port=8080", "./video-app"]
# CMD ["websocketd", "--port=8080", "./video-app"]
