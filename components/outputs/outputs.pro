include(../../framework.pri)
include(../../libs/libs.pri)

TARGET    = outputs
DESTDIR   = $$COMPONENT_PATH
TEMPLATE  = lib
CONFIG	 += dll
QT		 += core gui widgets

HEADERS  += plugin.h \
		graph.h \
		digit.h

SOURCES  += plugin.cpp \
		graph.cpp \
		digit.cpp
