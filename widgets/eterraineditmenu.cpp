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

    mSpacing = 2*mult;

    const auto w0 = new eActionListWidget(window());
    w0->addAction("Apply", [this]() {
        mBrushType = eBrushType::apply;
    }, [this]() {
        return mBrushType == eBrushType::apply;
    });
    for(int i = 0; i < 5; i++) {
        w0->addAction(eLanguage::zeusText(48, i), [this, i]() {
            mBrushType = eBrushType::brush;
            mBrushSize = i + 1;
        }, [this, i]() {
            return mBrushType == eBrushType::brush &&
                   mBrushSize == i + 1;
        });
    }
    for(int i = 0; i < 5; i++) {
        w0->addAction(eLanguage::zeusText(48, 5 + i), [this, i]() {
            mBrushType = eBrushType::square;
            mBrushSize = i + 2;
        }, [this, i]() {
            return mBrushType == eBrushType::square &&
                   mBrushSize == i + 2;
        });
    }
    w0->stackVertically(mSpacing);
    w0->fitContent();

    const auto w1 = new eWidget(window());

    const auto w2 = new eActionListWidget(window());
    w2->addAction("Forest", [this]() {
        mMode = eTerrainEditMode::forest;
    });
    w2->addAction("Chopped Forest", [this]() {
        mMode = eTerrainEditMode::choppedForest;
    });
    w2->addAction("Rainforest", [this]() {
        mMode = eTerrainEditMode::rainforest;
    });
    w2->addAction("Normal Forest", [this]() {
        mMode = eTerrainEditMode::normalForest;
    });
    w2->stackVertically(mSpacing);
    w2->fitContent();

    const auto w3 = new eActionListWidget(window());
    w3->addAction("Water", [this]() {
        mMode = eTerrainEditMode::water;
    });
    w3->addAction("Beach", [this]() {
        mMode = eTerrainEditMode::beach;
    });
    w3->addAction("Marsh", [this]() {
        mMode = eTerrainEditMode::marsh;
    });
    w3->stackVertically(mSpacing);
    w3->fitContent();

    const auto w4 = new eWidget(window());
    const auto w5 = new eActionListWidget(window());
    w5->addAction("Fish", [this]() {
        mMode = eTerrainEditMode::fish;
    });
    w5->addAction("Urchin", [this]() {
        mMode = eTerrainEditMode::urchin;
    });
    w5->stackVertically(mSpacing);
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
    w6->addAction("Black Marble", [this]() {
        mMode = eTerrainEditMode::blackMarble;
    });
    w6->addAction("Copper Ore", [this]() {
        mMode = eTerrainEditMode::bronze;
    });
    w6->addAction("Silver Ore", [this]() {
        mMode = eTerrainEditMode::silver;
    });
    w6->addAction("Orichalc", [this]() {
        mMode = eTerrainEditMode::orichalc;
    });
    w6->stackVertically(mSpacing);
    w6->fitContent();

    const auto w7 = new eActionListWidget(window());
    w7->addAction("Scrub", [this]() {
        mMode = eTerrainEditMode::scrub;
    });
    w7->addAction("Scrub area", [this]() {
        mMode = eTerrainEditMode::scrubArea;
    });
    w7->addAction("Remove crub", [this]() {
        mMode = eTerrainEditMode::removeScrub;
    });
    w7->addAction("Soften Scrub", [this]() {
        mMode = eTerrainEditMode::softenScrub;
    });
    w7->stackVertically(mSpacing);
    w7->fitContent();

    const auto w8 = new eActionListWidget(window());
    w8->addAction(eLanguage::zeusText(48, 12), [this]() {
        mMode = eTerrainEditMode::raise;
    });
    w8->addAction(eLanguage::zeusText(48, 13), [this]() {
        mMode = eTerrainEditMode::lower;
    });
    w8->addAction(eLanguage::zeusText(48, 14), [this]() {
        mMode = eTerrainEditMode::raiseHigh;
    });
    w8->addAction(eLanguage::zeusText(48, 15), [this]() {
        mMode = eTerrainEditMode::lowerHigh;
    });
    w8->addAction("Level Out", [this]() {
        mMode = eTerrainEditMode::levelOut;
    });
    w8->addAction("Reset Elevation", [this]() {
        mMode = eTerrainEditMode::resetElev;
    });
    w8->addAction(eLanguage::zeusText(48, 18), [this]() {
        mMode = eTerrainEditMode::halfSlope;
    });
    w8->addAction(eLanguage::zeusText(48, 16), [this]() {
        mMode = eTerrainEditMode::makeWalkable;
    });
    w8->stackVertically(mSpacing);
    w8->fitContent();

    const auto w9 = new eActionListWidget(window());
    w9->addAction(eLanguage::zeusText(48, 67), [this]() {
        mMode = eTerrainEditMode::quake;
    });
    w9->addAction(eLanguage::zeusText(48, 68), [this]() {
        mMode = eTerrainEditMode::lava;
    });
    w9->addAction(eLanguage::zeusText(48, 69), [this]() {
        mMode = eTerrainEditMode::tidalWave;
    });
    w9->addAction(eLanguage::zeusText(156, 5), [this]() {
        mMode = eTerrainEditMode::landSlide;
    });
    for(int i = 0; i < 8; i++) {
        w9->addAction(eLanguage::zeusText(48, 70 + i), [this, i]() {
            mMode = eTerrainEditMode::disasterPoint;
            mModeId = i + 1;
        }, [board, i, gw]() {
            const auto cid = gw->viewedCity();
            const auto b = board->banner(cid, eBannerTypeS::disasterPoint, i + 1);
            return b != nullptr;
        });
    }
    for(int i = 0; i < 3; i++) {
        w9->addAction(eLanguage::zeusText(48, 89 + i), [this, i]() {
            mMode = eTerrainEditMode::landSlidePoint;
            mModeId = i + 1;
        }, [board, i, gw]() {
            const auto cid = gw->viewedCity();
            const auto b = board->banner(cid, eBannerTypeS::landSlidePoint, i + 1);
            return b != nullptr;
        });
    }
    w9->stackVertically(mSpacing);
    w9->fitContent();

    const auto w10 = new eActionListWidget(window());
    for(int i = 8; i < 16; i++) {
        w10->addAction(eLanguage::zeusText(48, 56 + i - 8), [this, i]() {
            mMode = eTerrainEditMode::seaInvasion;
            mModeId = i + 1;
        }, [board, i, gw]() {
            const auto cid = gw->viewedCity();
            const auto b = board->banner(cid, eBannerTypeS::seaInvasion, i + 1);
            return b != nullptr;
        });
    }
    for(int i = 0; i < 3; i++) {
        w10->addAction(eLanguage::zeusText(48, 64 + i), [this, i]() {
            mMode = eTerrainEditMode::disembarkPoint;
            mModeId = i + 1;
        }, [board, i, gw]() {
            const auto cid = gw->viewedCity();
            const auto b = board->banner(cid, eBannerTypeS::disembarkPoint, i + 1);
            return b != nullptr;
        });
    }
    w10->stackVertically(mSpacing);
    w10->fitContent();

    const auto w11 = new eActionListWidget(window());
    for(int i = 0; i < 8; i++) {
        w11->addAction(eLanguage::zeusText(48, 19 + i), [this, i]() {
            mMode = eTerrainEditMode::landInvasion;
            mModeId = i + 1;
        }, [board, i, gw]() {
            const auto cid = gw->viewedCity();
            const auto b = board->banner(cid, eBannerTypeS::landInvasion, i + 1);
            return b != nullptr;
        });
    }
    for(int i = 0; i < 3; i++) {
        w11->addAction(eLanguage::zeusText(48, 86 + i), [this, i]() {
            mMode = eTerrainEditMode::monsterPoint;
            mModeId = i + 1;
        }, [board, i, gw]() {
            const auto cid = gw->viewedCity();
            const auto b = board->banner(cid, eBannerTypeS::monsterPoint, i + 1);
            return b != nullptr;
        });
    }
    w11->stackVertically(mSpacing);
    w11->fitContent();

    mW12 = new eActionListWidget(window());
    mW12->addAction(eLanguage::zeusText(48, 10), [this]() {
        mMode = eTerrainEditMode::entryPoint;
        mModeId = 1;
    }, [board, gw]() {
        const auto cid = gw->viewedCity();
        const auto b = board->banner(cid, eBannerTypeS::entryPoint);
        return b != nullptr;
    });
    mW12->addAction(eLanguage::zeusText(48, 11), [this]() {
        mMode = eTerrainEditMode::exitPoint;
        mModeId = 1;
    }, [board, gw]() {
        const auto cid = gw->viewedCity();
        const auto b = board->banner(cid, eBannerTypeS::exitPoint);
        return b != nullptr;
    });

    mW12->addAction(eLanguage::zeusText(48, 27), [this]() {
        mMode = eTerrainEditMode::riverEntryPoint;
        mModeId = 1;
    }, [board, gw]() {
        const auto cid = gw->viewedCity();
        const auto b = board->banner(cid, eBannerTypeS::riverEntryPoint);
        return b != nullptr;
    });
    mW12->addAction(eLanguage::zeusText(48, 28), [this]() {
        mMode = eTerrainEditMode::riverExitPoint;
        mModeId = 1;
    }, [board, gw]() {
        const auto cid = gw->viewedCity();
        const auto b = board->banner(cid, eBannerTypeS::riverExitPoint);
        return b != nullptr;
    });
    {
        mW12->addAction("Assign All", [this, board]() {
            const auto cid = static_cast<eCityId>(mModeId);
            board->assignAllTerritory(cid);
        });
        mW12->addAction("Neutral Territory", [this]() {
            mMode = eTerrainEditMode::cityTerritory;
            mModeId = static_cast<int>(eCityId::neutralFriendly);
        });
    }
    updateCitiesOnBoard(*board);
    mW12->stackVertically(mSpacing);
    mW12->fitContent();


    const auto w13 = new eActionListWidget(window());
    for(int i = 0; i < 3; i++) {
        w13->addAction(eLanguage::zeusText(48, 47 + i), [this, i]() {
            mMode = eTerrainEditMode::boar;
            mModeId = i + 1;
        }, [board, i, gw]() {
            const auto cid = gw->viewedCity();
            const auto b = board->banner(cid, eBannerTypeS::boar, i + 1);
            return b != nullptr;
        });
    }
    for(int i = 0; i < 3; i++) {
        w13->addAction(eLanguage::zeusText(48, 92 + i), [this, i]() {
            mMode = eTerrainEditMode::deer;
            mModeId = i + 1;
        }, [board, i, gw]() {
            const auto cid = gw->viewedCity();
            const auto b = board->banner(cid, eBannerTypeS::deer, i + 1);
            return b != nullptr;
        });
    }
    w13->stackVertically(mSpacing);
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
    mWidgets.push_back(mW12);
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

    addButton(coll.fBrushSize, w0);
    mB1 = addButton(coll.fEmptyLand, w1);
    addButton(coll.fForest, w2);
    addButton(coll.fWaterMarshBeach, w3);
    mB4 = addButton(coll.fMeadow, w4);
    addButton(coll.fFishAndUrchin, w5);
    addButton(coll.fRocks, w6);
    addButton(coll.fScrub, w7);
    addButton(coll.fElevation, w8);
    addButton(coll.fDisasters, w9);
    addButton(coll.fWaterPoints, w10);
    addButton(coll.fLandInvasionPoints, w11);
    addButton(coll.fExitEndEntryPoints, mW12);
    addButton(coll.fAnimalPoints, w13);

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
    }
    return mMode;
}

