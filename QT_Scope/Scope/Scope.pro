#-------------------------------------------------
#
# Project created by QtCreator 2017-10-12T19:43:23
#
#-------------------------------------------------

QT       += core gui
QT       += network
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport


TARGET = Scope
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    CustomPlotZoom.cpp \
    qcustomplot.cpp \
    kiss_fft.c \
    circular_buffer.c \
    ADC_stream.cpp \
    packetinterface.cpp \
    utility.cpp

HEADERS  += mainwindow.h \
    CustomPlotZoom.h \
    kissfft.hh \
    kiss_fft.h \
    _kiss_fft_guts.h \
    qcustomplot.h \
    circular_buffer.h \
    ADC_stream.h \
    packetinterface.h \
    datatypes.h \
    utility.h

FORMS    += mainwindow.ui
