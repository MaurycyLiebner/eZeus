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

eGameMenu::eGameMenu(eMainWindow* const window) :
    eLabel(window), mRes(window->resolution()) {
    const auto& intrfc = eGameTextures::interface();
    int icoll;
    switch(mRes) {
    case eRes::p480:
        icoll = 0;
        break;
    case eRes::p720:
    case eRes::p1080:
        icoll = 1;
        break;
    default:
        icoll = 2;
    }
    const auto& coll = intrfc[icoll];
    const auto tex = coll.fGameMenuBackground;
    setTexture(tex);
    setPadding(0);
    fitContent();

    const auto buttons = new eWidget(window);
    buttons->setX(6);
    buttons->setY(21);
    buttons->setPadding(0);

    const auto pop = createButton(coll.fPopulationTexture, buttons);
    createButton(coll.fHusbandryTexture, buttons);
    createButton(coll.fIndustryTexture, buttons);
    createButton(coll.fDistributionTexture, buttons);
    createButton(coll.fHygieneSafetyTexture, buttons);
    createButton(coll.fAdministrationTexture, buttons);
    createButton(coll.fCultureTexture, buttons);
    createButton(coll.fMythologyTexture, buttons);
    createButton(coll.fMilitaryTexture, buttons);
    createButton(coll.fAestheticsTexture, buttons);
    createButton(coll.fOverviewTexture, buttons);

    buttons->setHeight(11*(pop->height() + 2));

    buttons->layoutVertically();
    buttons->fitContent();
    addWidget(buttons);
}
