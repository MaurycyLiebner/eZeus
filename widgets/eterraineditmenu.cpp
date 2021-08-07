#include "eterraineditmenu.h"

#include "textures/egametextures.h"
#include "eactionlistwidget.h"

void eTerrainEditMenu::initialize() {
    eGameMenuBase::initialize();

    const auto& intrfc = eGameTextures::interface();
    int mult;
    int icoll;
    switch(resolution()) {
    case eRes::p480:
        mult = 1;
        icoll = 0;
        break;
    case eRes::p720:
    case eRes::p1080:
        mult = 2;
        icoll = 1;
        break;
    default:
        mult = 4;
        icoll = 2;
    }
    const auto& coll = intrfc[icoll];
    const auto tex = coll.fMapEditMenuBackground;
    setTexture(tex);
    setPadding(0);
    fitContent();

    const auto w0 = new eWidget(window());
    const auto w1 = new eWidget(window());
    const auto w2 = new eWidget(window());

    const auto w3 = new eActionListWidget(window());
    w3->addAction("Water", [this]() {
        mMode = eTerrainEditMode::water;
    });
    w3->addAction("Beach", [this]() {
        mMode = eTerrainEditMode::beach;
    });
    w3->fitContent();

    const auto w4 = new eWidget(window());
    const auto w5 = new eWidget(window());

    const auto w6 = new eActionListWidget(window());
    w6->addAction("Water", [this]() {
        mMode = eTerrainEditMode::water;
    });
    w6->addAction("Flat Rock", [this]() {
        mMode = eTerrainEditMode::flatStones;
    });
    w6->addAction("Tall Rock", [this]() {
        mMode = eTerrainEditMode::tallStones;
    });
    w6->addAction("Tiny Rock", [this]() {
        mMode = eTerrainEditMode::tinyStones;
    });
    w6->addAction("Copper Ore", [this]() {
        mMode = eTerrainEditMode::bronze;
    });
    w6->addAction("Silver Ore", [this]() {
        mMode = eTerrainEditMode::silver;
    });
    w6->fitContent();

    const auto w7 = new eWidget(window());

    const auto w8 = new eActionListWidget(window());
    w8->addAction("Raise", [this]() {
        mMode = eTerrainEditMode::raise;
    });
    w8->addAction("Lower", [this]() {
        mMode = eTerrainEditMode::lower;
    });
    w8->fitContent();

    const auto w9 = new eWidget(window());
    const auto w10 = new eWidget(window());
    const auto w11 = new eWidget(window());
    const auto w12 = new eWidget(window());
    const auto w13 = new eWidget(window());

    mWidgets.push_back(w0);
    mWidgets.push_back(w1);
    mWidgets.push_back(w2);
    mWidgets.push_back(w3);
    mWidgets.push_back(w4);
    mWidgets.push_back(w5);
    mWidgets.push_back(w6);
    mWidgets.push_back(w7);
    mWidgets.push_back(w8);
    mWidgets.push_back(w9);
    mWidgets.push_back(w10);
    mWidgets.push_back(w11);
    mWidgets.push_back(w12);
    mWidgets.push_back(w13);

    for(const auto w : mWidgets) {
        addWidget(w);
        w->move(21*mult, 10*mult);
        w->hide();
    }

    const auto b0 = addButton(coll.fBrushSize, w0);
    mB1 = addButton(coll.fEmptyLand, w1);
    mB2 = addButton(coll.fForest, w2);
    const auto b3 = addButton(coll.fWaterMarshBeach, w3);
    mB4 = addButton(coll.fMeadow, w4);
    const auto b5 = addButton(coll.fFishAndUrchin, w5);
    const auto b6 = addButton(coll.fRocks, w6);
    mB7 = addButton(coll.fScrub, w7);
    const auto b8 = addButton(coll.fElevation, w8);
    const auto b9 = addButton(coll.fDisasters, w9);
    const auto b10 = addButton(coll.fWaterPoints, w10);
    const auto b11 = addButton(coll.fLandInvasionPoints, w11);
    const auto b12 = addButton(coll.fExitEndEntryPoints, w12);
    const auto b13 = addButton(coll.fAnimalPoints, w13);

    connectAndLayoutButtons();

    {
        const auto btmButtons = new eWidget(window());
        btmButtons->setPadding(0);

        const auto b0 = createButton(coll.fBuildRoad, btmButtons);
        const auto b2 = createButton(coll.fRotation, btmButtons);
        const auto b1 = createButton(coll.fUndo, btmButtons);

        const int x = mult*24;
        const int y = std::round(mult*279.5);
        btmButtons->resize(b0->width() + b1->width() + b2->width(),
                           b0->height());
        btmButtons->move(x, y);
        btmButtons->layoutHorizontally();
        addWidget(btmButtons);
    }
}

eTerrainEditMode eTerrainEditMenu::mode() const {
    if(mB1->checked()) {
        return eTerrainEditMode::dry;
    } else if(mB2->checked()) {
        return eTerrainEditMode::forest;
    } else if(mB4->checked()) {
        return eTerrainEditMode::fertile;
    } else if(mB7->checked()) {
        return eTerrainEditMode::scrub;
    }
    return mMode;
}