void eTerrainEditMenu::setWorldDirection(const eWorldDirection dir) {
    mRotateButton->setDirection(dir);
}

bool sizeOneAction(const eTerrainEditMode mode) {
    return mode == eTerrainEditMode::quake ||
           mode == eTerrainEditMode::disasterPoint ||
           mode == eTerrainEditMode::entryPoint ||
           mode == eTerrainEditMode::exitPoint ||
           mode == eTerrainEditMode::riverEntryPoint ||
           mode == eTerrainEditMode::riverExitPoint ||
           mode == eTerrainEditMode::deer ||
           mode == eTerrainEditMode::boar ||
           mode == eTerrainEditMode::fish ||
           mode == eTerrainEditMode::urchin ||
           mode == eTerrainEditMode::landInvasion ||
           mode == eTerrainEditMode::monsterPoint ||
           mode == eTerrainEditMode::seaInvasion ||
           mode == eTerrainEditMode::disembarkPoint;
}

eBrushType eTerrainEditMenu::brushType() const {
    if(sizeOneAction(mode())) {
        return eBrushType::brush;
    }
    return mBrushType;
}

int eTerrainEditMenu::brushSize() const {
    if(sizeOneAction(mode())) {
        return 1;
    }
    return mBrushSize;
}

void eTerrainEditMenu::updateCitiesOnBoard(eGameBoard& board) {
    for(const auto tb : mTerrioryButtons) {
        tb.second->deleteLater();
    }
    mTerrioryButtons.clear();
    const auto cids = board.citiesOnBoard();
    for(const auto cid : cids) {
        const auto name = board.cityName(cid);
        const auto w = mW12->addAction(name + " Territory", [this, cid]() {
            mMode = eTerrainEditMode::cityTerritory;
            mModeId = static_cast<int>(cid);
        });
        mTerrioryButtons[cid] = w;
    }
    mW12->stackVertically(mSpacing);
    mW12->fitContent();
}
