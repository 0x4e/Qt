TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Array.cpp \
    Collection.cpp \
    FileIO.cpp \
    Options.cpp \
    Options_private.cpp \
    soundfilehelpers.cpp \
    SoundFileRead.cpp \
    SoundFileWrite.cpp \
    SoundHeader.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    Array.h \
    Collection.h \
    FileIO.h \
    Options.h \
    Options_private.h \
    sigConfiguration.h \
    soundfile.h \
    soundfilehelpers.h \
    SoundFileRead.h \
    SoundFileWrite.h \
    SoundHeader.h

