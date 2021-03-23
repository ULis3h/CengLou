QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += multimedia
QT += multimediawidgets
QT += axcontainer
QT += serialport
QT += core gui network


CONFIG += c++11
CONFIG += console

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


INCLUDEPATH+=d:/opencv/build/include/opencv \
                    d:/opencv/build/include/opencv2 \
                   d:/opencv/build/include
LIBS+=D:\opencv\build\x64\vc14\lib\opencv_world345.lib
LIBS+=D:\opencv\build\x64\vc14\lib\opencv_world345d.lib



SOURCES += \
    about.cpp \
    main.cpp \
    mainwindow.cpp \
    yawinf.cpp

HEADERS += \
    about.h \
    mainwindow.h \
    yawinf.h

FORMS += \
    about.ui \
    mainwindow.ui \
    yawinf.ui


RC_ICONS = ic.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
