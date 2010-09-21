TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS = src main tests

src.path = .
main.path = ./main
tests.path = ./tests

INSTALLS += src main tests

