#-------------------------------------------------
#
# Project created by QtCreator 2016-11-18T00:59:52
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fmssystem-desktop
TEMPLATE = app


SOURCES += main.cpp\
        ui/mainwindow.cpp \
    processing/abstractdataprocessor.cpp \
    processing/generatordataprocessor.cpp \
    processing/leapmotiondataprocessor.cpp \
    application.cpp \
    game/gamewidget.cpp

HEADERS  += ui/mainwindow.h \
    processing/abstractdataprocessor.h \
    processing/generatordataprocessor.h \
    processing/leapmotiondataprocessor.h \
    application.h \
    game/gamewidget.h

FORMS    += ui/mainwindow.ui
