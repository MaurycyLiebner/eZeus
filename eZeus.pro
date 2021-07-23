TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L/usr/lib/x86_64-linux-gnu
LIBS += -lpthread -lSDL2 -lSDL2_image -lSDL2_ttf

SOURCES += \
        engine/eeventloop.cpp \
        engine/etask.cpp \
        engine/ethreadpool.cpp \
        espriteframe.cpp \
        esprites.cpp \
        etexture.cpp \
        ewindow.cpp \
        ewindowrenderer.cpp \
        main.cpp \
        widgets/ebutton.cpp \
        widgets/efonts.cpp \
        widgets/emainmenu.cpp \
        widgets/emouseevent.cpp \
        widgets/epainter.cpp \
        widgets/ewidget.cpp

HEADERS += \
    engine/eeventloop.h \
    engine/etask.h \
    engine/ethreadpool.h \
    espriteframe.h \
    esprites.h \
    etexture.h \
    ewindow.h \
    ewindowrenderer.h \
    widgets/ebutton.h \
    widgets/efonts.h \
    widgets/emainmenu.h \
    widgets/emouseevent.h \
    widgets/epainter.h \
    widgets/ewidget.h
