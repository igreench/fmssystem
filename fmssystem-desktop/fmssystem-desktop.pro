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
    ui/gamewidget.cpp \
    game/cube.cpp

HEADERS  += ui/mainwindow.h \
    processing/abstractdataprocessor.h \
    processing/generatordataprocessor.h \
    processing/leapmotiondataprocessor.h \
    application.h \
    ui/gamewidget.h \
    game/cube.h

FORMS    += ui/mainwindow.ui
