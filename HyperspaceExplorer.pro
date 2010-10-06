TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS = src tests main

src.path = .
main.path = ./main
tests.path = ./tests

INSTALLS += src main tests
