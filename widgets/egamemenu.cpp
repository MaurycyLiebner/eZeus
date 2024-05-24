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
                    const auto name = eLanguage::zeusText(28, 60) + " " + c->name();
                    const eSPR s{eBuildingMode::pier, name, 0, i};
                    cs.push_back(s);
                } else {
                    const auto name = eLanguage::zeusText(28, 62) + " " + c->name();
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

void eGameMenu::setModeChangedAction(const eAction& func) {
    mModeChangeAct = func;
}

void eGameMenu::updateRequestButtons() {
    mOverDataW->updateRequestButtons();
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
    const int cmy = 5*height()/8;

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
        alabel->setText(name);
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

    mPopDataW = new ePopulationDataWidget(*b, window());

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
                     eLanguage::zeusText(28, 2),
                     cha0, cost1, 0, &coll.fCommonHousing},
                    {eBuildingMode::eliteHousing,
                     eLanguage::zeusText(28, 9),
                     eha0, cost2, 1, &coll.fEliteHousing}};
    const auto ww0 = createDataWidget(mPopDataW, buttonsVec0,
                                      eLanguage::zeusText(88, 0));

    const std::vector<eSPR> ff1spr = {eSPR{eBuildingMode::wheatFarm, eLanguage::zeusText(28, 31)},
                                      eSPR{eBuildingMode::carrotFarm, eLanguage::zeusText(28, 33)},
                                      eSPR{eBuildingMode::onionFarm, eLanguage::zeusText(28, 32)}};

    const auto ff1 = [this, cmx, cmy, ff1spr]() {
        openBuildWidget(cmx, cmy, ff1spr);
    };

    const std::vector<eSPR> of1spr = {eSPR{eBuildingMode::vine, eLanguage::zeusText(28, 35)},
                                      eSPR{eBuildingMode::oliveTree, eLanguage::zeusText(28, 36)},
                                      eSPR{eBuildingMode::orangeTree, eLanguage::zeusText(28, 217)},
                                      eSPR{eBuildingMode::orangeTendersLodge, eLanguage::zeusText(28, 214)},
                                      eSPR{eBuildingMode::growersLodge, eLanguage::zeusText(28, 37)}};

    const auto of1 = [this, cmx, cmy, of1spr]() {
        openBuildWidget(cmx, cmy, of1spr);
    };

    const std::vector<eSPR> af1spr = {eSPR{eBuildingMode::dairy, eLanguage::zeusText(28, 42)},
                                      eSPR{eBuildingMode::goat, eLanguage::zeusText(28, 39)},
                                      eSPR{eBuildingMode::cardingShed, eLanguage::zeusText(28, 41)},
                                      eSPR{eBuildingMode::sheep, eLanguage::zeusText(28, 40)}};
    const auto af1 = [this, cmx, cmy, af1spr]() {
        openBuildWidget(cmx, cmy, af1spr);
    };

    const std::vector<eSPR> ah1spr = {eSPR{eBuildingMode::fishery, eLanguage::zeusText(28, 44)},
                                      eSPR{eBuildingMode::urchinQuay, eLanguage::zeusText(28, 45)},
                                      eSPR{eBuildingMode::huntingLodge, eLanguage::zeusText(28, 46)}};

    const auto ah1 = [this, cmx, cmy, ah1spr]() {
        openBuildWidget(cmx, cmy, ah1spr);
    };



    mHusbDataW = new eHusbandryDataWidget(*b, window());
    const auto buttonsVec1 = eButtonsDataVec{
                            {eBuildingMode::none,
                             eLanguage::zeusText(28, 30),
                             ff1, 0, 0, &coll.fFoodFarming, ff1spr},
                            {eBuildingMode::none,
                             eLanguage::zeusText(28, 34),
                             of1, 0, 1, &coll.fOtherFarming, of1spr},
                            {eBuildingMode::none,
                             eLanguage::zeusText(28, 38),
                             af1, 0, 2, &coll.fAnimalFarming, af1spr},
                            {eBuildingMode::none,
                             eLanguage::zeusText(28, 43),
                             ah1, 0, 3, &coll.fAnimalHunting, ah1spr}};
    const auto ww1 = createDataWidget(mHusbDataW, buttonsVec1,
                                      eLanguage::zeusText(88, 1));

    const std::vector<eSPR> r2spr = {eSPR{eBuildingMode::mint, eLanguage::zeusText(28, 48)},
                                     eSPR{eBuildingMode::foundry, eLanguage::zeusText(28, 50)},
                                     eSPR{eBuildingMode::timberMill, eLanguage::zeusText(28, 51)},
                                     eSPR{eBuildingMode::masonryShop, eLanguage::zeusText(28, 49)}};
    const auto r2 = [this, cmx, cmy, r2spr]() {
        openBuildWidget(cmx, cmy, r2spr);
    };
    const std::vector<eSPR> p2spr = {eSPR{eBuildingMode::winery, eLanguage::zeusText(28, 53)},
                                     eSPR{eBuildingMode::olivePress, eLanguage::zeusText(28, 54)},
                                     eSPR{eBuildingMode::sculptureStudio, eLanguage::zeusText(28, 55)}};
    const auto p2 = [this, cmx, cmy, p2spr]() {
        openBuildWidget(cmx, cmy, p2spr);
    };
    const auto bg2 = [this]() {
        setMode(eBuildingMode::artisansGuild);
    };

    mEmplDataW = new eEmploymentDataWidget(*b, window());
    const int cost3 = eDifficultyHelpers::buildingCost(
                          diff, eBuildingType::artisansGuild);
    const auto buttonsVec2 = eButtonsDataVec{
                            {eBuildingMode::none,
                             eLanguage::zeusText(28, 47),
                             r2, 0, 0, &coll.fResources, r2spr},
                            {eBuildingMode::none,
                             eLanguage::zeusText(28, 52),
                             p2, 0, 1, &coll.fProcessing, p2spr},
                            {eBuildingMode::artisansGuild,
                             eLanguage::zeusText(28, 56),
                             bg2, cost3, 2, &coll.fArtisansGuild}};
    const auto ww2 = createDataWidget(mEmplDataW, buttonsVec2,
                                      eLanguage::zeusText(88, 2));


    const auto g3 = [this]() {
        setMode(eBuildingMode::granary);
    };
    const auto ww3 = [this]() {
        setMode(eBuildingMode::warehouse);
    };
    const std::vector<eSPR> a3spr = {eSPR{eBuildingMode::commonAgora, eLanguage::zeusText(28, 63)},
                                     eSPR{eBuildingMode::grandAgora, eLanguage::zeusText(28, 64)},
                                     eSPR{eBuildingMode::foodVendor, eLanguage::zeusText(28, 68)},
                                     eSPR{eBuildingMode::fleeceVendor, eLanguage::zeusText(28, 69)},
                                     eSPR{eBuildingMode::oilVendor, eLanguage::zeusText(28, 70)},
                                     eSPR{eBuildingMode::wineVendor, eLanguage::zeusText(28, 71)},
                                     eSPR{eBuildingMode::armsVendor, eLanguage::zeusText(28, 72)},
                                     eSPR{eBuildingMode::horseTrainer, eLanguage::zeusText(28, 73)}};
    const auto a3 = [this, cmx, cmy, a3spr]() {
        openBuildWidget(cmx, cmy, a3spr);
    };
    const auto t3 = [this, cmx, cmy]() {
        std::vector<eSPR> cs;
        tradePosts(cs, *mBoard);
        openBuildWidget(cmx, cmy, cs);
    };


    mStrgDataW = new eStorageDataWidget(*b, window());

    const int cost4 = eDifficultyHelpers::buildingCost(
                          diff, eBuildingType::granary);
    const int cost5 = eDifficultyHelpers::buildingCost(
                          diff, eBuildingType::warehouse);
    const auto buttonsVec3 = eButtonsDataVec{
                            {eBuildingMode::granary,
                             eLanguage::zeusText(28, 57),
                             g3, cost4, 0, &coll.fGranary},
                            {eBuildingMode::warehouse,
                             eLanguage::zeusText(28, 58),
                             ww3, cost5, 1, &coll.fWarehouse},
                            {eBuildingMode::none,
                             eLanguage::zeusText(28, 67),
                             a3, 0, 2, &coll.fAgoras, a3spr},
                            {eBuildingMode::tradePost,
                             eLanguage::zeusText(28, 26),
                             t3, 0, 3, &coll.fTrade}};
    const auto www3 = createDataWidget(mStrgDataW, buttonsVec3,
                                       eLanguage::zeusText(88, 3));


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

    mHySaDataW = new eHygieneSafetyDataWidget(*b, window());
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
                             eLanguage::zeusText(28, 74),
                             f4, cost6, 0, &coll.fFountain},
                            {eBuildingMode::hospital,
                             eLanguage::zeusText(28, 76),
                             h4, cost7, 1, &coll.fHospital},
                            {eBuildingMode::maintenanceOffice,
                             eLanguage::zeusText(28, 121),
                             ff4, cost8, 2, &coll.fFireFighter},
                            {eBuildingMode::watchpost,
                             eLanguage::zeusText(28, 124),
                             p4, cost9, 3, &coll.fPolice}};
    const auto ww4 = createDataWidget(mHySaDataW, buttonsVec4,
                                      eLanguage::zeusText(88, 4));

    const auto p5 = [this]() {
        setMode(eBuildingMode::palace);
    };
    const auto tc5 = [this]() {
        setMode(eBuildingMode::taxOffice);
    };
    const auto bb5 = [this]() {
        setMode(eBuildingMode::bridge);
    };

    mAdminDataW = new eAdminDataWidget(*b, window());
    const int cost10 = eDifficultyHelpers::buildingCost(
                          diff, eBuildingType::palace);
    const int cost11 = eDifficultyHelpers::buildingCost(
                          diff, eBuildingType::taxOffice);
    const int cost12 = eDifficultyHelpers::buildingCost(
                          diff, eBuildingType::bridge);
    const auto buttonsVec5 = eButtonsDataVec{
                            {eBuildingMode::palace,
                             eLanguage::zeusText(28, 117),
                             p5, cost10, 0, &coll.fPalace},
                            {eBuildingMode::taxOffice,
                             eLanguage::zeusText(28, 122),
                             tc5, cost11, 1, &coll.fTaxCollector},
                            {eBuildingMode::bridge,
                             eLanguage::zeusText(28, 120),
                             bb5, cost12, 2, &coll.fBridge}};
    const auto ww5 = createDataWidget(mAdminDataW, buttonsVec5,
                                      eLanguage::zeusText(88, 5));


    const std::vector<eSPR> p6spr = {eSPR{eBuildingMode::podium, eLanguage::zeusText(28, 81)},
                                     eSPR{eBuildingMode::college, eLanguage::zeusText(28, 77)}};
    const auto p6 = [this, cmx, cmy, p6spr]() {
        openBuildWidget(cmx, cmy, p6spr);
    };
    const auto g6 = [this]() {
        setMode(eBuildingMode::gymnasium);
    };
    const std::vector<eSPR> d6spr = {eSPR{eBuildingMode::theater, eLanguage::zeusText(28, 82)},
                                     eSPR{eBuildingMode::dramaSchool, eLanguage::zeusText(28, 78)}};
    const auto d6 = [this, cmx, cmy, d6spr]() {
        openBuildWidget(cmx, cmy, d6spr);
    };
    const auto s6 = [this]() {
        setMode(eBuildingMode::stadium);
    };

    mCultureDataW = new eCultureDataWidget(*mBoard, window());
    const int cost13 = eDifficultyHelpers::buildingCost(
                          diff, eBuildingType::gymnasium);
    const int cost14 = eDifficultyHelpers::buildingCost(
                          diff, eBuildingType::stadium);
    const auto buttonsVec6 = eButtonsDataVec{
                            {eBuildingMode::none,
                             eLanguage::zeusText(28, 137),
                             p6, 0, 0, &coll.fPhilosophy, p6spr},
                            {eBuildingMode::gymnasium,
                             eLanguage::zeusText(28, 79),
                             g6, cost13, 1, &coll.fGymnasium},
                            {eBuildingMode::none,
                             eLanguage::zeusText(28, 27),
                             d6, 0, 2, &coll.fDrama, d6spr},
                            {eBuildingMode::stadium,
                             eLanguage::zeusText(28, 80),
                             s6, cost14, 3, &coll.fStadium}};
    const auto ww6 = createDataWidget(mCultureDataW, buttonsVec6,
                                      eLanguage::zeusText(88, 6));



    const std::vector<eSPR> t7spr = {eSPR{eBuildingMode::templeZeus, eLanguage::zeusText(28, 84), 48},
                                     eSPR{eBuildingMode::templePoseidon, eLanguage::zeusText(28, 85), 37},
                                     eSPR{eBuildingMode::templeHades, eLanguage::zeusText(28, 95), 37},
                                     eSPR{eBuildingMode::templeHera, eLanguage::zeusText(28, 96), 30},
                                     eSPR{eBuildingMode::templeDemeter, eLanguage::zeusText(28, 86), 27},
                                     eSPR{eBuildingMode::templeAthena, eLanguage::zeusText(28, 92), 24},
                                     eSPR{eBuildingMode::templeArtemis, eLanguage::zeusText(28, 88), 20},
                                     eSPR{eBuildingMode::templeApollo, eLanguage::zeusText(28, 87), 20},
                                     eSPR{eBuildingMode::templeAtlas, eLanguage::zeusText(28, 97), 25},
                                     eSPR{eBuildingMode::templeAres, eLanguage::zeusText(28, 89), 13},
                                     eSPR{eBuildingMode::templeHephaestus, eLanguage::zeusText(28, 93), 13},
                                     eSPR{eBuildingMode::templeAphrodite, eLanguage::zeusText(28, 90), 11},
                                     eSPR{eBuildingMode::templeHermes, eLanguage::zeusText(28, 91), 9},
                                     eSPR{eBuildingMode::templeDionysus, eLanguage::zeusText(28, 94), 8}};
    const auto t7 = [this, cmx, cmy, t7spr]() {
        openBuildWidget(cmx, cmy, t7spr);
    };

    const std::vector<eSPR> hs7spr = {eSPR{eBuildingMode::achillesHall, eLanguage::zeusText(185, 8)},
                                      eSPR{eBuildingMode::atalantaHall, eLanguage::zeusText(185, 14)},
                                      eSPR{eBuildingMode::bellerophonHall, eLanguage::zeusText(185, 15)},
                                      eSPR{eBuildingMode::herculesHall, eLanguage::zeusText(185, 9)},
                                      eSPR{eBuildingMode::jasonHall, eLanguage::zeusText(185, 10)},
                                      eSPR{eBuildingMode::odysseusHall, eLanguage::zeusText(185, 11)},
                                      eSPR{eBuildingMode::perseusHall, eLanguage::zeusText(185, 12)},
                                      eSPR{eBuildingMode::theseusHall, eLanguage::zeusText(185, 13)}};
    const auto hs7 = [this, cmx, cmy, hs7spr]() {
        openBuildWidget(cmx, cmy, hs7spr);
    };

    mMythDataW = new eMythologyDataWidget(*b, window());
    const auto buttonsVec7 = eButtonsDataVec{
                            {eBuildingMode::none,
                             eLanguage::zeusText(28, 83),
                             t7, 0, 0, &coll.fTemples, t7spr},
                            {eBuildingMode::none,
                             eLanguage::zeusText(28, 125),
                             hs7, 0, 1, &coll.fHeroShrines, hs7spr}};
    const auto ww7 = createDataWidget(mMythDataW, buttonsVec7,
                                      eLanguage::zeusText(88, 7));


    const std::vector<eSPR> f8spr = {eSPR{eBuildingMode::wall, eLanguage::zeusText(28, 130)},
                                     eSPR{eBuildingMode::tower, eLanguage::zeusText(28, 132)},
                                     eSPR{eBuildingMode::gatehouse, eLanguage::zeusText(28, 131)}};
    const auto f8 = [this, cmx, cmy, f8spr]() {
        openBuildWidget(cmx, cmy, f8spr);
    };
    const std::vector<eSPR> mp8spr = {eSPR{eBuildingMode::armory, eLanguage::zeusText(28, 135)},
                                      eSPR{eBuildingMode::horseRanch, eLanguage::zeusText(28, 133)}};
    const auto mp8 = [this, cmx, cmy, mp8spr]() {
        openBuildWidget(cmx, cmy, mp8spr);
    };

    mMiltDataW = new eMilitaryDataWidget(*b, window());
    const auto buttonsVec8 = eButtonsDataVec{
                        {eBuildingMode::none,
                         eLanguage::zeusText(28, 139),
                         f8, 0, 0, &coll.fFortifications, f8spr},
                        {eBuildingMode::none,
                         eLanguage::zeusText(28, 140),
                         mp8, 0, 1, &coll.fMilitaryProduction, mp8spr}};
    const auto ww8 = createDataWidget(mMiltDataW, buttonsVec8,
                                      eLanguage::zeusText(88, 8));

    const std::vector<eSPR> bb9spr = {eSPR{eBuildingMode::park, eLanguage::zeusText(28, 128)},
                                      eSPR{eBuildingMode::waterPark, eLanguage::zeusText(28, 25)},
                                      eSPR{eBuildingMode::doricColumn, eLanguage::zeusText(28, 129)},
                                      eSPR{eBuildingMode::ionicColumn, eLanguage::zeusText(28, 145)},
                                      eSPR{eBuildingMode::corinthianColumn, eLanguage::zeusText(28, 146)},
                                      eSPR{eBuildingMode::avenue, eLanguage::zeusText(28, 118)}};
    const auto bb9 = [this, cmx, cmy, bb9spr]() {
        openBuildWidget(cmx, cmy, bb9spr);
    };
    const std::vector<eSPR> r9spr = {eSPR{eBuildingMode::bench, eLanguage::zeusText(28, 127)},
                                     eSPR{eBuildingMode::birdBath, eLanguage::zeusText(28, 152)},
                                     eSPR{eBuildingMode::shortObelisk, eLanguage::zeusText(28, 24)},
                                     eSPR{eBuildingMode::tallObelisk, eLanguage::zeusText(28, 19)},
                                     eSPR{eBuildingMode::flowerGarden, eLanguage::zeusText(28, 15)},
                                     eSPR{eBuildingMode::gazebo, eLanguage::zeusText(28, 16)},
                                     eSPR{eBuildingMode::shellGarden, eLanguage::zeusText(28, 150)},
                                     eSPR{eBuildingMode::sundial, eLanguage::zeusText(28, 20)},
                                     eSPR{eBuildingMode::hedgeMaze, eLanguage::zeusText(28, 17)},
                                     eSPR{eBuildingMode::dolphinSculpture, eLanguage::zeusText(28, 148)},
                                     eSPR{eBuildingMode::spring, eLanguage::zeusText(28, 22)},
                                     eSPR{eBuildingMode::topiary, eLanguage::zeusText(28, 21)},
                                     eSPR{eBuildingMode::fishPond, eLanguage::zeusText(28, 18)},
                                     eSPR{eBuildingMode::baths, eLanguage::zeusText(28, 151)},
                                     eSPR{eBuildingMode::stoneCircle, eLanguage::zeusText(28, 23)}};
    const auto r9 = [this, cmx, cmy, r9spr]() {
        openBuildWidget(cmx, cmy, r9spr);
    };
    const std::vector<eSPR> m9spr = {eSPR{eBuildingMode::populationMonument, eLanguage::zeusText(198, 1)},
                                     eSPR{eBuildingMode::victoryMonument, eLanguage::zeusText(198, 2)},
                                     eSPR{eBuildingMode::colonyMonument, eLanguage::zeusText(198, 3)},
                                     eSPR{eBuildingMode::athleteMonument, eLanguage::zeusText(198, 4)},
                                     eSPR{eBuildingMode::conquestMonument, eLanguage::zeusText(198, 5)},
                                     eSPR{eBuildingMode::happinessMonument, eLanguage::zeusText(198, 6)},
                                     eSPR{eBuildingMode::heroicFigureMonument, eLanguage::zeusText(198, 7)},
                                     eSPR{eBuildingMode::diplomacyMonument, eLanguage::zeusText(198, 8)},
                                     eSPR{eBuildingMode::scholarMonument, eLanguage::zeusText(198, 9)},

                                     eSPR{eBuildingMode::aphroditeMonument, eLanguage::zeusText(198, 16)},
                                     eSPR{eBuildingMode::apolloMonument, eLanguage::zeusText(198, 13)},
                                     eSPR{eBuildingMode::aresMonument, eLanguage::zeusText(198, 15)},
                                     eSPR{eBuildingMode::artemisMonument, eLanguage::zeusText(198, 14)},
                                     eSPR{eBuildingMode::athenaMonument, eLanguage::zeusText(198, 18)},
                                     eSPR{eBuildingMode::atlasMonument, eLanguage::zeusText(198, 35)},
                                     eSPR{eBuildingMode::demeterMonument, eLanguage::zeusText(198, 12)},
                                     eSPR{eBuildingMode::dionysusMonument, eLanguage::zeusText(198, 20)},
                                     eSPR{eBuildingMode::hadesMonument, eLanguage::zeusText(198, 21)},
                                     eSPR{eBuildingMode::hephaestusMonument, eLanguage::zeusText(198, 19)},
                                     eSPR{eBuildingMode::heraMonument, eLanguage::zeusText(198, 34)},
                                     eSPR{eBuildingMode::hermesMonument, eLanguage::zeusText(198, 17)},
                                     eSPR{eBuildingMode::poseidonMonument, eLanguage::zeusText(198, 11)},
                                     eSPR{eBuildingMode::zeusMonument, eLanguage::zeusText(198, 10)}};
    const auto m9 = [this, cmx, cmy, m9spr]() {
        openBuildWidget(cmx, cmy, m9spr);
    };

    mApplDataW = new eAppealDataWidget(*b, window());
    const auto buttonsVec = eButtonsDataVec{
                    {eBuildingMode::none,
                     eLanguage::zeusText(28, 142),
                     bb9, 0, 0, &coll.fBeautification, bb9spr},
                    {eBuildingMode::none,
                     eLanguage::zeusText(28, 141),
                     r9, 0, 1, &coll.fRecreation, r9spr},
                    {eBuildingMode::none,
                     eLanguage::zeusText(28, 157),
                     m9, 0, 2, &coll.fMonuments, m9spr}};
    const auto ww9 = createDataWidget(mApplDataW, buttonsVec,
                                      eLanguage::zeusText(88, 9));

    mOverDataW = new eOverviewDataWidget(*b, window());
    mMiniMap = new eMiniMap(window());
    mMiniMap->resize(dataWidWidth, 4*dataWidWidth/5);

    const auto ww10 = createDataWidgetBase(mOverDataW, mMiniMap,
                                           eLanguage::zeusText(88, 10));
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

    setupButtonHover(b0, eLanguage::zeusText(88, 0));
    setupButtonHover(b1, eLanguage::zeusText(88, 1));
    setupButtonHover(b2, eLanguage::zeusText(88, 2));
    setupButtonHover(b3, eLanguage::zeusText(88, 3));
    setupButtonHover(b4, eLanguage::zeusText(88, 4));
    setupButtonHover(b5, eLanguage::zeusText(88, 5));
    setupButtonHover(b6, eLanguage::zeusText(88, 6));
    setupButtonHover(b7, eLanguage::zeusText(88, 7));
    setupButtonHover(b8, eLanguage::zeusText(88, 8));
    setupButtonHover(b9, eLanguage::zeusText(88, 9));
    setupButtonHover(b10, eLanguage::zeusText(88, 10));

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
        const auto rb = eButton::sCreate(coll.fRoadBlock, window(), btmButtons);
        rb->setPressAction([this]() {
            setMode(eBuildingMode::roadblock);
        });
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

    mMiniMap->setBoard(b);

    updateButtonsVisibility();
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

void eGameMenu::pushEvent(const eEvent e, const eEventData& ed) {
    mEventW->pushEvent(e, ed);
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
    if(mModeChangeAct) mModeChangeAct();
}

bool eGameMenu::mousePressEvent(const eMouseEvent& e) {
    closeBuildWidget();
    return eGameMenuBase::mouseEnterEvent(e);
}
