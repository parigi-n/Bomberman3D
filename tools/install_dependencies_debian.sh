#!/bin/bash

ROOT_UID="0"
if [ "$UID" -ne "$ROOT_UID" ];
then
    echo "Please execute this script with root access"
    exit 1
fi

echo "Installing dependencies for debian based system"
apt-get install build-essential git cmake cmake-curses-gui doxygen xorg-dev libgl1-mesa-dev libudev-dev libglew-dev libjpeg-dev libopenal-dev libsndfile-dev libx11-dev libxcb1-dev libx11-xcb-dev libxcb-randr0-dev libxcb-image0-dev libflac-dev libvorbis-dev
