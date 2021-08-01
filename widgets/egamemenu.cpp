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

eWidget* eGameMenu::createButtons(
        const std::vector<const eTextureCollection*>& colls) {
    const auto result = new eWidget(window());

    const std::vector<std::pair<int, int>> poses =
        {{0, 0}, {70, 0}, {0, 60}, {70, 60}};

    const int iMax = colls.size();
    for(int i = 0; i < iMax; i++) {
        const auto& c = colls[i];
        const auto b = createButton(*c, result);
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
    int icoll;
    int margin;
    int x;
    int y;
    switch(mRes) {
    case eRes::p480:
        icoll = 0;
        margin = 2;
        x = 5;
        y = 15;
        break;
    case eRes::p720:
    case eRes::p1080:
        icoll = 1;
        margin = 2;
        x = 6;
        y = 21;
        break;
    default:
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

    const auto b0 = createButton(coll.fPopulationTexture, buttons);
    const auto b1 = createButton(coll.fHusbandryTexture, buttons);
    const auto b2 = createButton(coll.fIndustryTexture, buttons);
    const auto b3 = createButton(coll.fDistributionTexture, buttons);
    const auto b4 = createButton(coll.fHygieneSafetyTexture, buttons);
    const auto b5 = createButton(coll.fAdministrationTexture, buttons);
    const auto b6 = createButton(coll.fCultureTexture, buttons);
    const auto b7 = createButton(coll.fMythologyTexture, buttons);
    const auto b8 = createButton(coll.fMilitaryTexture, buttons);
    const auto b9 = createButton(coll.fAestheticsTexture, buttons);
    const auto b10 = createButton(coll.fOverviewTexture, buttons);

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

    const int iMax = mButtons.size();
    for(int i = 0; i < iMax; i++) {
        const auto b = mButtons[i];
        b->setCheckAction([this, i](const bool c) {
            (void)c;
            const int jMax = mButtons.size();
            for(int j = 0; j < jMax; j++) {
                const auto w = mWidgets[j];
                w->setVisible(j == i);
                if(j == i) continue;
                const auto b = mButtons[j];
                b->setChecked(false);
            }
        });
    }

    buttons->setHeight(11*(b0->height() + margin));

    buttons->layoutVertically();
    buttons->fitContent();
    addWidget(buttons);

    const auto w0 = createButtons(
                        std::vector<const eTextureCollection*>{
                            &coll.fCommonHousingTexture,
                            &coll.fEliteHousingTexture});
    const auto w1 = createButtons(
                        std::vector<const eTextureCollection*>{
                            &coll.fFoodFarmingTexture,
                            &coll.fOtherFarmingTexture,
                            &coll.fAnimalFarmingTexture,
                            &coll.fAnimalHuntingTexture});
    const auto w2 = createButtons(
                        std::vector<const eTextureCollection*>{
                            &coll.fResourcesTexture,
                            &coll.fProcessingTexture,
                            &coll.fBuildersGuildTexture});
    const auto w3 = createButtons(
                        std::vector<const eTextureCollection*>{
                            &coll.fGranaryTexture,
                            &coll.fWarehouseTexture,
                            &coll.fAgorasTexture,
                            &coll.fTradeTexture});
    const auto w4 = createButtons(
                        std::vector<const eTextureCollection*>{
                            &coll.fFireFighterTexture,
                            &coll.fFountainTexture,
                            &coll.fPoliceTexture,
                            &coll.fHospitalTexture});
    const auto w5 = createButtons(
                        std::vector<const eTextureCollection*>{
                            &coll.fResourcesTexture,
                            &coll.fProcessingTexture,
                            &coll.fBuildersGuildTexture});
    const auto w6 = createButtons(
                        std::vector<const eTextureCollection*>{
                            &coll.fPalaceTexture,
                            &coll.fTaxCollectorTexture,
                            &coll.fBridgeTexture});
    const auto w7 = createButtons(
                        std::vector<const eTextureCollection*>{
                            &coll.fPhilosophyTexture,
                            &coll.fGymnasiumTexture,
                            &coll.fDramaTexture,
                            &coll.fStadiumTexture});
    const auto w8 = createButtons(
                        std::vector<const eTextureCollection*>{
                            &coll.fTemplesTexture,
                            &coll.fHeroShrinesTexture});
    const auto w9 = createButtons(
                        std::vector<const eTextureCollection*>{
                            &coll.fFortificationsTexture,
                            &coll.fMilitaryProductionTexture});
    const auto w10 = createButtons(
                        std::vector<const eTextureCollection*>{
                            &coll.fBeautificationTexture,
                            &coll.fRecreationTexture,
                            &coll.fMonumentTexture});


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
    addWidget(w10);

    w0->align(eAlignment::right | eAlignment::vcenter);
    w1->align(eAlignment::right | eAlignment::vcenter);
    w2->align(eAlignment::right | eAlignment::vcenter);
    w3->align(eAlignment::right | eAlignment::vcenter);
    w4->align(eAlignment::right | eAlignment::vcenter);
    w5->align(eAlignment::right | eAlignment::vcenter);
    w6->align(eAlignment::right | eAlignment::vcenter);
    w7->align(eAlignment::right | eAlignment::vcenter);
    w8->align(eAlignment::right | eAlignment::vcenter);
    w9->align(eAlignment::right | eAlignment::vcenter);
    w10->align(eAlignment::right | eAlignment::vcenter);

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
    w10->hide();
}
