include(../framework.pri)

TARGET        = libs
DESTDIR       = $$BIN_PATH
TEMPLATE      = lib
CONFIG	     += dll
QT			 += core gui widgets

DEFINES      += LIBRARY

HEADERS	     += wire.h \
		pinitem.h \
		outputpin.h \
		inputpin.h \
		global.h \
		component.h \
		componentitem.h \
		componentplugin.h

SOURCES	     += wire.cpp \
		pinitem.cpp \
		outputpin.cpp \
		inputpin.cpp \
		component.cpp \
		componentitem.cpp \
		componentplugin.cpp
