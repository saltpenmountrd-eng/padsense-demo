QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET   = ConstructionSample
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

unix:  DEFINES += UNICODE _UNICODE
win32: DEFINES += UNICODE _UNICODE

SOURCES += \
    main.cpp \
    widget.cpp \
    machinewidget.cpp

HEADERS += \
    widget.h \
    machinewidget.h
