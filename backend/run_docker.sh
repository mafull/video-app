#!/usr/bin/env bash
set -e
docker build . -t video-app
clear
docker run --rm -it \
    -p 8080:8080 \
    -v /Users/max.fuller/Pictures:/usr/pictures \
    video-app "$@"
