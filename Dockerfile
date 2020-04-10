# docker build . -t video-app:0.1.0
# docker run --rm -it video-app:0.1.0

## STAGE 1 ##

FROM cpp-build-base:0.1.0 AS build

WORKDIR /src

COPY CMakeLists.txt src/* ./

RUN cmake . && make


## STAGE 2 ##

# Idelaly, run from base Ubuntu - currently get a linker error
# https://askubuntu.com/questions/575505/glibcxx-3-4-20-not-found-how-to-fix-this-error
# FROM ubuntu:bionic
FROM cpp-build-base:0.1.0

WORKDIR /opt/video-app

COPY --from=build /src/video-app ./

CMD ["./video-app"]
