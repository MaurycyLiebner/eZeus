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
    eBuildingMode fMode;
    std::string fName;
    std::function<void()> fPressedFunc;
    int fPrice;
    int fPriceSpace;
    const eTextureCollection* fColl;
    std::vector<eSPR> fSpr = {};
};

void tradePosts(std::vector<eSPR>& cs, eGameBoard& board) {
    const auto& wrld = board.getWorldBoard();
    int i = 0;
    for(const auto& c : wrld.cities()) {
        if(!board.hasTradePost(*c)) {
            if(!c->buys().empty() || !c->sells().empty()) {
                if(c->waterTrade()) {
                    const auto name = eLanguage::text("pier") + c->name();
                    const eSPR s{eBuildingMode::pier, name, 0, i};
                    cs.push_back(s);
                } else {
                    const auto name = eLanguage::text("trading_post") + c->name();
                    const eSPR s{eBuildingMode::tradePost, name, 0, i};
                    cs.push_back(s);
                }
            }
        }
        i++;
    }
}

class eSubButton {
public:
    eSubButton(const eBuildingMode mode,
               eButton* const button,
               const std::vector<eSPR>& children,
               eGameBoard& board) :
        mMode(mode),
        mButton(button),
        mChildren(children),
        mBoard(board) {}

    void updateVisible() {
        if(mMode == eBuildingMode::tradePost) {
            std::vector<eSPR> cs;
            tradePosts(cs, mBoard);
            mButton->setVisible(!cs.empty());
        } else if(mMode == eBuildingMode::none) {
            bool found = false;
            for(const auto& c : mChildren) {
                const bool s = mBoard.supportsBuilding(c.fMode);
                if(s) {
                    found = true;
                    break;
                }
            }
            mButton->setVisible(found);
        } else {
            const bool s = mBoard.supportsBuilding(mMode);
            mButton->setVisible(s);
        }
    }
private:
    const eBuildingMode mMode;
    eButton* const mButton;
    const std::vector<eSPR> mChildren;
    eGameBoard& mBoard;
};

eWidget* eGameMenu::createPriceWidget(const eInterfaceTextures& coll) {
    const auto r = new eWidget(window());
    r->setNoPadding();
    const auto plabel = new eLabel("0", window());
    plabel->setTinyFontSize();
    plabel->setTinyPadding();
    plabel->fitContent();
    const auto ilabel = new eLabel(window());
    ilabel->setTexture(coll.fDrachmasUnit);
    ilabel->setTinyPadding();
    ilabel->fitContent();
    r->addWidget(ilabel);
    r->addWidget(plabel);
    r->stackHorizontally();
    r->fitContent();
    plabel->align(eAlignment::vcenter);
    mPriceWidgets.push_back(r);
    mPriceLabels.push_back(plabel);
    r->hide();
    return r;
}

