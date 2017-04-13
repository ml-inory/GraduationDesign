#-------------------------------------------------
#
# Project created by QtCreator 2017-04-11T11:34:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ev_face
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -pedantic

SOURCES += main.cpp\
        mainwindow.cpp \
    ../../src/Cap_Controller.cpp

HEADERS  += mainwindow.h \
    ../build-ev_face-Desktop_Qt_5_6_2_GCC_64bit-Debug/ui_mainwindow.h \
    ../../include/Cap_Controller.hpp \
    ../../include/Seetaface.hpp

INCLUDEPATH += ../../include/ \
               /usr/local/include/ \
               /usr/include/glog/   \
               /home/inory/SeetaFaceEngine/FaceDetection/include    \
               /home/inory/SeetaFaceEngine/FaceAlignment/include

LIBS += -L/usr/local/lib/ -lopencv_core -lopencv_highgui -lopencv_videoio -lopencv_imgproc \
        -L/usr/lib/x86_64-linux-gnu/ -lglog \
        -L../ev_face/lib/ -lseeta_facedet_lib -lseeta_fa_lib

FORMS    += mainwindow.ui
