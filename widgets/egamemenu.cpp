#include "egamemenu.h"

#include "textures/egametextures.h"
#include "emainwindow.h"
#include "echeckablebutton.h"

eCheckableButton* eGameMenu::createButton(
        const eTextureCollection& texs,
        eWidget* const buttons) {
    const auto b = new eCheckableButton(window());
    b->setTexture(texs.getTexture(0));
    b->setPadding(0);
    b->setHoverTexture(texs.getTexture(1));
    b->setCheckedTexture(texs.getTexture(2));
    b->fitContent();
    buttons->addWidget(b);
    return b;
}

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
        const eTexCollVec& colls) {
    const auto result = new eWidget(window());

    const int x = resoltuionMult*35;
    const int y = resoltuionMult*27;
    const std::vector<std::pair<int, int>> poses =
        {{0, 0}, {x, 0}, {0, y}, {x, y}};

    const int iMax = colls.size();
    for(int i = 0; i < iMax; i++) {
        const auto& c = colls[i];
        const auto b = createSubButton(*c, result);
        const auto& pos = poses[i];
        b->setX(pos.first);
        b->setY(pos.second);
    }

    result->setPadding(0);
    result->fitContent();

    return result;
}

eGameMenu::eGameMenu(eMainWindow* const window) :
    eLabel(window), mRes(window->resolution()) {
    const auto& intrfc = eGameTextures::interface();
    int mult;
    int icoll;
    int margin;
    int x;
    int y;
    switch(mRes) {
    case eRes::p480:
        mult = 1;
        icoll = 0;
        margin = 2;
        x = 5;
        y = 15;
        break;
    case eRes::p720:
    case eRes::p1080:
        mult = 2;
        icoll = 1;
        margin = 2;
        x = 6;
        y = 21;
        break;
    default:
        mult = 4;
        icoll = 2;
        margin = 3;
        x = 12;
        y = 42;
    }
    const auto& coll = intrfc[icoll];
    const auto tex = coll.fGameMenuBackground;
    setTexture(tex);
    setPadding(0);
    fitContent();

    const auto buttons = new eWidget(window);
    buttons->setX(x);
    buttons->setY(y);
    buttons->setPadding(0);

    const auto b0 = createButton(coll.fPopulation, buttons);
    const auto b1 = createButton(coll.fHusbandry, buttons);
    const auto b2 = createButton(coll.fIndustry, buttons);
    const auto b3 = createButton(coll.fDistribution, buttons);
    const auto b4 = createButton(coll.fHygieneSafety, buttons);
    const auto b5 = createButton(coll.fAdministration, buttons);
    const auto b6 = createButton(coll.fCulture, buttons);
    const auto b7 = createButton(coll.fMythology, buttons);
    const auto b8 = createButton(coll.fMilitary, buttons);
    const auto b9 = createButton(coll.fAesthetics, buttons);
    const auto b10 = createButton(coll.fOverview, buttons);

    mButtons.push_back(b0);
    mButtons.push_back(b1);
    mButtons.push_back(b2);
    mButtons.push_back(b3);
    mButtons.push_back(b4);
    mButtons.push_back(b5);
    mButtons.push_back(b6);
    mButtons.push_back(b7);
    mButtons.push_back(b8);
    mButtons.push_back(b9);
    mButtons.push_back(b10);

    b10->setChecked(true);

    const int iMax = mButtons.size();
    for(int i = 0; i < iMax; i++) {
        const auto b = mButtons[i];
        b->setCheckAction([this, i, b](const bool c) {
            if(c) {
                const int jMax = mButtons.size();
                const int wSize = mWidgets.size();
                for(int j = 0; j < jMax; j++) {
                    if(j < wSize) {
                        const auto w = mWidgets[j];
                        w->setVisible(j == i);
                    }
                    if(j == i) continue;
                    const auto b = mButtons[j];
                    b->setChecked(false);
                }
            } else {
                b->setChecked(true);
            }
        });
    }

    buttons->setHeight(11*(b0->height() + margin));

    buttons->layoutVertically();
    buttons->fitContent();
    addWidget(buttons);

    const auto w0 = createSubButtons(mult,
                        std::vector<const eTextureCollection*>{
                            &coll.fCommonHousing,
                            &coll.fEliteHousing});
    const auto w1 = createSubButtons(mult,
                        std::vector<const eTextureCollection*>{
                            &coll.fFoodFarming,
                            &coll.fOtherFarming,
                            &coll.fAnimalFarming,
                            &coll.fAnimalHunting});
    const auto w2 = createSubButtons(mult,
                        std::vector<const eTextureCollection*>{
                            &coll.fResources,
                            &coll.fProcessing,
                            &coll.fBuildersGuild});
    const auto w3 = createSubButtons(mult,
                        std::vector<const eTextureCollection*>{
                            &coll.fGranary,
                            &coll.fWarehouse,
                            &coll.fAgoras,
                            &coll.fTrade});
    const auto w4 = createSubButtons(mult,
                        std::vector<const eTextureCollection*>{
                            &coll.fFireFighter,
                            &coll.fFountain,
                            &coll.fPolice,
                            &coll.fHospital});
    const auto w5 = createSubButtons(mult,
                        std::vector<const eTextureCollection*>{
                            &coll.fPalace,
                            &coll.fTaxCollector,
                            &coll.fBridge});
    const auto w6 = createSubButtons(mult,
                        std::vector<const eTextureCollection*>{
                            &coll.fPhilosophy,
                            &coll.fGymnasium,
                            &coll.fDrama,
                            &coll.fStadium});
    const auto w7 = createSubButtons(mult,
                        std::vector<const eTextureCollection*>{
                            &coll.fTemples,
                            &coll.fHeroShrines});
    const auto w8 = createSubButtons(mult,
                        std::vector<const eTextureCollection*>{
                            &coll.fFortifications,
                            &coll.fMilitaryProduction});
    const auto w9 = createSubButtons(mult,
                        std::vector<const eTextureCollection*>{
                            &coll.fBeautification,
                            &coll.fRecreation,
                            &coll.fMonuments});


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

    addWidget(w0);
    addWidget(w1);
    addWidget(w2);
    addWidget(w3);
    addWidget(w4);
    addWidget(w5);
    addWidget(w6);
    addWidget(w7);
    addWidget(w8);
    addWidget(w9);

    {
        const int x = mult*24;
        const int y = mult*165;
        w0->move(x, y);
        w1->move(x, y);
        w2->move(x, y);
        w3->move(x, y);
        w4->move(x, y);
        w5->move(x, y);
        w6->move(x, y);
        w7->move(x, y);
        w8->move(x, y);
        w9->move(x, y);
    }

    w0->hide();
    w1->hide();
    w2->hide();
    w3->hide();
    w4->hide();
    w5->hide();
    w6->hide();
    w7->hide();
    w8->hide();
    w9->hide();

    {
        const auto btmButtons = new eWidget(window);
        btmButtons->setPadding(0);

        const auto b = createSubButton(coll.fBuildRoad, btmButtons);
        createSubButton(coll.fRoadBlock, btmButtons);
        createSubButton(coll.fClear, btmButtons);
        createSubButton(coll.fUndo, btmButtons);

        const int x = mult*24;
        const int y = std::round(mult*217.5);
        btmButtons->resize(4*b->width(), b->height());
        btmButtons->move(x, y);
        btmButtons->layoutHorizontally();
        addWidget(btmButtons);
    }

    {
        const auto butts = new eWidget(window);
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
        const auto butts = new eWidget(window);
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
