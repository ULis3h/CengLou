TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    cgetimg.cpp \
    cimgproc.cpp \
    ccallocal.cpp \
    cserial.cpp \
    cfacerec.cpp

INCLUDEPATH += /usr/local/include \
               /usr/local/include/opencv \
               /usr/local/include/opencv2
LIBS += /usr/local/lib/arm-linux-gnueabihf/libopencv_highgui.so \
        /usr/local/lib/arm-linux-gnueabihf/libopencv_core.so    \
        /usr/local/lib/arm-linux-gnueabihf/libopencv_imgproc.so \
        /usr/local/lib/arm-linux-gnueabihf/libopencv_imgcodecs.so\
        /usr/lib/libfairsionCamera.so\
        /usr/local/lib/arm-linux-gnueabihf/libopencv_videoio.so

HEADERS += \
    cgetimg.h \
    cimgproc.h \
    ccallocal.h \
    cserial.h \
    cfacerec.h
