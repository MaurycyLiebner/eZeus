TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L/usr/lib/x86_64-linux-gnu
LIBS += -lpthread -lSDL2 -lSDL2_image -lSDL2_ttf

SOURCES += \
        emainwindow.cpp \
        engine/ebeachtodry.cpp \
        engine/eeventloop.cpp \
        engine/efertiletodry.cpp \
        engine/eforesttodry.cpp \
        engine/egameboard.cpp \
        engine/egameboarditerator.cpp \
        engine/egameeventloop.cpp \
        engine/egameobject.cpp \
        engine/emovinggameobject.cpp \
        engine/erivertodry.cpp \
        engine/etask.cpp \
        engine/ethreadpool.cpp \
        engine/etile.cpp \
        espriteframe.cpp \
        esprites.cpp \
        etexture.cpp \
        etexturecollection.cpp \
        main.cpp \
        widgets/ebutton.cpp \
        widgets/echeckbox.cpp \
        widgets/ecombobox.cpp \
        widgets/econtextmenu.cpp \
        widgets/efonts.cpp \
        widgets/egamewidget.cpp \
        widgets/elabel.cpp \
        widgets/elabeledwidget.cpp \
        widgets/emainmenu.cpp \
        widgets/emouseevent.cpp \
        widgets/epainter.cpp \
        widgets/eresolution.cpp \
        widgets/esettingsmenu.cpp \
        widgets/eterraineditmenu.cpp \
        widgets/ewidget.cpp

HEADERS += \
    emainwindow.h \
    engine/ebeachtodry.h \
    engine/eeventloop.h \
    engine/efertiletodry.h \
    engine/eforesttodry.h \
    engine/egameboard.h \
    engine/egameboarditerator.h \
    engine/egameeventloop.h \
    engine/egameobject.h \
    engine/emovinggameobject.h \
    engine/erivertodry.h \
    engine/etask.h \
    engine/ethreadpool.h \
    engine/etile.h \
    espriteframe.h \
    esprites.h \
    etexture.h \
    etexturecollection.h \
    widgets/ebutton.h \
    widgets/echeckbox.h \
    widgets/ecombobox.h \
    widgets/econtextmenu.h \
    widgets/efonts.h \
    widgets/egamewidget.h \
    widgets/elabel.h \
    widgets/elabeledwidget.h \
    widgets/emainmenu.h \
    widgets/emouseevent.h \
    widgets/epainter.h \
    widgets/eresolution.h \
    widgets/esettingsmenu.h \
    widgets/eterraineditmenu.h \
    widgets/ewidget.h
