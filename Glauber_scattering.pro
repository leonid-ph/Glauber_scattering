#-------------------------------------------------
#
# Project created by QtCreator 2015-03-29T20:49:48
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Glauber_scattering
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    glauber.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    glauber.h

FORMS    += mainwindow.ui

RESOURCES += \
    resourses.qrc
