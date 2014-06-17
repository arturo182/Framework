include(../../framework.pri)
include(../../libs/libs.pri)

TARGET    = gates
DESTDIR   = $$COMPONENT_PATH
TEMPLATE  = lib
CONFIG	 += dll
QT		 += core gui widgets

HEADERS  += xorgate.h \
		xnorgate.h \
		orgate.h \
		notgate.h \
		norgate.h \
		nandgate.h \
		buffer.h \
		andgate.h \
		plugin.h

SOURCES  += xorgate.cpp \
		xnorgate.cpp \
		orgate.cpp \
		notgate.cpp \
		norgate.cpp \
		nandgate.cpp \
		buffer.cpp \
		andgate.cpp \
		plugin.cpp
