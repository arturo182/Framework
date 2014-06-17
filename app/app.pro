include(../framework.pri)
include(../libs/libs.pri)

QT            += core gui widgets printsupport
TARGET        = Framework
DESTDIR       = ../bin
TEMPLATE      = app

SOURCES      += main.cpp\
		mainwindow.cpp \
		scene.cpp \
		componentlist.cpp \
		componentmimedata.cpp \
	componenttree.cpp \
	plugindialog.cpp \
	commands.cpp

HEADERS      += mainwindow.h \
		scene.h \
		componentlist.h \
		componentmimedata.h \
	componenttree.h \
	plugindialog.h \
	commands.h

FORMS	     += mainwindow.ui \
	plugindialog.ui

RESOURCES    += res/res.qrc
