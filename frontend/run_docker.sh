#!/usr/bin/env bash
set -e
docker build -t video-app-frontend .
clear
docker run --rm -it \
    -p 3000:3000 \
    -v ${PWD}/src:/app/src \
    video-app-frontend

