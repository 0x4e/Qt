#-------------------------------------------------
#
# Project created by QtCreator 2016-07-09T12:34:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = wavereader
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Array.cpp \
    Collection.cpp \
    FileIO.cpp \
    Options.cpp \
    Options_private.cpp \
    qcustomplot.cpp \
    soundfilehelpers.cpp \
    SoundFileRead.cpp \
    SoundFileWrite.cpp \
    SoundHeader.cpp \
    kiss_fft.c \
    CustomPlotZoom.cpp

HEADERS  += mainwindow.h \
    Array.h \
    Collection.h \
    FileIO.h \
    Options.h \
    Options_private.h \
    qcustomplot.h \
    sigConfiguration.h \
    soundfile.h \
    soundfilehelpers.h \
    SoundFileRead.h \
    SoundFileWrite.h \
    SoundHeader.h \
    kiss_fft.h \
    CustomPlotZoom.h

FORMS    += mainwindow.ui
