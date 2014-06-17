include(../../framework.pri)
include(../../libs/libs.pri)

TARGET    = inputs
DESTDIR   = $$COMPONENT_PATH
TEMPLATE  = lib
CONFIG	 += dll
QT		 += core gui widgets

HEADERS  += plugin.h \
		timer.h \
		switch.h \
		slider.h \
		mouse.h \
		button.h

SOURCES  += plugin.cpp \
		timer.cpp \
		switch.cpp \
		slider.cpp \
		mouse.cpp \
		button.cpp
