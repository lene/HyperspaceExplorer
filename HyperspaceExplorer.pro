TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS = src main tests

src.path = .
INSTALLS += src main tests