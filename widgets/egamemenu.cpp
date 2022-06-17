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
#include "widgets/datawidgets/estoragedatawidget.h"
#include "widgets/datawidgets/ehygienesafetydatawidget.h"
#include "widgets/datawidgets/eculturedatawidget.h"
#include "widgets/datawidgets/eadmindatawidget.h"
#include "widgets/datawidgets/ehusbandrydatawidget.h"
#include "widgets/datawidgets/emythologydatawidget.h"
#include "widgets/datawidgets/emilitarydatawidget.h"
#include "widgets/datawidgets/eoverviewdatawidget.h"
#include "eminimap.h"

#include "eeventwidget.h"

#include "egamewidget.h"

#include "elanguage.h"

#include "ebuildwidget.h"

struct eSubButtonData {
    std::string fName;
    std::function<void()> fPressedFunc;
    const eTextureCollection* fColl = nullptr;
};

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
        const auto b = eButton::sCreate(*c.fColl, window(), result);
        b->setPressAction(c.fPressedFunc);
        b->setMouseEnterAction([c, this]() {
            mNameLabel->setText(c.fName);
        });
        b->setMouseLeaveAction([c, this]() {
            mNameLabel->setText("");
        });
        const auto& pos = poses[i];
        b->setX(pos.first);
        b->setY(pos.second);
    }

    result->setNoPadding();
    result->fitContent();

    return result;
}

void eGameMenu::addAction(const eSPR& c, const int mult,
                          const eInterfaceTextures& coll,
                          eContextMenu* const cm) {
    auto& a = cm->addAction(c.fName, [this, c]() {
        setMode(c.fMode);
        mCityId = c.fCity;
    });
    const auto diff = mBoard->difficulty();
    const auto mode = c.fMode;
    const auto t = eBuildingModeHelpers::toBuildingType(mode);
    const int cost = eDifficultyHelpers::buildingCost(diff, t);
    a.addTexture(mult*20, coll.fDrachmasUnit);
    a.addText(0, std::to_string(cost));
}

eBuildButton* eGameMenu::createBuildButton(const eSPR& c) {
    const auto bb = new eBuildButton(window());
    const auto diff = mBoard->difficulty();
    const auto mode = c.fMode;
    const auto t = eBuildingModeHelpers::toBuildingType(mode);
    const int cost = eDifficultyHelpers::buildingCost(diff, t);
    bb->initialize(c.fName, c.fMarbleCost, cost);
    bb->setPressAction([this, c]() {
        setMode(c.fMode);
        mCityId = c.fCity;
        closeBuildWidget();
    });
    return bb;
}

void eGameMenu::openBuildWidget(const int cmx, const int cmy,
                                const std::vector<eSPR>& cs) {
    const auto bw = new eBuildWidget(window());
    std::vector<eBuildButton*> ws;
    for(const auto& c : cs) {
        const auto bb = createBuildButton(c);
        ws.push_back(bb);
    }
    bw->initialize(ws);
    bw->exec(cmx - bw->width(), cmy - bw->height(), this);
    setBuildWidget(bw);
}

