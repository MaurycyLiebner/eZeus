#include "eworldmenu.h"

#include "textures/egametextures.h"

#include "ebutton.h"
#include "emainwindow.h"
#include "eworldgoodswidget.h"

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
        mRequestButton = eButton::sCreate(coll.fRequestButton, window(), this);
        mFulfillButton = eButton::sCreate(coll.fFulfillButton, window(), this);
        mGiftButton = eButton::sCreate(coll.fGiftButton, window(), this);
        mRaidButton = eButton::sCreate(coll.fRaidButton, window(), this);
        mConquerButton = eButton::sCreate(coll.fConquerButton, window(), this);

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

        mRequestButton->setX(xwrb);
        mRequestButton->setY(ywrb);

        mFulfillButton->setX(xwfb);
        mFulfillButton->setY(ywfb);

        mGiftButton->setX(xwgb);
        mGiftButton->setY(ywgb);

        mRaidButton->setX(xwrdb);
        mRaidButton->setY(ywrdb);

        mConquerButton->setX(xwcb);
        mConquerButton->setY(ywcb);


        const auto wh = eButton::sCreate(coll.fHelpButton, window(), this);
        const int whx = 6*mult;
        const int why = 286*mult;

        wh->setX(whx);
        wh->setY(why);

        const auto wgw = eButton::sCreate(coll.fWorldSmallButton, window(), this);
        wgw->setPressAction([this](){
            window()->showGame();
        });
        const int wgwx = 20*mult;
        const int wgwy = 285*mult;

        const auto wgwtxt = new eLabel("Back to city", window());
        wgwtxt->setSmallFontSize();
        wgwtxt->fitContent();
        wgw->addWidget(wgwtxt);
        wgwtxt->align(eAlignment::center);

        wgw->setX(wgwx);
        wgw->setY(wgwy);


        const auto wat = eButton::sCreate(coll.fWorldBigButton, window(), this);

        mAttitudeLabel = new eLabel("Loyal", window());
        mAttitudeLabel->setSmallFontSize();
        mAttitudeLabel->fitContent();
        wat->addWidget(mAttitudeLabel);
        mAttitudeLabel->align(eAlignment::center);

        const int watx = 4*mult;
        const int waty = 66*mult;

        wat->setX(watx);
        wat->setY(waty);
    }

    {
        mRelationshipLabel = new eLabel("", window());
        mRelationshipLabel->setSmallFontSize();
        mRelationshipLabel->fitContent();
        addWidget(mRelationshipLabel);
        mRelationshipLabel->align(eAlignment::hcenter);
        const int rly = 16*mult;
        mRelationshipLabel->setY(rly);

        mNameLabel = new eLabel("", window());
        mNameLabel->setSmallFontSize();
        mNameLabel->fitContent();
        addWidget(mNameLabel);
        mNameLabel->align(eAlignment::hcenter);
        mNameLabel->setY(rly + mRelationshipLabel->height());

        mLeaderLabel = new eLabel("", window());
        mLeaderLabel->setSmallFontSize();
        mLeaderLabel->fitContent();
        addWidget(mLeaderLabel);
        mLeaderLabel->align(eAlignment::hcenter);
        mLeaderLabel->setY(mNameLabel->y() + mNameLabel->height());
    }

    {
        mGoodsWidget = new eWorldGoodsWidget(window());
        addWidget(mGoodsWidget);
        mGoodsWidget->setX(mult*10);
        mGoodsWidget->setY(mult*90);

        mGoodsWidget->setWidth(mult*75);
        mGoodsWidget->setHeight(mult*105);

        mGoodsWidget->initialize();
    }

    setCity(nullptr);
}

void eWorldMenu::setCity(const stdsptr<eWorldCity>& c) {
    mCity = c;

    if(c) {
        {
            std::string atStr;
            switch(c->attitude()) {
            case eWorldCityAttitude::congenial:
                atStr = "Congenial";
                break;
            case eWorldCityAttitude::dedicated:
                atStr = "Dedicated";
                break;
            case eWorldCityAttitude::loyal:
                atStr = "Loyal";
                break;
            default:
                atStr = "Unknown";
                break;
            }

            mAttitudeLabel->setText(atStr);
        }
        {
            std::string relStr;
            switch(c->relationship()) {
            case eWorldCityRelationship::mainCity:
                relStr = "Our city!";
                break;
            case eWorldCityRelationship::collony:
                relStr = "Collony";
                break;
            case eWorldCityRelationship::vassal:
                relStr = "Vassal";
                break;
            case eWorldCityRelationship::ally:
                relStr = "Ally";
                break;
            case eWorldCityRelationship::rival:
                relStr = "Rival";
                break;
            }

            mRelationshipLabel->setText(relStr);
        }
        mNameLabel->setText(c->name());
        mLeaderLabel->setText(c->leader());
    } else {
        mAttitudeLabel->setText("");
        mRelationshipLabel->setText("");
        mNameLabel->setText("");
        mLeaderLabel->setText("");
    }

    mRequestButton->setEnabled(c.get());
    mFulfillButton->setEnabled(c.get());
    mGiftButton->setEnabled(c.get());
    mRaidButton->setEnabled(c.get());
    mConquerButton->setEnabled(c.get());

    mGoodsWidget->setCity(c);
}
