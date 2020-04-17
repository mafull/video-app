#!/usr/bin/env bash
set -e
docker build . -t video-app:0.1.0
clear
docker run --rm -it \
    -v /Users/max.fuller/Pictures:/usr/pictures \
    video-app:0.1.0 "$@"
