#include "eworldmenu.h"

#include "textures/egametextures.h"

#include "ebutton.h"
#include "emainwindow.h"
#include "eworldgoodswidget.h"
#include "eworldtributewidget.h"
#include "egamewidget.h"

#include "elanguage.h"

void eWorldMenu::initialize(const eAction& openRequest,
                            const eAction& openGift,
                            const eAction& openRaid,
                            const eAction& openConquer) {
    int iRes;
    int mult;
    iResAndMult(iRes, mult);

    const auto& intrfc = eGameTextures::interface();
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
        mRequestButton->setPressAction(openRequest);

        mFulfillButton->setX(xwfb);
        mFulfillButton->setY(ywfb);

        mGiftButton->setX(xwgb);
        mGiftButton->setY(ywgb);
        mGiftButton->setPressAction(openGift);

        mRaidButton->setX(xwrdb);
        mRaidButton->setY(ywrdb);
        mRaidButton->setPressAction(openRaid);

        mConquerButton->setX(xwcb);
        mConquerButton->setY(ywcb);
        mConquerButton->setPressAction(openConquer);

        const auto wh = eButton::sCreate(coll.fHelpButton, window(), this);
        const int whx = 6*mult;
        const int why = 286*mult;

        wh->setX(whx);
        wh->setY(why);

        const auto wgw = eButton::sCreate(coll.fWorldSmallButton, window(), this);
        wgw->setPressAction([this](){
            window()->showGame(nullptr, eGameWidgetSettings());
        });
        const int wgwx = 20*mult;
        const int wgwy = 285*mult;

        const auto backToCityStr = eLanguage::zeusText(47, 8);
        const auto wgwtxt = new eLabel(backToCityStr, window());
        wgwtxt->setSmallFontSize();
        wgwtxt->fitContent();
        wgw->addWidget(wgwtxt);
        wgwtxt->align(eAlignment::center);

        wgw->setX(wgwx);
        wgw->setY(wgwy);


        const auto wat = eButton::sCreate(coll.fWorldBigButton, window(), this);

        mAttitudeLabel = new eLabel("unknown", window());
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
        mRelationshipLabel = new eLabel("a", window());
        mRelationshipLabel->setNoPadding();
        mRelationshipLabel->setSmallFontSize();
        mRelationshipLabel->fitContent();
        addWidget(mRelationshipLabel);
        mRelationshipLabel->align(eAlignment::hcenter);
        const int rly = 14*mult;
        mRelationshipLabel->setY(rly);

        mNameLabel = new eLabel("a", window());
        mNameLabel->setNoPadding();
        mNameLabel->setSmallFontSize();
        mNameLabel->fitContent();
        addWidget(mNameLabel);
        mNameLabel->align(eAlignment::hcenter);
        mNameLabel->setY(rly + mRelationshipLabel->height());

        mLeaderLabel = new eLabel("a", window());
        mLeaderLabel->setNoPadding();
        mLeaderLabel->setTinyFontSize();
        mLeaderLabel->fitContent();
        addWidget(mLeaderLabel);
        mLeaderLabel->align(eAlignment::hcenter);
        mLeaderLabel->setY(mNameLabel->y() + mNameLabel->height());
    }

    {
        mTextLabel = new eLabel(window());
        mTextLabel->setNoPadding();
        addWidget(mTextLabel);
        mTextLabel->setX(mult*10);
        mTextLabel->setY(mult*90);
        const int w = mult*75;
        mTextLabel->setWrapWidth(w);
        mTextLabel->setWrapAlignment(eAlignment::hcenter);
        mTextLabel->setWidth(w);
        mTextLabel->setHeight(mult*105);
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

    {
        mTributeWidget = new eWorldTributeWidget(window());
        addWidget(mTributeWidget);

        mTributeWidget->setX(mult*10);
        mTributeWidget->setY(mult*205);

        mTributeWidget->setWidth(mult*75);
        mTributeWidget->setHeight(mult*24);

        mTributeWidget->initialize();
    }

    setCity(nullptr);
}

void eWorldMenu::setCity(const stdsptr<eWorldCity>& c) {
    if(!c) {
        const auto text = eLanguage::zeusText(47, 5);
        mTextLabel->setText(text);
        mTextLabel->show();
    } else {
        mTextLabel->hide();
    }

    mCity = c;

    bool vassalOrColony = false;
    bool distant = false;

    if(c) {
        const auto rel = c->relationship();
        vassalOrColony = rel == eWorldCityRelationship::vassal ||
                         rel == eWorldCityRelationship::collony;
        const int min = static_cast<int>(eWorldCityType::distantCity);
        const int max = static_cast<int>(eWorldCityType::distantCityNW);
        const auto type = c->type();
        const int typei = static_cast<int>(type);
        distant = typei >= min && typei <= max;
        updateRelationshipLabel();
        mNameLabel->setText(c->name());
        const auto leader = eLanguage::zeusText(44, 328);
        mLeaderLabel->setText(leader + " " + c->leader());
    } else {
        mAttitudeLabel->setText("");
        mRelationshipLabel->setText("");
        mNameLabel->setText("");
        mLeaderLabel->setText("");
    }

    mRequestButton->setEnabled(c.get() && !distant);
    mFulfillButton->setEnabled(c.get() && !distant);
    mGiftButton->setEnabled(c.get() && !distant);
    mRaidButton->setEnabled(c.get() && !vassalOrColony && !distant);
    mConquerButton->setEnabled(c.get() && !vassalOrColony && !distant);

    mGoodsWidget->setCity(c);
    mTributeWidget->setCity(c);
}

