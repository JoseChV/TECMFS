#-------------------------------------------------
#
# Project created by QtCreator 2018-11-23 T9:03:55
#
#-------------------------------------------------
#Se debe agregar el mulmedia
QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = videogui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    oddyseyconsulta.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