eWidget* eGameMenu::createSubButtons(
        const int resoltuionMult,
        const eButtonsDataVec& buttons) {
    const auto result = new eWidget(window());

    const int x = resoltuionMult*35;
    const int y = resoltuionMult*28;
    const std::vector<std::pair<int, int>> poses =
        {{0, 0}, {x, 0}, {0, y}, {x, y}};

    const int iMax = buttons.size();
    for(int i = 0; i < iMax; i++) {
        const auto& c = buttons[i];

        const auto b = eButton::sCreate(*c.fColl, window(), result);
        b->setPressAction(c.fPressedFunc);
        b->setMouseEnterAction([c, this]() {
            mNameLabel->setText(c.fName);
            displayPrice(c.fPrice, c.fPriceSpace);
        });
        b->setMouseLeaveAction([c, this]() {
            mNameLabel->setText("");
            displayPrice(0, c.fPriceSpace);
        });
        const auto& pos = poses[i];
        b->setX(pos.first);
        b->setY(pos.second);

        switch(c.fMode) {
        case eBuildingMode::palace:
            mPalaceButton = b;
            break;
        case eBuildingMode::stadium:
            mStadiumButton = b;
            break;
        default: break;
        }

        const auto subButton = new eSubButton(c.fMode, b, c.fSpr, *mBoard);
        subButton->updateVisible();
        mSubButtons.push_back(subButton);
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
    std::vector<eBuildButton*> ws;
    for(const auto& c : cs) {
        if(!mBoard->supportsBuilding(c.fMode)) continue;
        const auto bb = createBuildButton(c);
        ws.push_back(bb);
    }
    if(ws.empty()) return;
    const auto bw = new eBuildWidget(window());
    bw->initialize(ws);
    bw->exec(cmx - bw->width(), cmy - bw->height(), this);
    setBuildWidget(bw);
}

void eGameMenu::displayPrice(const int price, const int loc) {
    const auto w = mPriceWidgets[loc];
    const auto l = mPriceLabels[loc];
    if(price <= 0) {
        w->hide();
    } else {
        l->setText(std::to_string(price));
        w->show();
    }
}

eGameMenu::~eGameMenu() {
    for(const auto s : mSubButtons) {
        delete s;
    }
}

void eGameMenu::initialize(eGameBoard* const b) {
    mBoard = b;
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

    {
        const auto ww = new eWidget(window());
        ww->setNoPadding();
        const int x = mult*35;
        const int y = mult*28;
        const std::vector<std::pair<int, int>> poses =
            {{0, 0}, {x, 0}, {0, y}, {x, y}};
        for(const auto& p : poses) {
            const auto w = createPriceWidget(coll);
            ww->addWidget(w);
            w->setX(p.first);
            w->setY(p.second);
        }
        ww->fitContent();
        addWidget(ww);
        ww->setX(wx);
        ww->setY(wy + 29*mult);
    }

    mPopDataW = new ePopulationDataWidget(window());

    const auto diff = mBoard->difficulty();
    const int cost1 = eDifficultyHelpers::buildingCost(
                          diff, eBuildingType::commonHouse);
    const int cost2 = eDifficultyHelpers::buildingCost(
                          diff, eBuildingType::eliteHousing);

    const auto cha0 = [this]() {
        setMode(eBuildingMode::commonHousing);
    };
    const auto eha0 = [this]() {
        setMode(eBuildingMode::eliteHousing);
    };

    const auto buttonsVec0 = eButtonsDataVec{
                    {eBuildingMode::commonHousing,
                     eLanguage::text("common_housing"),
                     cha0, cost1, 0, &coll.fCommonHousing},
                    {eBuildingMode::eliteHousing,
                     eLanguage::text("elite_housing"),
                     eha0, cost2, 1, &coll.fEliteHousing}};
    const auto ww0 = createDataWidget(mPopDataW, buttonsVec0,
                                      "population_title");

    const std::vector<eSPR> ff1spr = {eSPR{eBuildingMode::wheatFarm, eLanguage::text("wheat_farm")},
                                      eSPR{eBuildingMode::carrotFarm, eLanguage::text("carrot_farm")},
                                      eSPR{eBuildingMode::onionFarm, eLanguage::text("onion_farm")}};

    const auto ff1 = [this, cmx, cmy, ff1spr]() {
        openBuildWidget(cmx, cmy, ff1spr);
    };

    const std::vector<eSPR> of1spr = {eSPR{eBuildingMode::vine, eLanguage::text("vine")},
                                      eSPR{eBuildingMode::oliveTree, eLanguage::text("olive_tree")},
                                      eSPR{eBuildingMode::orangeTree, eLanguage::text("orange_tree")},
                                      eSPR{eBuildingMode::orangeTendersLodge, eLanguage::text("orange_tenders_lodge")},
                                      eSPR{eBuildingMode::growersLodge, eLanguage::text("growers_lodge")}};

    const auto of1 = [this, cmx, cmy, of1spr]() {
        openBuildWidget(cmx, cmy, of1spr);
    };

    const std::vector<eSPR> af1spr = {eSPR{eBuildingMode::dairy, eLanguage::text("dairy")},
                                      eSPR{eBuildingMode::goat, eLanguage::text("goat")},
                                      eSPR{eBuildingMode::cardingShed, eLanguage::text("carding_shed")},
                                      eSPR{eBuildingMode::sheep, eLanguage::text("sheep")}};
    const auto af1 = [this, cmx, cmy, af1spr]() {
        openBuildWidget(cmx, cmy, af1spr);
    };

    const std::vector<eSPR> ah1spr = {eSPR{eBuildingMode::fishery, eLanguage::text("fishery")},
                                      eSPR{eBuildingMode::urchinQuay, eLanguage::text("urchin_quay")},
                                      eSPR{eBuildingMode::huntingLodge, eLanguage::text("hunting_lodge")}};

    const auto ah1 = [this, cmx, cmy, ah1spr]() {
        openBuildWidget(cmx, cmy, ah1spr);
    };



    mHusbDataW = new eHusbandryDataWidget(window());
    const auto buttonsVec1 = eButtonsDataVec{
                            {eBuildingMode::none,
                             eLanguage::text("farms"),
                             ff1, 0, 0, &coll.fFoodFarming, ff1spr},
                            {eBuildingMode::none,
                             eLanguage::text("orchards"),
                             of1, 0, 1, &coll.fOtherFarming, of1spr},
                            {eBuildingMode::none,
                             eLanguage::text("herding"),
                             af1, 0, 2, &coll.fAnimalFarming, af1spr},
                            {eBuildingMode::none,
                             eLanguage::text("land_and_sea"),
                             ah1, 0, 3, &coll.fAnimalHunting, ah1spr}};
    const auto ww1 = createDataWidget(mHusbDataW, buttonsVec1,
                                      "husbandry_title");

    const std::vector<eSPR> r2spr = {eSPR{eBuildingMode::mint, eLanguage::text("mint")},
                                     eSPR{eBuildingMode::foundry, eLanguage::text("foundry")},
                                     eSPR{eBuildingMode::timberMill, eLanguage::text("timber_mill")},
                                     eSPR{eBuildingMode::masonryShop, eLanguage::text("masonry_shop")}};
    const auto r2 = [this, cmx, cmy, r2spr]() {
        openBuildWidget(cmx, cmy, r2spr);
    };
    const std::vector<eSPR> p2spr = {eSPR{eBuildingMode::winery, eLanguage::text("winery")},
                                     eSPR{eBuildingMode::olivePress, eLanguage::text("olive_press")},
                                     eSPR{eBuildingMode::sculptureStudio, eLanguage::text("sculpture_studio")}};
    const auto p2 = [this, cmx, cmy, p2spr]() {
        openBuildWidget(cmx, cmy, p2spr);
    };
    const auto bg2 = [this]() {
        setMode(eBuildingMode::artisansGuild);
    };

    mEmplDataW = new eEmploymentDataWidget(window());
    const int cost3 = eDifficultyHelpers::buildingCost(
                          diff, eBuildingType::artisansGuild);
    const auto buttonsVec2 = eButtonsDataVec{
                            {eBuildingMode::none,
                             eLanguage::text("raw_materials"),
                             r2, 0, 0, &coll.fResources, r2spr},
                            {eBuildingMode::none,
                             eLanguage::text("workshops"),
                             p2, 0, 1, &coll.fProcessing, p2spr},
                            {eBuildingMode::artisansGuild,
                             eLanguage::text("artisans_guild"),
                             bg2, cost3, 2, &coll.fArtisansGuild}};
    const auto ww2 = createDataWidget(mEmplDataW, buttonsVec2,
                                      "industry_title");


    const auto g3 = [this]() {
        setMode(eBuildingMode::granary);
    };
    const auto ww3 = [this]() {
        setMode(eBuildingMode::warehouse);
    };
    const std::vector<eSPR> a3spr = {eSPR{eBuildingMode::commonAgora, eLanguage::text("common_agora")},
                                     eSPR{eBuildingMode::grandAgora, eLanguage::text("grand_agora")},
                                     eSPR{eBuildingMode::foodVendor, eLanguage::text("food_vendor")},
                                     eSPR{eBuildingMode::fleeceVendor, eLanguage::text("fleece_vendor")},
                                     eSPR{eBuildingMode::oilVendor, eLanguage::text("oil_vendor")},
                                     eSPR{eBuildingMode::wineVendor, eLanguage::text("wine_vendor")},
                                     eSPR{eBuildingMode::armsVendor, eLanguage::text("arms_vendor")},
                                     eSPR{eBuildingMode::horseTrainer, eLanguage::text("horse_trainer")}};
    const auto a3 = [this, cmx, cmy, a3spr]() {
        openBuildWidget(cmx, cmy, a3spr);
    };
    const auto t3 = [this, cmx, cmy]() {
        std::vector<eSPR> cs;
        tradePosts(cs, *mBoard);
        openBuildWidget(cmx, cmy, cs);
    };


    mStrgDataW = new eStorageDataWidget(window());

    const int cost4 = eDifficultyHelpers::buildingCost(
                          diff, eBuildingType::granary);
    const int cost5 = eDifficultyHelpers::buildingCost(
                          diff, eBuildingType::warehouse);
    const auto buttonsVec3 = eButtonsDataVec{
                            {eBuildingMode::granary,
                             eLanguage::text("granary"),
                             g3, cost4, 0, &coll.fGranary},
                            {eBuildingMode::warehouse,
                             eLanguage::text("storehouse"),
                             ww3, cost5, 1, &coll.fWarehouse},
                            {eBuildingMode::none,
                             eLanguage::text("agoras"),
                             a3, 0, 2, &coll.fAgoras, a3spr},
                            {eBuildingMode::tradePost,
                             eLanguage::text("trade"),
                             t3, 0, 3, &coll.fTrade}};
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
    const int cost6 = eDifficultyHelpers::buildingCost(
                          diff, eBuildingType::fountain);
    const int cost7 = eDifficultyHelpers::buildingCost(
                          diff, eBuildingType::hospital);
    const int cost8 = eDifficultyHelpers::buildingCost(
                          diff, eBuildingType::maintenanceOffice);
    const int cost9 = eDifficultyHelpers::buildingCost(
                          diff, eBuildingType::watchPost);
    const auto buttonsVec4 = eButtonsDataVec{
                            {eBuildingMode::fountain,
                             eLanguage::text("fountain"),
                             f4, cost6, 0, &coll.fFountain},
                            {eBuildingMode::hospital,
                             eLanguage::text("infirmary"),
                             h4, cost7, 1, &coll.fHospital},
                            {eBuildingMode::maintenanceOffice,
                             eLanguage::text("maintenance_office"),
                             ff4, cost8, 2, &coll.fFireFighter},
                            {eBuildingMode::watchpost,
                             eLanguage::text("watchpost"),
                             p4, cost9, 3, &coll.fPolice}};
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
    const int cost10 = eDifficultyHelpers::buildingCost(
                          diff, eBuildingType::palace);
    const int cost11 = eDifficultyHelpers::buildingCost(
                          diff, eBuildingType::taxOffice);
    const int cost12 = eDifficultyHelpers::buildingCost(
                          diff, eBuildingType::bridge);
    const auto buttonsVec5 = eButtonsDataVec{
                            {eBuildingMode::palace,
                             eLanguage::text("palace"),
                             p5, cost10, 0, &coll.fPalace},
                            {eBuildingMode::taxOffice,
                             eLanguage::text("tax_office"),
                             tc5, cost11, 1, &coll.fTaxCollector},
                            {eBuildingMode::bridge,
                             eLanguage::text("water_crossing"),
                             bb5, cost12, 2, &coll.fBridge}};
    const auto ww5 = createDataWidget(mAdminDataW, buttonsVec5,
                                      "administration_title");


    const std::vector<eSPR> p6spr = {eSPR{eBuildingMode::podium, eLanguage::text("podium")},
                                     eSPR{eBuildingMode::college, eLanguage::text("college")}};
    const auto p6 = [this, cmx, cmy, p6spr]() {
        openBuildWidget(cmx, cmy, p6spr);
    };
    const auto g6 = [this]() {
        setMode(eBuildingMode::gymnasium);
    };
    const std::vector<eSPR> d6spr = {eSPR{eBuildingMode::theater, eLanguage::text("theater")},
                                     eSPR{eBuildingMode::dramaSchool, eLanguage::text("drama_school")}};
    const auto d6 = [this, cmx, cmy, d6spr]() {
        openBuildWidget(cmx, cmy, d6spr);
    };
    const auto s6 = [this]() {
        setMode(eBuildingMode::stadium);
    };

    mCultureDataW = new eCultureDataWidget(window());
    const int cost13 = eDifficultyHelpers::buildingCost(
                          diff, eBuildingType::gymnasium);
    const int cost14 = eDifficultyHelpers::buildingCost(
                          diff, eBuildingType::stadium);
    const auto buttonsVec6 = eButtonsDataVec{
                            {eBuildingMode::none,
                             eLanguage::text("philosophy"),
                             p6, 0, 0, &coll.fPhilosophy, p6spr},
                            {eBuildingMode::gymnasium,
                             eLanguage::text("gymnasium"),
                             g6, cost13, 1, &coll.fGymnasium},
                            {eBuildingMode::none,
                             eLanguage::text("drama"),
                             d6, 0, 2, &coll.fDrama, d6spr},
                            {eBuildingMode::stadium,
                             eLanguage::text("stadium"),
                             s6, cost14, 3, &coll.fStadium}};
    const auto ww6 = createDataWidget(mCultureDataW, buttonsVec6,
                                      "culture_title");



    const std::vector<eSPR> t7spr = {eSPR{eBuildingMode::templeHephaestus, eLanguage::text("forge_of_hephaestus"), 13},
                     eSPR{eBuildingMode::templeArtemis, eLanguage::text("artemis_menagerie"), 20}};
    const auto t7 = [this, cmx, cmy, t7spr]() {
        openBuildWidget(cmx, cmy, t7spr);
    };
    const auto hs7 = [this, cmx, cmy]() {};


    mMythDataW = new eMythologyDataWidget(window());
    const auto buttonsVec7 = eButtonsDataVec{
                            {eBuildingMode::none,
                             eLanguage::text("sanctuaries"),
                             t7, 0, 0, &coll.fTemples, t7spr},
                            {eBuildingMode::none,
                             eLanguage::text("heros_hall"),
                             hs7, 0, 1, &coll.fHeroShrines}};
    const auto ww7 = createDataWidget(mMythDataW, buttonsVec7,
                                      "mythology_title");


    const std::vector<eSPR> f8spr = {eSPR{eBuildingMode::wall, eLanguage::text("wall")},
                     eSPR{eBuildingMode::tower, eLanguage::text("tower")},
                     eSPR{eBuildingMode::gatehouse, eLanguage::text("gatehouse")}};
    const auto f8 = [this, cmx, cmy, f8spr]() {
        openBuildWidget(cmx, cmy, f8spr);
    };
    const std::vector<eSPR> mp8spr = {eSPR{eBuildingMode::armory, eLanguage::text("armory")}};
    const auto mp8 = [this, cmx, cmy, mp8spr]() {
        openBuildWidget(cmx, cmy, mp8spr);
    };

    mMiltDataW = new eMilitaryDataWidget(window());
    const auto buttonsVec8 = eButtonsDataVec{
                        {eBuildingMode::none,
                         eLanguage::text("fortifications"),
                         f8, 0, 0, &coll.fFortifications, f8spr},
                        {eBuildingMode::none,
                         eLanguage::text("military_workshops"),
                         mp8, 0, 1, &coll.fMilitaryProduction, mp8spr}};
    const auto ww8 = createDataWidget(mMiltDataW, buttonsVec8,
                                      "military_title");

    const std::vector<eSPR> bb9spr = {eSPR{eBuildingMode::park, eLanguage::text("park")},
                                      eSPR{eBuildingMode::waterPark, eLanguage::text("water_park")},
                                      eSPR{eBuildingMode::doricColumn, eLanguage::text("doric_column")},
                                      eSPR{eBuildingMode::ionicColumn, eLanguage::text("ionic_column")},
                                      eSPR{eBuildingMode::corinthianColumn, eLanguage::text("corinthian_column")},
                                      eSPR{eBuildingMode::avenue, eLanguage::text("avenue")}};
    const auto bb9 = [this, cmx, cmy, bb9spr]() {
        openBuildWidget(cmx, cmy, bb9spr);
    };
    const std::vector<eSPR> r9spr = {eSPR{eBuildingMode::bench, eLanguage::text("bench")},
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
    const auto r9 = [this, cmx, cmy, r9spr]() {
        openBuildWidget(cmx, cmy, r9spr);
    };
    const std::vector<eSPR> m9spr = {eSPR{eBuildingMode::populationMonument, eLanguage::text("population_monument")},
                                     eSPR{eBuildingMode::commemorative2, "Commemorative 2"},
                                     eSPR{eBuildingMode::colonyMonument, eLanguage::text("colony_monument")},
                                     eSPR{eBuildingMode::athleteMonument, eLanguage::text("athlete_monument")},
                                     eSPR{eBuildingMode::conquestMonument, eLanguage::text("conquest_monument")},
                                     eSPR{eBuildingMode::happinessMonument, eLanguage::text("happiness_monument")},
                                     eSPR{eBuildingMode::commemorative7, "Commemorative 7"},
                                     eSPR{eBuildingMode::commemorative8, "Commemorative 8"},
                                     eSPR{eBuildingMode::scholarMonument, eLanguage::text("scholar_monument")}};
    const auto m9 = [this, cmx, cmy, m9spr]() {
        openBuildWidget(cmx, cmy, m9spr);
    };

    mApplDataW = new eAppealDataWidget(window());
    const auto buttonsVec = eButtonsDataVec{
                    {eBuildingMode::none,
                     eLanguage::text("beautification"),
                     bb9, 0, 0, &coll.fBeautification, bb9spr},
                    {eBuildingMode::none,
                     eLanguage::text("recreational_areas"),
                     r9, 0, 1, &coll.fRecreation, r9spr},
                    {eBuildingMode::none,
                     eLanguage::text("monuments"),
                     m9, 0, 2, &coll.fMonuments, m9spr}};
    const auto ww9 = createDataWidget(mApplDataW, buttonsVec,
                                      "aesthetics_title");

    mOverDataW = new eOverviewDataWidget(window());
    mMiniMap = new eMiniMap(window());
    mMiniMap->resize(dataWidWidth, 4*dataWidWidth/5);

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

    const auto setupButtonHover =
        [this](eCheckableButton* b0, const std::string& txt) {
        b0->setMouseEnterAction([this, txt]() {
            mNameLabel->setText(txt);
        });
        b0->setMouseLeaveAction([this]() {
            mNameLabel->setText("");
        });
    };

    setupButtonHover(b0, eLanguage::text("population_title"));
    setupButtonHover(b1, eLanguage::text("husbandry_title"));
    setupButtonHover(b2, eLanguage::text("industry_title"));
    setupButtonHover(b3, eLanguage::text("distribution_title"));
    setupButtonHover(b4, eLanguage::text("hygiene_safety_title"));
    setupButtonHover(b5, eLanguage::text("administration_title"));
    setupButtonHover(b6, eLanguage::text("culture_title"));
    setupButtonHover(b7, eLanguage::text("mythology_title"));
    setupButtonHover(b8, eLanguage::text("military_title"));
    setupButtonHover(b9, eLanguage::text("aesthetics_title"));
    setupButtonHover(b10, eLanguage::text("overview_title"));

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

    mPopDataW->setBoard(b);
    mEmplDataW->setBoard(b);
    mStrgDataW->setBoard(b);
    mAdminDataW->setBoard(b);
    mMiniMap->setBoard(b);
}

void eGameMenu::setGameWidget(eGameWidget* const gw) {
    mPopDataW->setGameWidget(gw);
    mEmplDataW->setGameWidget(gw);
    mStrgDataW->setGameWidget(gw);
    mApplDataW->setGameWidget(gw);
    mHySaDataW->setGameWidget(gw);
    mMiltDataW->setGameWidget(gw);
    mMythDataW->setGameWidget(gw);
    mAdminDataW->setGameWidget(gw);
    mCultureDataW->setGameWidget(gw);
    mOverDataW->setGameWidget(gw);

    mWorldButton->setPressAction([this]() {
        window()->showWorld();
    });
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

void eGameMenu::updateButtonsVisibility() {
    for(const auto s : mSubButtons) {
        s->updateVisible();
    }
    mPalaceButton->setVisible(!mBoard->hasPalace());
    mStadiumButton->setVisible(!mBoard->hasStadium());
}

void eGameMenu::setMode(const eBuildingMode mode) {
    closeBuildWidget();
    mMode = mode;
}

bool eGameMenu::mousePressEvent(const eMouseEvent& e) {
    closeBuildWidget();
    return eGameMenuBase::mouseEnterEvent(e);
}
