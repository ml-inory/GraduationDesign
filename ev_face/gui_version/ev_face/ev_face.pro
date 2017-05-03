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
    ../build/ui_mainwindow.h \
    ../../include/Cap_Controller.hpp \
    ../../include/Seetaface.hpp

SEETA_ROOT = /Users/rzyang/SeetaFaceEngine

FACE_DETECTION_ROOT = $${SEETA_ROOT}/FaceDetection
FACE_ALIGNMENT_ROOT = $${SEETA_ROOT}/FaceAlignment
FACE_ID_ROOT = $${SEETA_ROOT}/FaceIdentification

FACE_DETECTION_INCLUDE = $${FACE_DETECTION_ROOT}/include
FACE_ALIGNMENT_INCLUDE = $${FACE_ALIGNMENT_ROOT}/include
FACE_ID_INCLUDE = $${FACE_ID_ROOT}/include

FACE_DETECTION_LIB = $${FACE_DETECTION_ROOT}/build
FACE_ALIGNMENT_LIB = $${FACE_ALIGNMENT_ROOT}/build
FACE_ID_LIB = $${FACE_ID_ROOT}/build

INCLUDEPATH += ../../include/ \
               /usr/local/include/ \
               $${FACE_DETECTION_INCLUDE}    \
               $${FACE_ALIGNMENT_INCLUDE}   \
               $${FACE_ID_INCLUDE}

LIBS += -L/usr/local/lib/ -lopencv_core -lopencv_videoio -lopencv_imgproc \
        -L/usr/local/lib/ -lglog \
        -L$${FACE_DETECTION_LIB} -lseeta_facedet_lib \
        -L$${FACE_ALIGNMENT_LIB} -lseeta_fa_lib \
        -L$${FACE_ID_LIB} -lviplnet

FORMS    += mainwindow.ui
