#-------------------------------------------------
#
# Project created by QtCreator 2017-05-09T15:21:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PokerOld
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    aibehavior.cpp \
    aiplayer.cpp \
    dealer.cpp \
    diffmenu.cpp \
    hand.cpp \
    modern.cpp \
    modernai.cpp \
    noob.cpp \
    noobai.cpp \
    player.cpp \
    room.cpp \
    table.cpp \
    warning.cpp

HEADERS  += mainwindow.h \
    aibehavior.h \
    aiplayer.h \
    dealer.h \
    diffmenu.h \
    hand.h \
    modern.h \
    modernai.h \
    noob.h \
    noobai.h \
    player.h \
    room.h \
    table.h \
    warning.h

FORMS    += mainwindow.ui \
    diffmenu.ui

RESOURCES += \
    myres.qrc