void eGameMenu::initialize() {
    eGameMenuBase::initialize();

    int iRes;
    int mult;
    iResAndMult(iRes, mult);

    const auto& intrfc = eGameTextures::interface();
    const auto& coll = intrfc[iRes];
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

    const int dataWidWidth = 65*mult;
    const int dataWidHeight = 113*mult;

    const int wwHeight = 190*mult;
    const int wy = dataWidHeight + 37*mult;
    const int wx = 24*mult;

    const auto createDataWidgetBase =
        [&](eDataWidget* const dataW,
            eWidget* const w9,
            const std::string& name) {
        const auto ww9 = new eWidget(window());
        const auto alabel = new eLabel(window());
        alabel->setText(eLanguage::text(name));
        alabel->setSmallFontSize();
        alabel->fitContent();
        ww9->addWidget(alabel);
        dataW->setWidth(dataWidWidth);
        dataW->setHeight(dataWidHeight);
        dataW->initialize();
        ww9->addWidget(dataW);
        ww9->setWidth(dataWidWidth);
        ww9->setHeight(wwHeight);
        ww9->stackVertically();
        alabel->align(eAlignment::hcenter);
        ww9->addWidget(w9);
        w9->setY(wy);
        ww9->fitContent();
        return ww9;
    };

    const auto createDataWidget =
        [&](eDataWidget* const dataW,
            const eButtonsDataVec& buttonsVec,
            const std::string& name) {
        const auto w9 = createSubButtons(mult, buttonsVec);
        return createDataWidgetBase(dataW, w9, name);
    };

    mNameLabel = new eFramedLabel(window());
    mNameLabel->setType(eFrameType::inner);
    mNameLabel->setVerySmallFontSize();
    mNameLabel->setText("Recreational Areas");
    mNameLabel->setVeryTinyPadding();
    mNameLabel->fitContent();
    mNameLabel->setText("");
    mNameLabel->setWidth(dataWidWidth);
    mNameLabel->setX(wx);
    mNameLabel->setY(wy);
    addWidget(mNameLabel);

    mPopDataW = new ePopulationDataWidget(window());
    mPopDataW->setBoard(mBoard);
    const auto buttonsVec0 = eButtonsDataVec{
                    {eLanguage::text("common_housing"),
                     cha0, &coll.fCommonHousing},
                    {eLanguage::text("elite_housing"),
                     eha0, &coll.fEliteHousing}};
    const auto ww0 = createDataWidget(mPopDataW, buttonsVec0,
                                      "population_title");

    const auto ff1 = [this, cmx, cmy]() {
        const std::vector<eSPR> cs = {eSPR{eBuildingMode::wheatFarm, eLanguage::text("wheat_farm")},
                         eSPR{eBuildingMode::carrotFarm, eLanguage::text("carrot_farm")},
                         eSPR{eBuildingMode::onionFarm, eLanguage::text("onion_farm")}};
        openBuildWidget(cmx, cmy, cs);
    };
    const auto of1 = [this, cmx, cmy]() {
        const std::vector<eSPR> cs = {eSPR{eBuildingMode::vine, eLanguage::text("vine")},
                         eSPR{eBuildingMode::oliveTree, eLanguage::text("olive_tree")},
                         eSPR{eBuildingMode::orangeTree, eLanguage::text("orange_tree")},
                         eSPR{eBuildingMode::orangeTendersLodge, eLanguage::text("orange_tenders_lodge")},
                         eSPR{eBuildingMode::growersLodge, eLanguage::text("growers_lodge")}};
        openBuildWidget(cmx, cmy, cs);
    };
    const auto af1 = [this, cmx, cmy]() {
        const std::vector<eSPR> cs = {eSPR{eBuildingMode::dairy, eLanguage::text("dairy")},
                         eSPR{eBuildingMode::goat, eLanguage::text("goat")},
                         eSPR{eBuildingMode::cardingShed, eLanguage::text("carding_shed")},
                         eSPR{eBuildingMode::sheep, eLanguage::text("sheep")}};
        openBuildWidget(cmx, cmy, cs);
    };
    const auto ah1 = [this, cmx, cmy]() {
        const std::vector<eSPR> cs = {eSPR{eBuildingMode::fishery, eLanguage::text("fishery")},
                         eSPR{eBuildingMode::urchinQuay, eLanguage::text("urchin_quay")},
                         eSPR{eBuildingMode::huntingLodge, eLanguage::text("hunting_lodge")}};
        openBuildWidget(cmx, cmy, cs);
    };



    mHusbDataW = new eHusbandryDataWidget(window());
    const auto buttonsVec1 = eButtonsDataVec{
                            {eLanguage::text("farms"),
                             ff1, &coll.fFoodFarming},
                            {eLanguage::text("orchards"),
                             of1, &coll.fOtherFarming},
                            {eLanguage::text("herding"),
                             af1, &coll.fAnimalFarming},
                            {eLanguage::text("land_and_sea"),
                             ah1, &coll.fAnimalHunting}};
    const auto ww1 = createDataWidget(mHusbDataW, buttonsVec1,
                                      "husbandry_title");


    const auto r2 = [this, cmx, cmy]() {
        const std::vector<eSPR> cs = {eSPR{eBuildingMode::mint, eLanguage::text("mint")},
                         eSPR{eBuildingMode::foundry, eLanguage::text("foundry")},
                         eSPR{eBuildingMode::timberMill, eLanguage::text("timber_mill")},
                         eSPR{eBuildingMode::masonryShop, eLanguage::text("masonry_shop")}};
        openBuildWidget(cmx, cmy, cs);
    };
    const auto p2 = [this, cmx, cmy]() {
        const std::vector<eSPR> cs = {eSPR{eBuildingMode::winery, eLanguage::text("winery")},
                         eSPR{eBuildingMode::olivePress, eLanguage::text("olive_press")},
                         eSPR{eBuildingMode::sculptureStudio, eLanguage::text("sculpture_studio")}};
        openBuildWidget(cmx, cmy, cs);
    };
    const auto bg2 = [this]() {
        setMode(eBuildingMode::artisansGuild);
    };

    mEmplDataW = new eEmploymentDataWidget(window());
    mEmplDataW->setBoard(mBoard);
    const auto buttonsVec2 = eButtonsDataVec{
                            {eLanguage::text("raw_materials"),
                             r2, &coll.fResources},
                            {eLanguage::text("workshops"),
                             p2, &coll.fProcessing},
                            {eLanguage::text("artisans_guild"),
                             bg2, &coll.fArtisansGuild}};
    const auto ww2 = createDataWidget(mEmplDataW, buttonsVec2,
                                      "industry_title");


    const auto g3 = [this]() {
        setMode(eBuildingMode::granary);
    };
    const auto ww3 = [this]() {
        setMode(eBuildingMode::warehouse);
    };
    const auto a3 = [this, cmx, cmy]() {
        const std::vector<eSPR> cs = {eSPR{eBuildingMode::foodVendor, eLanguage::text("food_vendor")},
                         eSPR{eBuildingMode::fleeceVendor, eLanguage::text("fleece_vendor")},
                         eSPR{eBuildingMode::oilVendor, eLanguage::text("oil_vendor")},
                         eSPR{eBuildingMode::wineVendor, eLanguage::text("wine_vendor")},
                         eSPR{eBuildingMode::armsVendor, eLanguage::text("arms_vendor")},
                         eSPR{eBuildingMode::horseTrainer, eLanguage::text("horse_trainer")}};
        openBuildWidget(cmx, cmy, cs);
    };
    const auto t3 = [this, cmx, cmy]() {
        std::vector<eSPR> cs;
        const auto& wrld = mBoard->getWorldBoard();
        int i = 0;
        for(const auto& c : wrld.cities()) {
            if(!c->buys().empty() || !c->sells().empty()) {
                const auto name = eLanguage::text("trading_post") + c->name();
                const eSPR s{eBuildingMode::tradePost, name, 0, i};
                cs.push_back(s);
            }
            i++;
        }
        openBuildWidget(cmx, cmy, cs);
    };


    mStrgDataW = new eStorageDataWidget(window());
    mStrgDataW->setBoard(mBoard);
    const auto buttonsVec3 = eButtonsDataVec{
                            {eLanguage::text("granary"),
                             g3, &coll.fGranary},
                            {eLanguage::text("storehouse"),
                             ww3, &coll.fWarehouse},
                            {eLanguage::text("agoras"),
                             a3, &coll.fAgoras},
                            {eLanguage::text("trade"),
                             t3, &coll.fTrade}};
    const auto www3 = createDataWidget(mStrgDataW, buttonsVec3,
                                       "distribution_title");


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

    mHySaDataW = new eHygieneSafetyDataWidget(window());
    const auto buttonsVec4 = eButtonsDataVec{
                            {eLanguage::text("fountain"),
                             f4, &coll.fFountain},
                            {eLanguage::text("infirmary"),
                             h4, &coll.fHospital},
                            {eLanguage::text("maintenance_office"),
                             ff4, &coll.fFireFighter},
                            {eLanguage::text("watchpost"),
                             p4, &coll.fPolice}};
    const auto ww4 = createDataWidget(mHySaDataW, buttonsVec4,
                                      "hygiene_safety_title");

    const auto p5 = [this]() {
        setMode(eBuildingMode::palace);
    };
    const auto tc5 = [this]() {
        setMode(eBuildingMode::taxOffice);
    };
    const auto bb5 = [this]() {};

    mAdminDataW = new eAdminDataWidget(window());
    mAdminDataW->setBoard(mBoard);
    const auto buttonsVec5 = eButtonsDataVec{
                            {eLanguage::text("palace"),
                             p5, &coll.fPalace},
                            {eLanguage::text("tax_office"),
                             tc5, &coll.fTaxCollector},
                            {eLanguage::text("water_crossing"),
                             bb5, &coll.fBridge}};
    const auto ww5 = createDataWidget(mAdminDataW, buttonsVec5,
                                      "administration_title");


    const auto p6 = [this, cmx, cmy]() {
        const std::vector<eSPR> cs = {eSPR{eBuildingMode::podium, eLanguage::text("podium")},
                         eSPR{eBuildingMode::college, eLanguage::text("college")}};
        openBuildWidget(cmx, cmy, cs);
    };
    const auto g6 = [this]() {
        setMode(eBuildingMode::gymnasium);
    };
    const auto d6 = [this, cmx, cmy]() {
        const std::vector<eSPR> cs = {eSPR{eBuildingMode::theater, eLanguage::text("theater")},
                         eSPR{eBuildingMode::dramaSchool, eLanguage::text("drama_school")}};
        openBuildWidget(cmx, cmy, cs);
    };
    const auto s6 = [this]() {
        setMode(eBuildingMode::stadium);
    };

    mCultureDataW = new eCultureDataWidget(window());
    const auto buttonsVec6 = eButtonsDataVec{
                            {eLanguage::text("philosophy"),
                             p6, &coll.fPhilosophy},
                            {eLanguage::text("gymnasium"),
                             g6, &coll.fGymnasium},
                            {eLanguage::text("drama"),
                             d6, &coll.fDrama},
                            {eLanguage::text("stadium"),
                             s6, &coll.fStadium}};
    const auto ww6 = createDataWidget(mCultureDataW, buttonsVec6,
                                      "culture_title");


    const auto t7 = [this, cmx, cmy]() {
        const std::vector<eSPR> cs = {eSPR{eBuildingMode::templeHephaestus, eLanguage::text("forge_of_hephaestus"), 13},
                         eSPR{eBuildingMode::templeArtemis, eLanguage::text("artemis_menagerie"), 20}};
        openBuildWidget(cmx, cmy, cs);
    };
    const auto hs7 = [this, cmx, cmy]() {};


    mMythDataW = new eMythologyDataWidget(window());
    const auto buttonsVec7 = eButtonsDataVec{
                            {eLanguage::text("sanctuaries"),
                             t7, &coll.fTemples},
                            {eLanguage::text("heros_hall"),
                             hs7, &coll.fHeroShrines}};
    const auto ww7 = createDataWidget(mMythDataW, buttonsVec7,
                                      "mythology_title");


    const auto f8 = [this, cmx, cmy]() {
        const std::vector<eSPR> cs = {eSPR{eBuildingMode::wall, eLanguage::text("wall")},
                         eSPR{eBuildingMode::tower, eLanguage::text("tower")},
                         eSPR{eBuildingMode::gatehouse, eLanguage::text("gatehouse")}};
        openBuildWidget(cmx, cmy, cs);
    };
    const auto mp8 = [this, cmx, cmy]() {
        const std::vector<eSPR> cs = {eSPR{eBuildingMode::armory, eLanguage::text("armory")}};
        openBuildWidget(cmx, cmy, cs);
    };

    mMiltDataW = new eMilitaryDataWidget(window());
    const auto buttonsVec8 = eButtonsDataVec{
                        {eLanguage::text("fortifications"),
                         f8, &coll.fFortifications},
                        {eLanguage::text("military_workshops"),
                         mp8, &coll.fMilitaryProduction}};
    const auto ww8 = createDataWidget(mMiltDataW, buttonsVec8,
                                      "military_title");

    const auto bb9 = [this, cmx, cmy]() {
        const std::vector<eSPR> cs = {eSPR{eBuildingMode::park, eLanguage::text("park")},
                         eSPR{eBuildingMode::waterPark, eLanguage::text("water_park")},
                         eSPR{eBuildingMode::doricColumn, eLanguage::text("doric_column")},
                         eSPR{eBuildingMode::ionicColumn, eLanguage::text("ionic_column")},
                         eSPR{eBuildingMode::corinthianColumn, eLanguage::text("corinthian_column")},
                         eSPR{eBuildingMode::avenue, eLanguage::text("avenue")}};
        openBuildWidget(cmx, cmy, cs);
    };
    const auto r9 = [this, cmx, cmy]() {
        const auto cm = new eContextMenu(window());
        const std::vector<eSPR> cs = {eSPR{eBuildingMode::bench, eLanguage::text("bench")},
                         eSPR{eBuildingMode::birdBath, eLanguage::text("bird_bath")},
                         eSPR{eBuildingMode::shortObelisk, eLanguage::text("short_obelisk")},
                         eSPR{eBuildingMode::tallObelisk, eLanguage::text("tall_obelisk")},
                         eSPR{eBuildingMode::flowerGarden, eLanguage::text("flower_garden")},
                         eSPR{eBuildingMode::gazebo, eLanguage::text("gazebo")},
                         eSPR{eBuildingMode::shellGarden, eLanguage::text("shell_garden")},
                         eSPR{eBuildingMode::sundial, eLanguage::text("sundial")},
                         eSPR{eBuildingMode::hedgeMaze, eLanguage::text("hedge_maze")},
                         eSPR{eBuildingMode::dolphinSculpture, eLanguage::text("dolphin_sculpture")},
                         eSPR{eBuildingMode::spring, eLanguage::text("spring")},
                         eSPR{eBuildingMode::topiary, eLanguage::text("topiary")},
                         eSPR{eBuildingMode::fishPond, eLanguage::text("fish_pond")},
                         eSPR{eBuildingMode::baths, eLanguage::text("baths")},
                         eSPR{eBuildingMode::stoneCircle, eLanguage::text("stone_circle")}};
        openBuildWidget(cmx, cmy, cs);
    };
    const auto m9 = [this, cmx, cmy]() {
        const std::vector<eSPR> cs = {eSPR{eBuildingMode::populationMonument, eLanguage::text("population_monument")},
                         eSPR{eBuildingMode::commemorative2, "Commemorative 2"},
                         eSPR{eBuildingMode::colonyMonument, eLanguage::text("colony_monument")},
                         eSPR{eBuildingMode::athleteMonument, eLanguage::text("athlete_monument")},
                         eSPR{eBuildingMode::conquestMonument, eLanguage::text("conquest_monument")},
                         eSPR{eBuildingMode::happinessMonument, eLanguage::text("happiness_monument")},
                         eSPR{eBuildingMode::commemorative7, "Commemorative 7"},
                         eSPR{eBuildingMode::commemorative8, "Commemorative 8"},
                         eSPR{eBuildingMode::scholarMonument, eLanguage::text("scholar_monument")}};
        openBuildWidget(cmx, cmy, cs);
    };

    mApplDataW = new eAppealDataWidget(window());
    const auto buttonsVec = eButtonsDataVec{
                    {eLanguage::text("beautification"),
                     bb9, &coll.fBeautification},
                    {eLanguage::text("recreational_areas"),
                     r9, &coll.fRecreation},
                    {eLanguage::text("monuments"),
                     m9, &coll.fMonuments}};
    const auto ww9 = createDataWidget(mApplDataW, buttonsVec,
                                      "aesthetics_title");

    mOverDataW = new eOverviewDataWidget(window());
    mMiniMap = new eMiniMap(window());
    mMiniMap->resize(dataWidWidth, dataWidWidth);

    const auto ww10 = createDataWidgetBase(mOverDataW, mMiniMap,
                                           "overview_title");

    mWidgets.push_back(ww0);
    mWidgets.push_back(ww1);
    mWidgets.push_back(ww2);
    mWidgets.push_back(www3);
    mWidgets.push_back(ww4);
    mWidgets.push_back(ww5);
    mWidgets.push_back(ww6);
    mWidgets.push_back(ww7);
    mWidgets.push_back(ww8);
    mWidgets.push_back(ww9);
    mWidgets.push_back(ww10);

    for(const auto w : mWidgets) {
        addWidget(w);
        w->move(wx, 12*mult);
        w->hide();
    }

    const auto b0 = addButton(coll.fPopulation, ww0);
    const auto b1 = addButton(coll.fHusbandry, ww1);
    const auto b2 = addButton(coll.fIndustry, ww2);
    const auto b3 = addButton(coll.fDistribution, www3);
    const auto b4 = addButton(coll.fHygieneSafety, ww4);
    const auto b5 = addButton(coll.fAdministration, ww5);
    const auto b6 = addButton(coll.fCulture, ww6);
    const auto b7 = addButton(coll.fMythology, ww7);
    const auto b8 = addButton(coll.fMilitary, ww8);
    const auto b9 = addButton(coll.fAesthetics, ww9);
    const auto b10 = addButton(coll.fOverview, ww10);

    b10->setChecked(true);
    ww10->setVisible(true);

    connectAndLayoutButtons();

    {
        const auto btmButtons = new eWidget(window());
        btmButtons->setPadding(0);

        const auto b = eButton::sCreate(coll.fBuildRoad, window(), btmButtons);
        b->setPressAction([this]() {
            setMode(eBuildingMode::road);
        });
        eButton::sCreate(coll.fRoadBlock, window(), btmButtons);
        const auto e = eButton::sCreate(coll.fClear, window(), btmButtons);
        e->setPressAction([this]() {
            setMode(eBuildingMode::erase);
        });
        eButton::sCreate(coll.fUndo, window(), btmButtons);

        const int x = mult*24;
        const int y = std::round(mult*217.5);
        btmButtons->resize(4*b->width(), b->height());
        btmButtons->move(x, y);
        btmButtons->layoutHorizontally();
        addWidget(btmButtons);
    }

    {
        const auto butts = new eWidget(window());
        const auto info = eCheckableButton::sCreate(coll.fShowInfo, window(), butts);
        const auto map = eCheckableButton::sCreate(coll.fShowMap, window(), butts);
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
        const auto m = eCheckableButton::sCreate(coll.fMessages, window(), this);
        m->move(mult*73, mult*239);
    }
    {
        const auto butts = new eWidget(window());
        butts->setPadding(0);
        const auto goals = eCheckableButton::sCreate(coll.fGoals, window(), butts);
        const auto rotate = eCheckableButton::sCreate(coll.fRotation, window(), butts);
        mWorldButton = eButton::sCreate(coll.fWorld, window(), butts);
        const int w = goals->width() + rotate->width() + mWorldButton->width() + 5;
        butts->resize(w, mWorldButton->height());
        butts->layoutHorizontally();
        butts->setX(mult*5);
        butts->setY(std::round(mult*282.5));
        addWidget(butts);
    }

    {
        mEventW = new eEventWidget(window());
        mEventW->setNoPadding();
        mEventW->setX(mult*5);
        mEventW->setY(mult*240);
        mEventW->setWidth(dataWidWidth);
        addWidget(mEventW);
    }
}