void eWorldMenu::setText(const std::string& text) {
    setCity(nullptr);
    mTextLabel->setText(text);
    mTextLabel->show();
}

void eWorldMenu::updateRelationshipLabel() const {
    if(!mCity) {
        mRelationshipLabel->setText("");
        mAttitudeLabel->setText("");
        return;
    }
    const auto rel = mCity->relationship();
    if(mCity->isCurrentCity()) {
        mAttitudeLabel->setText("");
    } else {
        eWorldCityAttitude at;
        const int iat = mCity->attitude();
        if(rel == eWorldCityRelationship::ally) {
            if(iat < 20) at = eWorldCityAttitude::annoyed;
            else if(iat < 40) at = eWorldCityAttitude::apatheticA;
            else if(iat < 60) at = eWorldCityAttitude::sympathetic;
            else if(iat < 80) at = eWorldCityAttitude::congenial;
            else at = eWorldCityAttitude::helpful;
        } else if(rel == eWorldCityRelationship::collony ||
                  rel == eWorldCityRelationship::vassal) {
            if(iat < 20) at = eWorldCityAttitude::angry;
            else if(iat < 40) at = eWorldCityAttitude::bitter;
            else if(iat < 60) at = eWorldCityAttitude::loyal;
            else if(iat < 80) at = eWorldCityAttitude::dedicated;
            else at = eWorldCityAttitude::devoted;
        } else { // rival
            if(iat < 20) at = eWorldCityAttitude::furious;
            else if(iat < 40) at = eWorldCityAttitude::displeased;
            else if(iat < 60) at = eWorldCityAttitude::apatheticR;
            else if(iat < 80) at = eWorldCityAttitude::respectful;
            else at = eWorldCityAttitude::admiring;
        }
        const int group = 65;
        int string = -1;
        switch(at) {
        case eWorldCityAttitude::philanthropic:
            string = 15;
            break;
        case eWorldCityAttitude::resentful:
            string = 16;
            break;

        case eWorldCityAttitude::helpful:
            string = 0;
            break;
        case eWorldCityAttitude::congenial:
            string = 1;
            break;
        case eWorldCityAttitude::sympathetic:
            string = 2;
            break;
        case eWorldCityAttitude::apatheticA:
            string = 3;
            break;
        case eWorldCityAttitude::annoyed:
            string = 4;
            break;


        case eWorldCityAttitude::devoted:
            string = 10;
            break;
        case eWorldCityAttitude::dedicated:
            string = 11;
            break;
        case eWorldCityAttitude::loyal:
            string = 12;
            break;
        case eWorldCityAttitude::bitter:
            string = 13;
            break;
        case eWorldCityAttitude::angry:
            string = 14;
            break;


        case eWorldCityAttitude::docile:
            string = 17;
            break;
        case eWorldCityAttitude::hostile:
            string = 18;
            break;

        case eWorldCityAttitude::admiring:
            string = 5;
            break;
        case eWorldCityAttitude::respectful:
            string = 6;
            break;
        case eWorldCityAttitude::apatheticR:
            string = 7;
            break;
        case eWorldCityAttitude::displeased:
            string = 8;
            break;
        case eWorldCityAttitude::furious:
            string = 9;
            break;
        default:
        case eWorldCityAttitude::insubordinate:
            string = 19;
            break;
        }
        const auto atStr = eLanguage::zeusText(group, string);
        mAttitudeLabel->setText(atStr);
        mAttitudeLabel->fitContent();
        mAttitudeLabel->align(eAlignment::center);
    }

    {
        int group = 253;
        int string = -1;
        if(mCity->isCurrentCity()) {
            group = 47;
            string = 0;
        } else {
            switch(rel) {
            case eWorldCityRelationship::mainCity:
                group = 39;
                string = 0;
                break;
            case eWorldCityRelationship::collony:
                string = 3;
                break;
            case eWorldCityRelationship::vassal:
                string = 2;
                break;
            case eWorldCityRelationship::ally:
                string = 0;
                break;
            case eWorldCityRelationship::rival:
                string = 1;
                break;
            }
        }
        const auto relStr = eLanguage::zeusText(group, string);
        mRelationshipLabel->setText(relStr);
        mRelationshipLabel->fitContent();
        mRelationshipLabel->align(eAlignment::hcenter);
    }
}
