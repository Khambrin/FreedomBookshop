#-------------------------------------------------
#
# Project created by QtCreator 2016-06-17T16:27:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FreedomBookshop
TEMPLATE = app


SOURCES += main.cpp \
        mainwindow.cpp \
    item.cpp \
    libro.cpp \
    dvd.cpp \
    scontrino.cpp \
    user.cpp \
    standard_user.cpp \
    premium_user.cpp \
    userlist.cpp \
    employee_user.cpp \
    database.cpp \
    prodottiview.cpp \
    databaseview.cpp \
    controller.cpp \
    utentiview.cpp \
    acquistiview.cpp

HEADERS  += mainwindow.h \
    item.h \
    libro.h \
    dvd.h \
    scontrino.h \
    user.h \
    standard_user.h \
    premium_user.h \
    userlist.h \
    employee_user.h \
    database.h \
    prodottiview.h \
    databaseview.h \
    controller.h \
    utentiview.h \
    acquistiview.h \
    errors.h

FORMS    += mainwindow.ui
