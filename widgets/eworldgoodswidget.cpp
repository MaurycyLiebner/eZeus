#include "eworldgoodswidget.h"

#include "elabel.h"
#include "ebutton.h"
#include "textures/egametextures.h"
#include "eworldgoodswidget.h"
#include "engine/egameboard.h"
#include "eframedbutton.h"
#include "eresourcebutton.h"
#include "evaluebutton.h"
#include "evectorhelpers.h"

#include "emainwindow.h"
#include "ecancelbutton.h"

#include "elanguage.h"

void eTradeTypesWidget::initialize() {
    setType(eFrameType::inner);
}

void eTradeTypesWidget::setTrade(const std::vector<eResourceTrade>& trade) {
    const auto uiScale = resolution().uiScale();
    int iRes;
    int mult;
    iResAndMult(iRes, mult);

    const int h = mult*12;

    const int n = trade.size();
    setHeight(n*h);

    removeChildren();
    int i = 0;
    for(const auto& t : trade) {
        const auto w = new eWidget(window());
        w->setHeight(h);
        w->setX(h/2);
        w->setWidth(width() - h);
        w->setNoPadding();

        const auto icon = eResourceTypeHelpers::icon(uiScale, t.fType);
        const auto iconLabel = new eLabel(window());
        iconLabel->setNoPadding();
        iconLabel->setTexture(icon);
        iconLabel->fitContent();
        w->addWidget(iconLabel);
        iconLabel->align(eAlignment::vcenter | eAlignment::left);

        const auto name = eResourceTypeHelpers::typeName(t.fType);
        const auto nameLabel = new eLabel(name, window());
        nameLabel->setTinyFontSize();
        nameLabel->fitContent();
        w->addWidget(nameLabel);
        nameLabel->align(eAlignment::vcenter | eAlignment::left);
        nameLabel->setX(iconLabel->x() + iconLabel->width());

        const auto used = std::to_string(t.fUsed);
        const auto max = std::to_string(t.fMax);
        const auto str = used + "/" + max;
        const auto usedLabel = new eLabel(str, window());
        usedLabel->setTinyFontSize();
        usedLabel->fitContent();
        w->addWidget(usedLabel);
        usedLabel->align(eAlignment::vcenter | eAlignment::right);

        addWidget(w);
        w->setY(i*h);
        i++;
    }
}

void eWorldTradeWidget::initialize(const std::string& name) {
    int iRes;
    int mult;
    iResAndMult(iRes, mult);

    setWidth(mult*75);

    mNameLabel = new eLabel(window());
    mNameLabel->setTinyPadding();
    mNameLabel->setSmallFontSize();
    mNameLabel->setText(name);
    mNameLabel->fitContent();
    addWidget(mNameLabel);
    mNameLabel->align(eAlignment::top | eAlignment::hcenter);

    mTradeTypesWidget = new eTradeTypesWidget(window());
    mTradeTypesWidget->setY(mNameLabel->height());
    mTradeTypesWidget->initialize();
    mTradeTypesWidget->setWidth(width());
    addWidget(mTradeTypesWidget);

    setNoPadding();
    fitContent();
}

void eWorldTradeWidget::setName(const std::string &name) {
    mNameLabel->setText(name);
    mNameLabel->fitContent();
    mNameLabel->align(eAlignment::top | eAlignment::hcenter);
}

void eWorldTradeWidget::setTrade(std::vector<eResourceTrade>* const trade) {
    mTrade = trade;
    const int oh = height();
    mTradeTypesWidget->setTrade(trade ? *trade : std::vector<eResourceTrade>{});
    fitContent();
    const int nh = height();
    setY(y() + oh - nh);
}

void eWorldGoodsWidget::initialize() {
    int iRes;
    int mult;
    iResAndMult(iRes, mult);
    const auto& intrfc = eGameTextures::interface();
    const auto& coll = intrfc[iRes];

    mGoodsLabel = new eLabel(window());
    mGoodsLabel->setSmallFontSize();
    mGoodsLabel->setTinyPadding();
    const auto goodsStr = eLanguage::zeusText(47, 6);
    mGoodsLabel->setText(goodsStr);
    mGoodsLabel->fitContent();
    addWidget(mGoodsLabel);
    mGoodsLabel->align(eAlignment::top | eAlignment::hcenter);

    mOrdersButton = eButton::sCreate(coll.fWorldSmallButton, window(), this);

    const auto ordersStr = eLanguage::zeusText(47, 7);
    const auto ordersTxt = new eLabel(ordersStr, window());
    ordersTxt->setSmallFontSize();
    ordersTxt->fitContent();
    mOrdersButton->addWidget(ordersTxt);
    ordersTxt->align(eAlignment::center);
    mOrdersButton->align(eAlignment::hcenter);
    mOrdersButton->setY(mGoodsLabel->y() + mGoodsLabel->height());

    mBuysWidget = new eWorldTradeWidget(window());
    mBuysWidget->initialize(eLanguage::zeusText(47, 1));
    addWidget(mBuysWidget);

    mSellsWidget = new eWorldTradeWidget(window());
    mSellsWidget->initialize(eLanguage::zeusText(47, 2));
    addWidget(mSellsWidget);

    updateTradeY();
}

void eWorldGoodsWidget::setCity(const stdsptr<eWorldCity>& c) {
    const auto buys = c ? &c->buys() : nullptr;
    const auto sells = c ? &c->sells() : nullptr;
    const bool cc = c && c->isCurrentCity();
    mBuysWidget->setTrade(buys);
    mSellsWidget->setTrade(sells);
    const bool neb = buys && !buys->empty();
    const bool nes = sells && !sells->empty();
    mBuysWidget->setVisible(neb && !cc);
    mSellsWidget->setVisible(nes && !cc);
    mGoodsLabel->setVisible(c.get() && !cc);
    mOrdersButton->setVisible((neb || nes) && !cc);
    updateTradeY();

    if(c) {
        if(c->isRival()) {
            mBuysWidget->setName(eLanguage::zeusText(47, 3));
            mSellsWidget->setName(eLanguage::zeusText(47, 4));
        } else {
            mBuysWidget->setName(eLanguage::zeusText(47, 1));
            mSellsWidget->setName(eLanguage::zeusText(47, 2));
        }
    }
}

void eWorldGoodsWidget::updateTradeY() const {
    mSellsWidget->setY(height() - mSellsWidget->height());
    mBuysWidget->setY(mSellsWidget->y() - mBuysWidget->height());
}
