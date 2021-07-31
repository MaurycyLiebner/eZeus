TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L/usr/lib/x86_64-linux-gnu
LIBS += -lpthread -lSDL2 -lSDL2_image -lSDL2_ttf

SOURCES += \
        buildings/ebuilding.cpp \
        buildings/egymnasium.cpp \
        buildings/eroad.cpp \
        buildings/esmallhouse.cpp \
        characters/echaracter.cpp \
        characters/echaracteraction.cpp \
        characters/edemeter.cpp \
        characters/emovearoundaction.cpp \
        emainwindow.cpp \
        engine/efunctask.cpp \
        engine/egameboard.cpp \
        engine/egameboarditerator.cpp \
        engine/egameobject.cpp \
        engine/emovinggameobject.cpp \
        engine/etask.cpp \
        engine/eterrain.cpp \
        engine/ethreadpool.cpp \
        engine/etile.cpp \
        espriteframe.cpp \
        esprites.cpp \
        etexture.cpp \
        etexturecollection.cpp \
        main.cpp \
        textures/ebeachtodry.cpp \
        textures/ebuildingtextures.cpp \
        textures/echaractertextures.cpp \
        textures/edemetertextures.cpp \
        textures/efertiletodry.cpp \
        textures/eforesttodry.cpp \
        textures/estonestodry.cpp \
        textures/esurroundingterrain.cpp \
        textures/eterraintextures.cpp \
        textures/etextureloadinghelpers.cpp \
        textures/etiletotexture.cpp \
        textures/ewatercorner.cpp \
        textures/ewatertobeach.cpp \
        textures/ewatertodry.cpp \
        textures/ewatertox.cpp \
        widgets/ebutton.cpp \
        widgets/echeckablebutton.cpp \
        widgets/echeckbox.cpp \
        widgets/ecombobox.cpp \
        widgets/econtextmenu.cpp \
        widgets/efonts.cpp \
        widgets/egameloadingwidget.cpp \
        widgets/egamewidget.cpp \
        widgets/elabel.cpp \
        widgets/elabeledwidget.cpp \
        widgets/emainmenu.cpp \
        widgets/emouseevent.cpp \
        widgets/epainter.cpp \
        widgets/eprogressbar.cpp \
        widgets/eresolution.cpp \
        widgets/esettingsmenu.cpp \
        widgets/etabwidget.cpp \
        widgets/eterraineditmenu.cpp \
        widgets/etilepainter.cpp \
        widgets/ewidget.cpp

HEADERS += \
    buildings/ebuilding.h \
    buildings/egymnasium.h \
    buildings/eroad.h \
    buildings/esmallhouse.h \
    characters/echaracter.h \
    characters/echaracteraction.h \
    characters/edemeter.h \
    characters/emovearoundaction.h \
    emainwindow.h \
    engine/efunctask.h \
    engine/egameboard.h \
    engine/egameboarditerator.h \
    engine/egameobject.h \
    engine/emovinggameobject.h \
    engine/eorientation.h \
    engine/etask.h \
    engine/eterrain.h \
    engine/ethreadpool.h \
    engine/etile.h \
    espriteframe.h \
    esprites.h \
    etexture.h \
    etexturecollection.h \
    textures/ebeachtodry.h \
    textures/ebuildingtextures.h \
    textures/echaractertextures.h \
    textures/edemetertextures.h \
    textures/efertiletodry.h \
    textures/eforesttodry.h \
    textures/estonestodry.h \
    textures/esurroundingterrain.h \
    textures/eterraintextures.h \
    textures/etextureloadinghelpers.h \
    textures/etiletotexture.h \
    textures/ewatercorner.h \
    textures/ewatertobeach.h \
    textures/ewatertodry.h \
    textures/ewatertox.h \
    widgets/ebutton.h \
    widgets/echeckablebutton.h \
    widgets/echeckbox.h \
    widgets/ecombobox.h \
    widgets/econtextmenu.h \
    widgets/efonts.h \
    widgets/egameloadingwidget.h \
    widgets/egamewidget.h \
    widgets/elabel.h \
    widgets/elabeledwidget.h \
    widgets/emainmenu.h \
    widgets/emouseevent.h \
    widgets/epainter.h \
    widgets/eprogressbar.h \
    widgets/eresolution.h \
    widgets/esettingsmenu.h \
    widgets/etabwidget.h \
    widgets/eterraineditmenu.h \
    widgets/etilepainter.h \
    widgets/ewidget.h
