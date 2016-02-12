#-------------------------------------------------
#
# Project created by QtCreator 2013-12-11T18:22:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Project_5
TEMPLATE = app


SOURCES += main.cpp\
        uiboundary.cpp \
    Filer/ZigBeeIF_out.cpp \
    Filer/ZigBeeIF_in.cpp \
    Filer/UIController.cpp \
    Filer/SettingsController.cpp \
    Filer/Mobile.cpp \
    Filer/MeasurementsController.cpp \
    Filer/ManualController.cpp \
    Filer/Cradle.cpp \
    Filer/AutomaticController.cpp

HEADERS  += uiboundary.h \
    Filer/ZigBeeIF_out.hpp \
    Filer/ZigBeeIF_in.hpp \
    Filer/UIController.hpp \
    Filer/SettingsController.hpp \
    Filer/Settings.hpp \
    Filer/Mobile.hpp \
    Filer/MeasurementsController.hpp \
    Filer/ManualController.hpp \
    Filer/Cradle.hpp \
    Filer/common.hpp \
    Filer/AutomaticController.hpp

FORMS    += uiboundary.ui

OTHER_FILES +=
