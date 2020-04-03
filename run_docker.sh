#!/usr/bin/env bash
set -e
docker build --rm -t video-app:latest .
clear
docker run --rm -it \
    -v /Users/max.fuller/Pictures:/usr/pictures \
    video-app:latest "$@"
