#include "eterraineditmenu.h"

#include "textures/egametextures.h"
#include "eactionlistwidget.h"
#include "engine/egameboard.h"
#include "spawners/ebanner.h"
#include "erotatebutton.h"
#include "eminimap.h"
#include "egamewidget.h"
#include "elanguage.h"

void eTerrainEditMenu::initialize(eGameWidget* const gw,
                                  eGameBoard* const board) {
    eGameMenuBase::initialize();

    int iRes;
    int mult;
    iResAndMult(iRes, mult);

    const auto& intrfc = eGameTextures::interface();
    const auto& coll = intrfc[iRes];
    const auto tex = coll.fMapEditMenuBackground;
    setTexture(tex);
    setPadding(0);
    fitContent();

    const int spacing = 2*mult;

    const auto w0 = new eWidget(window());
    const auto w1 = new eWidget(window());

    const auto w2 = new eActionListWidget(window());
    w2->addAction("Forest", [this]() {
        mMode = eTerrainEditMode::forest;
    });
    w2->addAction("Chopped Forest", [this]() {
        mMode = eTerrainEditMode::choppedForest;
    });
    w2->stackVertically(spacing);
    w2->fitContent();

    const auto w3 = new eActionListWidget(window());
    w3->addAction("Water", [this]() {
        mMode = eTerrainEditMode::water;
    });
    w3->addAction("Beach", [this]() {
        mMode = eTerrainEditMode::beach;
    });
    w3->stackVertically(spacing);
    w3->fitContent();

    const auto w4 = new eWidget(window());
    const auto w5 = new eActionListWidget(window());
    w5->addAction("Fish", [this]() {
        mMode = eTerrainEditMode::fish;
    });
    w5->addAction("Urchin", [this]() {
        mMode = eTerrainEditMode::urchin;
    });
    w5->stackVertically(spacing);
    w5->fitContent();

    const auto w6 = new eActionListWidget(window());
    w6->addAction("Flat Rock", [this]() {
        mMode = eTerrainEditMode::flatStones;
    });
    w6->addAction("Tall Rock", [this]() {
        mMode = eTerrainEditMode::tallStones;
    });
    w6->addAction("Marble", [this]() {
        mMode = eTerrainEditMode::marble;
    });
    w6->addAction("Copper Ore", [this]() {
        mMode = eTerrainEditMode::bronze;
    });
    w6->addAction("Silver Ore", [this]() {
        mMode = eTerrainEditMode::silver;
    });
    w6->stackVertically(spacing);
    w6->fitContent();

    const auto w7 = new eWidget(window());

    const auto w8 = new eActionListWidget(window());
    w8->addAction("Raise", [this]() {
        mMode = eTerrainEditMode::raise;
    });
    w8->addAction("Lower", [this]() {
        mMode = eTerrainEditMode::lower;
    });
    w8->addAction("Level Out", [this]() {
        mMode = eTerrainEditMode::levelOut;
    });
    w8->addAction("Reset Elevation", [this]() {
        mMode = eTerrainEditMode::resetElev;
    });
    w8->addAction("Make Walkable", [this]() {
        mMode = eTerrainEditMode::makeWalkable;
    });
    w8->stackVertically(spacing);
    w8->fitContent();

    const auto w9 = new eActionListWidget(window());
    w9->addAction("Fire", [this]() {
        mMode = eTerrainEditMode::fire;
    });
    w9->addAction("Ruins", [this]() {
        mMode = eTerrainEditMode::ruins;
    });
    w9->addAction(eLanguage::zeusText(48, 67), [this]() {
        mMode = eTerrainEditMode::quake;
    });
    for(int i = 0; i < 8; i++) {
        w9->addAction(eLanguage::zeusText(48, 70 + i), [this, i]() {
            mMode = eTerrainEditMode::disasterPoint;
            mModeId = i;
        }, [board, i]() {
            const auto b = board->banner(eBannerTypeS::disasterPoint, i);
            return b != nullptr;
        });
    }
    w9->stackVertically(spacing);
    w9->fitContent();

    const auto w10 = new eWidget(window());


    const auto w11 = new eActionListWidget(window());
    for(int i = 0; i < 8; i++) {
        w11->addAction("Land inv pt " + std::to_string(i + 1), [this, i]() {
            mMode = eTerrainEditMode::landInvasion;
            mModeId = i;
        }, [board, i]() {
            const auto b = board->banner(eBannerTypeS::landInvasion, i);
            return b != nullptr;
        });
    }
    for(int i = 0; i < 3; i++) {
        w11->addAction("Monster Point " + std::to_string(i + 1), [this, i]() {
            mMode = eTerrainEditMode::monsterPoint;
            mModeId = i;
        }, [board, i]() {
            const auto b = board->banner(eBannerTypeS::monsterPoint, i);
            return b != nullptr;
        });
    }
    w11->stackVertically(spacing);
    w11->fitContent();

    const auto w12 = new eActionListWidget(window());
    w12->addAction("Entry Point", [this]() {
        mMode = eTerrainEditMode::entryPoint;
        mModeId = 0;
    }, [board]() {
        const auto b = board->banner(eBannerTypeS::entryPoint);
        return b != nullptr;
    });
    w12->addAction("Exit Point", [this]() {
        mMode = eTerrainEditMode::exitPoint;
        mModeId = 0;
    }, [board]() {
        const auto b = board->banner(eBannerTypeS::exitPoint);
        return b != nullptr;
    });
    w12->stackVertically(spacing);
    w12->fitContent();


    const auto w13 = new eActionListWidget(window());
    for(int i = 0; i < 3; i++) {
        w13->addAction("Boar spawn " + std::to_string(i + 1), [this, i]() {
            mMode = eTerrainEditMode::boar;
            mModeId = i;
        }, [board, i]() {
            const auto b = board->banner(eBannerTypeS::boar, i);
            return b != nullptr;
        });
    }
    for(int i = 0; i < 3; i++) {
        w13->addAction("Deer spawn " + std::to_string(i + 1), [this, i]() {
            mMode = eTerrainEditMode::deer;
            mModeId = i;
        }, [board, i]() {
            const auto b = board->banner(eBannerTypeS::deer, i);
            return b != nullptr;
        });
    }
    w13->stackVertically(spacing);
    w13->fitContent();

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
        w->move(24*mult, 10*mult);
        w->setWidth(width() - w->x());
        w->hide();
    }

    const int dataWidWidth = 65*mult;
    const int dataWidHeight = 119*mult;
    const int wy = dataWidHeight + 96*mult;
    mMiniMap = new eMiniMap(window());
    mMiniMap->resize(dataWidWidth, 4*dataWidWidth/5);
    addWidget(mMiniMap);
    mMiniMap->move(24*mult, wy);
    mMiniMap->setBoard(board);

    const auto b0 = addButton(coll.fBrushSize, w0);
    mB1 = addButton(coll.fEmptyLand, w1);
    const auto b2 = addButton(coll.fForest, w2);
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

        const auto b0 = eCheckableButton::sCreate(coll.fBuildRoad, window(), btmButtons);
        mRotateButton = new eRotateButton(window());
        btmButtons->addWidget(mRotateButton);
        mRotateButton->setDirectionSetter([gw](const eWorldDirection dir) {
            gw->setWorldDirection(dir);
        });
        const auto b1 = eCheckableButton::sCreate(coll.fUndo, window(), btmButtons);

        const int x = mult*24;
        const int y = std::round(mult*279.5);
        btmButtons->resize(b0->width() + b1->width() + mRotateButton->width(),
                           b0->height());
        btmButtons->move(x, y);
        btmButtons->layoutHorizontally();
        addWidget(btmButtons);
    }
}

eTerrainEditMode eTerrainEditMenu::mode() const {
    if(mB1->checked()) {
        return eTerrainEditMode::dry;
    } else if(mB4->checked()) {
        return eTerrainEditMode::fertile;
    } else if(mB7->checked()) {
        return eTerrainEditMode::scrub;
    }
    return mMode;
}

void eTerrainEditMenu::setWorldDirection(const eWorldDirection dir) {
    mRotateButton->setDirection(dir);
}
