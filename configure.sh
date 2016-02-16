#!/bin/sh

#Required dependencies - if you know you already have this installed feel free to skip it
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"


git submodule init
git submodule update

cd src/libraries/hidapi
cp hidapi/hidapi.h mac/hidapi.h
./bootstrap
./configure
make
make install
cd ../..

make
cp inkling_broadcaster ../inkling_broadcaster
rm inkling_broadcaster