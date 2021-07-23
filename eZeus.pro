TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L/usr/lib/x86_64-linux-gnu
LIBS += -lpthread -lSDL2 -lSDL2_image -lSDL2_ttf

SOURCES += \
        emainwindow.cpp \
        engine/eeventloop.cpp \
        engine/etask.cpp \
        engine/ethreadpool.cpp \
        espriteframe.cpp \
        esprites.cpp \
        etexture.cpp \
        main.cpp \
        widgets/ebutton.cpp \
        widgets/efonts.cpp \
        widgets/elayout.cpp \
        widgets/emainmenu.cpp \
        widgets/emouseevent.cpp \
        widgets/epainter.cpp \
        widgets/esettingsmenu.cpp \
        widgets/evlayout.cpp \
        widgets/ewidget.cpp

HEADERS += \
    emainwindow.h \
    engine/eeventloop.h \
    engine/etask.h \
    engine/ethreadpool.h \
    espriteframe.h \
    esprites.h \
    etexture.h \
    widgets/ebutton.h \
    widgets/efonts.h \
    widgets/elayout.h \
    widgets/emainmenu.h \
    widgets/emouseevent.h \
    widgets/epainter.h \
    widgets/esettingsmenu.h \
    widgets/evlayout.h \
    widgets/ewidget.h
