#-------------------------------------------------
#
# Project created by QtCreator 2016-07-25T22:02:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sans_titre1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mouseevent.cpp \
    board.cpp \
    boardmouseevent.cpp \
    player.cpp \
    firstpage.cpp \
    optionpage.cpp \
    promotion.cpp

HEADERS  += mainwindow.h \
    mouseevent.h \
    board.h \
    boardmouseevent.h \
    player.h \
    firstpage.h \
    lcdnumber.h \
    optionpage.h \
    promotion.h

FORMS    += mainwindow.ui \
    firstpage.ui \
    optionpage.ui \
    promotion.ui

DISTFILES +=

RESOURCES += \
    resources.qrc
