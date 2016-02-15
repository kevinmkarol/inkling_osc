#!/bin/sh

git submodule init
git submodule update

cd src/libraries/hidapi
./bootstrap
./configure
make
make install
cd ../..

make
cp inkling_broadcaster ../inkling_broadcaster
rm inkling_broadcaster