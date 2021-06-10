QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Easy_Coins
TEMPLATE = app

CONFIG += c++1z

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        easy.cpp \
        loading.cpp \
        main.cpp \
        drawer.cpp \
        maps.cpp

HEADERS += \
    drawer.h \
    easy.h \
    loading.h \
    maps.h