void eGameMenu::setGameWidget(eGameWidget* const gw) {
    mPopDataW->setGameWidget(gw);
    mEmplDataW->setGameWidget(gw);
    mStrgDataW->setGameWidget(gw);
    mApplDataW->setGameWidget(gw);
    mHySaDataW->setGameWidget(gw);
    mAdminDataW->setGameWidget(gw);
    mCultureDataW->setGameWidget(gw);

    mWorldButton->setPressAction([this]() {
        window()->showWorld();
    });
}

void eGameMenu::setBoard(eGameBoard* const b) {
    mBoard = b;
    mPopDataW->setBoard(b);
    mEmplDataW->setBoard(b);
    mStrgDataW->setBoard(b);
    mAdminDataW->setBoard(b);
    mMiniMap->setBoard(b);
}

eMiniMap* eGameMenu::miniMap() const {
    return mMiniMap;
}

void eGameMenu::pushEvent(const eEvent e, eTile* const tile) {
    mEventW->pushEvent(e, tile);
}

void eGameMenu::setViewTileHandler(const eViewTileHandler& h) {
    mEventW->setViewTileHandler(h);
}

void eGameMenu::closeBuildWidget() {
    if(!mBuildWidget) return;
    mBuildWidget->deleteLater();
    mBuildWidget = nullptr;
}

void eGameMenu::setBuildWidget(eBuildWidget* const bw) {
    closeBuildWidget();
    mBuildWidget = bw;
}

void eGameMenu::setMode(const eBuildingMode mode) {
    closeBuildWidget();
    mMode = mode;
}

bool eGameMenu::mousePressEvent(const eMouseEvent& e) {
    closeBuildWidget();
    return eGameMenuBase::mouseEnterEvent(e);
}
