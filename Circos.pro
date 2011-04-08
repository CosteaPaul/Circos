#-------------------------------------------------
#
# Project created by QtCreator 2011-03-28T12:49:47
#
#-------------------------------------------------

QT       += core gui

TARGET = Circos
TEMPLATE = app


SOURCES += main.cpp\
        circosmain.cpp \
    wimage.cpp \
    scircossession.cpp \
    ITranslatable.cpp

HEADERS  += circosmain.h \
    ITranslatable.h \
    wimage.h \
    scircossession.h

FORMS    += circosmain.ui \
    wimage.ui
