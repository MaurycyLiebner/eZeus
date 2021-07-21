TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L/usr/lib/x86_64-linux-gnu
LIBS += -lSDL2 -lSDL2_image -lSDL2_ttf

SOURCES += \
        etexturehelper.cpp \
        ewindow.cpp \
        ewindowrenderer.cpp \
        main.cpp

HEADERS += \
    etexturehelper.h \
    ewindow.h \
    ewindowrenderer.h
