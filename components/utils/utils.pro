include(../../framework.pri)
include(../../libs/libs.pri)

TARGET    = utils
DESTDIR   = $$COMPONENT_PATH
TEMPLATE  = lib
CONFIG	 += dll
QT		 += core gui widgets

HEADERS  += plugin.h \
	label.h

SOURCES  += plugin.cpp \
	label.cpp
