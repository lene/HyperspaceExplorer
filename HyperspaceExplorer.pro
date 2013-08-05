TEMPLATE = subdirs
CONFIG += ordered
QMAKE_CLEAN += Makefile
SUBDIRS = src tests main

src.path = .
main.path = ./main
tests.path = ./tests

INSTALLS += src main tests

