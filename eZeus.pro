TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L/usr/lib/x86_64-linux-gnu
LIBS += -lSDL2 -lSDL2_image -lSDL2_ttf

SOURCES += \
        engine/eeventloop.cpp \
        engine/etask.cpp \
        engine/ethreadpool.cpp \
        espriteframe.cpp \
        esprites.cpp \
        etexture.cpp \
        ewindow.cpp \
        ewindowrenderer.cpp \
        main.cpp

HEADERS += \
    engine/eeventloop.h \
    engine/etask.h \
    engine/ethreadpool.h \
    espriteframe.h \
    esprites.h \
    etexture.h \
    ewindow.h \
    ewindowrenderer.h
