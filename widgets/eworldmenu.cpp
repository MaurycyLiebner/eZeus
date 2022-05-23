#include "eworldmenu.h"

#include "textures/egametextures.h"

#include "ebutton.h"

void eWorldMenu::initialize() {
    const auto& intrfc = eGameTextures::interface();
    const auto uiScale = resolution().uiScale();
    const int iRes = static_cast<int>(uiScale);
    const int mult = iRes + 1;

    const auto& coll = intrfc[iRes];
    const auto tex = coll.fWorldMenuBackground;
    setTexture(tex);
    setPadding(0);
    fitContent();

    {
        const auto wlab = eButton::sCreate(coll.fWorldLeftArrowButton, window(), this);
        const auto whb = eButton::sCreate(coll.fWorldHistoryButton, window(), this);
        const auto wrab = eButton::sCreate(coll.fWorldRightArrowButton, window(), this);

        const int xwlab = std::round(5.5*mult);
        const int xwhb = std::round(34.5*mult);
        const int xwrab = std::round(59.5*mult);

        const int ywlab = std::round(48.5*mult);
        const int ywhb = std::round(44.5*mult);
        const int ywrab = ywlab;

        wlab->setX(xwlab);
        wlab->setY(ywlab);

        whb->setX(xwhb);
        whb->setY(ywhb);

        wrab->setX(xwrab);
        wrab->setY(ywrab);
    }

    {
        const auto wrb = eButton::sCreate(coll.fRequestButton, window(), this);
        const auto wfb = eButton::sCreate(coll.fFulfillButton, window(), this);
        const auto wgb = eButton::sCreate(coll.fGiftButton, window(), this);
        const auto wrdb = eButton::sCreate(coll.fRaidButton, window(), this);
        const auto wcb = eButton::sCreate(coll.fConquerButton, window(), this);

        const int xwrb = std::round(6.5*mult);
        const int xwfb = 35*mult;
        const int xwgb = std::round(63.5*mult);
        const int xwrdb = xwrb;
        const int xwcb = 49*mult;

        const int ywrb = 230*mult;
        const int ywfb = ywrb;
        const int ywgb = ywrb;
        const int ywrdb = 259*mult;
        const int ywcb = ywrdb;

        wrb->setX(xwrb);
        wrb->setY(ywrb);

        wfb->setX(xwfb);
        wfb->setY(ywfb);

        wgb->setX(xwgb);
        wgb->setY(ywgb);

        wrdb->setX(xwrdb);
        wrdb->setY(ywrdb);

        wcb->setX(xwcb);
        wcb->setY(ywcb);
    }
}
