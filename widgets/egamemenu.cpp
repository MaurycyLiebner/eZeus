#include "egamemenu.h"

#include "textures/egametextures.h"
#include "emainwindow.h"
#include "echeckablebutton.h"
#include "econtextmenu.h"
#include "engine/egameboard.h"
#include "engine/edifficulty.h"

#include "widgets/datawidgets/epopulationdatawidget.h"
#include "widgets/datawidgets/eemploymentdatawidget.h"
#include "widgets/datawidgets/eappealdatawidget.h"
#include "eminimap.h"

struct eSubButtonData {
    std::function<void()> fPressedFunc;
    const eTextureCollection* fColl = nullptr;
};

eButton* eGameMenu::createSubButton(
        const eTextureCollection& texs,
        eWidget* const buttons) {
    const auto b = new eButton(window());
    b->setTexture(texs.getTexture(0));
    b->setPadding(0);
    b->setHoverTexture(texs.getTexture(1));
    b->setPressedTexture(texs.getTexture(2));
    b->fitContent();
    buttons->addWidget(b);
    return b;
}

eWidget* eGameMenu::createSubButtons(
        const int resoltuionMult,
        const eButtonsDataVec& buttons) {
    const auto result = new eWidget(window());

    const int x = resoltuionMult*35;
    const int y = resoltuionMult*27;
    const std::vector<std::pair<int, int>> poses =
        {{0, 0}, {x, 0}, {0, y}, {x, y}};

    const int iMax = buttons.size();
    for(int i = 0; i < iMax; i++) {
        const auto& c = buttons[i];
        const auto b = createSubButton(*c.fColl, result);
        b->setPressAction(c.fPressedFunc);
        const auto& pos = poses[i];
        b->setX(pos.first);
        b->setY(pos.second);
    }

    result->setPadding(0);
    result->fitContent();

    return result;
}

void eGameMenu::addAction(const eSPR& c, const int mult,
                          const eInterfaceTextures& coll,
                          eContextMenu* const cm) {
    auto& a = cm->addAction(c.second, [this, c]() {
        setMode(c.first);
    });
    const auto diff = mBoard->difficulty();
    const auto mode = c.first;
    const auto t = eBuildingModeHelpers::toBuildingType(mode);
    const int cost = eDifficultyHelpers::buildingCost(diff, t);
    a.addTexture(mult*20, coll.fDrachmasUnit);
    a.addText(0, std::to_string(cost));
}

