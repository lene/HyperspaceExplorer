#! /bin/sh

aclocal && \
automake --gnu && \
autoconf && \
./configure && \
make 2>&1 && \
( cd src; ./HyperspaceExplorer )