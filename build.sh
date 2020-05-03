#!/bin/sh

pwd=$(pwd)

if [ "$1" = "--with-eigen" ]; then
  eigenBuild=$pwd/src/eigen/build
  mkdir -p $eigenBuild
  cd src/eigen/build
  cmake ../
  sudo make install
fi

projectBuild=$pwd/build

mkdir -p $projectBuild
cd $projectBuild
cmake ../
make all -j7
cd $pwd