void eGameMenu::initialize() {
    eGameMenuBase::initialize();

    const auto& intrfc = eGameTextures::interface();
    int mult;
    int icoll;
    switch(resolution().uiScale()) {
    case eUIScale::small:
        mult = 1;
        icoll = 0;
        break;
    case eUIScale::medium:
        mult = 2;
        icoll = 1;
        break;
    default:
        mult = 4;
        icoll = 2;
    }
    const auto& coll = intrfc[icoll];
    const auto tex = coll.fGameMenuBackground;
    setTexture(tex);
    setPadding(0);
    fitContent();

    const int cmx = -padding();
    const int cmy = 3*height()/4;

    const auto cha0 = [this]() {
        setMode(eBuildingMode::commonHousing);
    };
    const auto eha0 = [this]() {
        setMode(eBuildingMode::eliteHousing);
    };

    const auto ww0 = new eWidget(window());
    const auto w0 = createSubButtons(mult,
                        eButtonsDataVec{
                            {cha0, &coll.fCommonHousing},
                            {eha0, &coll.fEliteHousing}});
    mPopDataW = new ePopulationDataWidget(window());
    mPopDataW->setWidth(65*mult);
    mPopDataW->setHeight(120*mult);
    mPopDataW->initialize();
    ww0->addWidget(mPopDataW);
    ww0->addWidget(w0);
    ww0->fitContent();
    ww0->setHeight(190*mult);
    w0->setY(mPopDataW->height() + 20*mult);
    mPopDataW->align(eAlignment::top);

    const auto ff1 = [this, cmx, cmy, mult, coll]() {
        const auto cm = new eContextMenu(window());
        for(const auto& c : {eSPR{eBuildingMode::wheatFarm, "Wheat Farm"},
                             eSPR{eBuildingMode::carrotFarm, "Carrot Farm"},
                             eSPR{eBuildingMode::onionFarm, "Onion Farm"}}) {
            addAction(c, mult, coll, cm);
        }
        cm->fitContent();
        cm->exec(cmx - cm->width(), cmy - cm->height(), this);
    };
    const auto of1 = [this, cmx, cmy, mult, coll]() {
        const auto cm = new eContextMenu(window());
        for(const auto& c : {eSPR{eBuildingMode::vine, "Vine"},
                             eSPR{eBuildingMode::oliveTree, "Olive Tree"},
                             eSPR{eBuildingMode::growersLodge, "Growers Lodge"}}) {
            addAction(c, mult, coll, cm);
        }
        cm->fitContent();
        cm->exec(cmx - cm->width(), cmy - cm->height(), this);
    };
    const auto af1 = [this, cmx, cmy, coll, mult]() {
        const auto cm = new eContextMenu(window());
        for(const auto& c : {eSPR{eBuildingMode::dairy, "Dairy"},
                             eSPR{eBuildingMode::goat, "Goat"},
                             eSPR{eBuildingMode::cardingShed, "Carding Shed"},
                             eSPR{eBuildingMode::sheep, "Sheep"}}) {
            addAction(c, mult, coll, cm);
        }
        cm->fitContent();
        cm->exec(cmx - cm->width(), cmy - cm->height(), this);
    };
    const auto ah1 = [this, cmx, cmy, coll, mult]() {
        const auto cm = new eContextMenu(window());
        for(const auto& c : {eSPR{eBuildingMode::fishery, "Fishery"},
                             eSPR{eBuildingMode::urchinQuay, "Urchin Quay"},
                             eSPR{eBuildingMode::huntingLodge, "Hunting Lodge"}}) {
            addAction(c, mult, coll, cm);
        }
        cm->fitContent();
        cm->exec(cmx - cm->width(), cmy - cm->height(), this);
    };

    const auto w1 = createSubButtons(mult,
                        eButtonsDataVec{
                            {ff1, &coll.fFoodFarming},
                            {of1, &coll.fOtherFarming},
                            {af1, &coll.fAnimalFarming},
                            {ah1, &coll.fAnimalHunting}});


    const auto r2 = [this, cmx, cmy, coll, mult]() {
        const auto cm = new eContextMenu(window());
        for(const auto& c : {eSPR{eBuildingMode::mint, "Mint"},
                             eSPR{eBuildingMode::foundry, "Foundry"},
                             eSPR{eBuildingMode::timberMill, "Timber Mill"},
                             eSPR{eBuildingMode::masonryShop, "Masonry Shop"}}) {
            addAction(c, mult, coll, cm);
        }
        cm->fitContent();
        cm->exec(cmx - cm->width(), cmy - cm->height(), this);
    };
    const auto p2 = [this, cmx, cmy, coll, mult]() {
        const auto cm = new eContextMenu(window());
        for(const auto& c : {eSPR{eBuildingMode::winery, "Winery"},
                             eSPR{eBuildingMode::olivePress, "Olive Press"},
                             eSPR{eBuildingMode::sculptureStudio, "Sculpture Studio"}}) {
            addAction(c, mult, coll, cm);
        }
        cm->fitContent();
        cm->exec(cmx - cm->width(), cmy - cm->height(), this);
    };
    const auto bg2 = [this]() {
        setMode(eBuildingMode::artisansGuild);
    };

    const auto ww2 = new eWidget(window());
    const auto w2 = createSubButtons(mult,
                        eButtonsDataVec{
                             {r2, &coll.fResources},
                             {p2, &coll.fProcessing},
                             {bg2, &coll.fBuildersGuild}});
    mEmplDataW = new eEmploymentDataWidget(window());
    mEmplDataW->setWidth(65*mult);
    mEmplDataW->setHeight(120*mult);
    mEmplDataW->initialize();
    ww2->addWidget(mEmplDataW);
    ww2->addWidget(w2);
    ww2->fitContent();
    ww2->setHeight(190*mult);
    w2->setY(mEmplDataW->height() + 20*mult);
    mEmplDataW->align(eAlignment::top);


    const auto g3 = [this]() {
        setMode(eBuildingMode::granary);
    };
    const auto ww3 = [this]() {
        setMode(eBuildingMode::warehouse);
    };
    const auto a3 = [this, cmx, cmy, coll, mult]() {
        const auto cm = new eContextMenu(window());
        for(const auto& c : {eSPR{eBuildingMode::foodVendor, "Food Vendor"},
                             eSPR{eBuildingMode::fleeceVendor, "Fleece Vendor"},
                             eSPR{eBuildingMode::oilVendor, "Oil Vendor"},
                             eSPR{eBuildingMode::wineVendor, "Wine Vendor"},
                             eSPR{eBuildingMode::armsVendor, "Arms Vendor"},
                             eSPR{eBuildingMode::horseTrainer, "Horse Trainer"}}) {
            addAction(c, mult, coll, cm);
        }
        cm->fitContent();
        cm->exec(cmx - cm->width(), cmy - cm->height(), this);
    };
    const auto t3 = [this, cmx, cmy, coll, mult]() {};
    const auto w3 = createSubButtons(mult,
                        eButtonsDataVec{
                             {g3, &coll.fGranary},
                             {ww3, &coll.fWarehouse},
                             {a3, &coll.fAgoras},
                             {t3, &coll.fTrade}});


    const auto ff4 = [this]() {
        setMode(eBuildingMode::maintenanceOffice);
    };
    const auto f4 = [this]() {
        setMode(eBuildingMode::fountain);
    };
    const auto p4 = [this]() {
        setMode(eBuildingMode::watchpost);
    };
    const auto h4 = [this]() {
        setMode(eBuildingMode::hospital);
    };
    const auto w4 = createSubButtons(mult,
                        eButtonsDataVec{
                             {ff4, &coll.fFireFighter},
                             {f4, &coll.fFountain},
                             {p4, &coll.fPolice},
                             {h4, &coll.fHospital}});

    const auto p5 = [this]() {
        setMode(eBuildingMode::palace);
    };
    const auto tc5 = [this]() {
        setMode(eBuildingMode::taxOffice);
    };
    const auto bb5 = [this]() {};
    const auto w5 = createSubButtons(mult,
                        eButtonsDataVec{
                             {p5, &coll.fPalace},
                             {tc5, &coll.fTaxCollector},
                             {bb5, &coll.fBridge}});


    const auto p6 = [this, cmx, cmy, coll, mult]() {
        const auto cm = new eContextMenu(window());
        for(const auto& c : {eSPR{eBuildingMode::podium, "Podium"},
                             eSPR{eBuildingMode::college, "College"}}) {
           addAction(c, mult, coll, cm);
        }
        cm->fitContent();
        cm->exec(cmx - cm->width(), cmy - cm->height(), this);
    };
    const auto g6 = [this]() {
        setMode(eBuildingMode::gymnasium);
    };
    const auto d6 = [this, cmx, cmy, coll, mult]() {
        const auto cm = new eContextMenu(window());
        for(const auto& c : {eSPR{eBuildingMode::theater, "Theater"},
                             eSPR{eBuildingMode::dramaSchool, "Drama School"}}) {
            addAction(c, mult, coll, cm);
        }
        cm->fitContent();
        cm->exec(cmx - cm->width(), cmy - cm->height(), this);
    };
    const auto s6 = [this]() {
        setMode(eBuildingMode::stadium);
    };
    const auto w6 = createSubButtons(mult,
                        eButtonsDataVec{
                             {p6, &coll.fPhilosophy},
                             {g6, &coll.fGymnasium},
                             {d6, &coll.fDrama},
                             {s6, &coll.fStadium}});


    const auto t7 = [this, cmx, cmy, coll, mult]() {};
    const auto hs7 = [this, cmx, cmy, coll, mult]() {};
    const auto w7 = createSubButtons(mult,
                        eButtonsDataVec{
                             {t7, &coll.fTemples},
                             {hs7, &coll.fHeroShrines}});

    const auto f8 = [this, cmx, cmy, coll, mult]() {};
    const auto mp8 = [this, cmx, cmy, coll, mult]() {
        const auto cm = new eContextMenu(window());
        for(const auto& c : {eSPR{eBuildingMode::armory, "Armory"}}) {
            addAction(c, mult, coll, cm);
        }
        cm->fitContent();
        cm->exec(cmx - cm->width(), cmy - cm->height(), this);
    };
    const auto w8 = createSubButtons(mult,
                        eButtonsDataVec{
                             {f8, &coll.fFortifications},
                             {mp8, &coll.fMilitaryProduction}});

    const auto bb9 = [this, cmx, cmy, coll, mult]() {
        const auto cm = new eContextMenu(window());
        for(const auto& c : {eSPR{eBuildingMode::park, "Park"},
                             eSPR{eBuildingMode::waterPark, "Water Park"},
                             eSPR{eBuildingMode::doricColumn, "Doric Column"},
                             eSPR{eBuildingMode::ionicColumn, "Ionic Column"},
                             eSPR{eBuildingMode::corinthianColumn, "Corinthian Column"}}) {
            addAction(c, mult, coll, cm);
        }
        cm->fitContent();
        cm->exec(cmx - cm->width(), cmy - cm->height(), this);
    };
    const auto r9 = [this, cmx, cmy, coll, mult]() {
        const auto cm = new eContextMenu(window());
        for(const auto& c : {eSPR{eBuildingMode::bench, "Bench"},
                             eSPR{eBuildingMode::birdBath, "Bird Bath"},
                             eSPR{eBuildingMode::shortObelisk, "Short Obelisk"},
                             eSPR{eBuildingMode::tallObelisk, "Tall Obelisk"},
                             eSPR{eBuildingMode::flowerGarden, "Flower Garden"},
                             eSPR{eBuildingMode::gazebo, "Gazebo"},
                             eSPR{eBuildingMode::shellGarden, "Shell Garden"},
                             eSPR{eBuildingMode::sundial, "Sundial"},
                             eSPR{eBuildingMode::hedgeMaze, "Hedge Maze"},
                             eSPR{eBuildingMode::dolphinSculpture, "Dolphin Sculpture"},
                             eSPR{eBuildingMode::spring, "Spring"},
                             eSPR{eBuildingMode::topiary, "Topiary"},
                             eSPR{eBuildingMode::fishPond, "Fish Pond"},
                             eSPR{eBuildingMode::baths, "Baths"},
                             eSPR{eBuildingMode::stoneCircle, "Stone Circle"}}) {
            addAction(c, mult, coll, cm);
        }
        cm->fitContent();
        cm->exec(cmx - cm->width(), cmy - cm->height(), this);
    };
    const auto m9 = [this, cmx, cmy, coll, mult]() {};

    const auto ww9 = new eWidget(window());
    const auto w9 = createSubButtons(mult,
                        eButtonsDataVec{
                             {bb9, &coll.fBeautification},
                             {r9, &coll.fRecreation},
                             {m9, &coll.fMonuments}});
    mApplDataW = new eAppealDataWidget(window());
    mApplDataW->setWidth(65*mult);
    mApplDataW->setHeight(120*mult);
    mApplDataW->initialize();
    ww9->addWidget(mApplDataW);
    ww9->addWidget(w9);
    ww9->fitContent();
    ww9->setHeight(190*mult);
    w9->setY(mApplDataW->height() + 20*mult);
    mApplDataW->align(eAlignment::top);


    mMiniMap = new eMiniMap(window());
    mMiniMap->resize(65*mult, 65*mult);

    mWidgets.push_back(ww0);
    mWidgets.push_back(w1);
    mWidgets.push_back(ww2);
    mWidgets.push_back(w3);
    mWidgets.push_back(w4);
    mWidgets.push_back(w5);
    mWidgets.push_back(w6);
    mWidgets.push_back(w7);
    mWidgets.push_back(w8);
    mWidgets.push_back(ww9);
    mWidgets.push_back(mMiniMap);

    for(const auto w : mWidgets) {
        addWidget(w);
        w->move(24*mult, 20*mult/*165*mult*/);
        w->hide();
    }

    const auto b0 = addButton(coll.fPopulation, ww0);
    const auto b1 = addButton(coll.fHusbandry, w1);
    const auto b2 = addButton(coll.fIndustry, ww2);
    const auto b3 = addButton(coll.fDistribution, w3);
    const auto b4 = addButton(coll.fHygieneSafety, w4);
    const auto b5 = addButton(coll.fAdministration, w5);
    const auto b6 = addButton(coll.fCulture, w6);
    const auto b7 = addButton(coll.fMythology, w7);
    const auto b8 = addButton(coll.fMilitary, w8);
    const auto b9 = addButton(coll.fAesthetics, ww9);
    const auto b10 = addButton(coll.fOverview, mMiniMap);

    b10->setChecked(true);

    connectAndLayoutButtons();

    {
        const auto btmButtons = new eWidget(window());
        btmButtons->setPadding(0);

        const auto b = createSubButton(coll.fBuildRoad, btmButtons);
        b->setPressAction([this]() {
            setMode(eBuildingMode::road);
        });
        createSubButton(coll.fRoadBlock, btmButtons);
        const auto e = createSubButton(coll.fClear, btmButtons);
        e->setPressAction([this]() {
            setMode(eBuildingMode::erase);
        });
        createSubButton(coll.fUndo, btmButtons);

        const int x = mult*24;
        const int y = std::round(mult*217.5);
        btmButtons->resize(4*b->width(), b->height());
        btmButtons->move(x, y);
        btmButtons->layoutHorizontally();
        addWidget(btmButtons);
    }

    {
        const auto butts = new eWidget(window());
        const auto info = createButton(coll.fShowInfo, butts);
        const auto map = createButton(coll.fShowMap, butts);
        info->setChecked(true);
        info->setCheckAction([info, map](const bool c) {
            if(!c) return info->setChecked(true);
            map->setChecked(false);
        });
        map->setCheckAction([info, map](const bool c) {
            if(!c) return map->setChecked(true);
            info->setChecked(false);
        });
        butts->resize(info->width() + map->width(), info->height());
        butts->layoutHorizontally();
        butts->setX(mult*26);
        addWidget(butts);
    }

    {
        const auto m = createButton(coll.fMessages, this);
        m->move(mult*73, mult*239);
    }
    {
        const auto butts = new eWidget(window());
        butts->setPadding(0);
        const auto goals = createButton(coll.fGoals, butts);
        const auto rotate = createButton(coll.fRotation, butts);
        const auto world = createButton(coll.fWorld, butts);
        const int w = goals->width() + rotate->width() + world->width() + 5;
        butts->resize(w, world->height());
        butts->layoutHorizontally();
        butts->setX(mult*5);
        butts->setY(std::round(mult*282.5));
        addWidget(butts);
    }
}

void eGameMenu::setGameWidget(eGameWidget* const gw) {
    mApplDataW->setGameWidget(gw);
}

void eGameMenu::setBoard(eGameBoard* const b) {
    mBoard = b;
    mPopDataW->setBoard(b);
    mEmplDataW->setBoard(b);
    mMiniMap->setBoard(b);
}

eMiniMap* eGameMenu::miniMap() const {
    return mMiniMap;
}

void eGameMenu::setMode(const eBuildingMode mode) {
    mMode = mode;
}
