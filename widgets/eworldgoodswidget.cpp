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

class eTradeEditWidget : public eFramedWidget {
public:
    using eFramedWidget::eFramedWidget;

    class eTradeResourceButton : public eWidget {
    public:
        using eWidget::eWidget;

        void initialize(const eResourceType type, const int count,
                        const eAction& changeAction,
                        const eAction& removeAction) {
            mCountButton = new eValueButton(window());
            mCountButton->initialize(1, 99);
            mCountButton->setValueChangeAction([changeAction](const int) {
                if(changeAction) changeAction();
            });
            addWidget(mCountButton);

            mResourceButton = new eResourceButton(window());
            mResourceButton->initialize([changeAction](const eResourceType) {
                if(changeAction) changeAction();
            });
            addWidget(mResourceButton);

            const auto closeButton = new eCancelButton(window());
            closeButton->setPressAction([removeAction]() {
                if(removeAction) removeAction();
            });
            addWidget(closeButton);

            setTypeAndCount(type, count);
        }

        void setTypeAndCount(const eResourceType type, const int count) {
            mResourceButton->setResource(type);
            mCountButton->setValue(count);

            stackHorizontally();
            fitContent();
        }

        int count() const { return mCountButton->value(); }
        eResourceType type() const { return mResourceButton->resource(); }
    private:
        eValueButton* mCountButton = nullptr;
        eResourceButton* mResourceButton = nullptr;
    };

    void initialize(std::vector<eResourceTrade>* const trade,
                    eAction changeAction) {
        changeAction = [this, changeAction]() {
            updateVector();
            if(changeAction) changeAction();
        };

        setType(eFrameType::message);

        const int p = padding();

        mInnerWidget = new eWidget(window());
        addWidget(mInnerWidget);
        mInnerWidget->move(p, p);
        mInnerWidget->resize(width() - 2*p, height() - 2*p);

        mButtonsWidget = new eWidget(window());
        mButtonsWidget->setWidth(mInnerWidget->width());
        mInnerWidget->addWidget(mButtonsWidget);

        mTrade = trade;

        for(const auto r : *trade) {
            const auto b = new eTradeResourceButton(window());
            b->initialize(r.fType, r.fMax, changeAction, [this, b, changeAction]() {
                changeAction();
                eVectorHelpers::remove(mButtons, b);
                b->deleteLater();
                updateVector();
            });
            mButtonsWidget->addWidget(b);
            b->align(eAlignment::hcenter);
            mButtons.push_back(b);
        }
        mButtonsWidget->stackVertically();
        mButtonsWidget->fitHeight();

        const auto addButton = new eFramedButton(window());
        addButton->setPressAction([this, changeAction]() {
            const auto b = new eTradeResourceButton(window());
            const auto r = eResourceType::marble;
            b->initialize(r, 12, changeAction, [this, b, changeAction]() {
                changeAction();
                eVectorHelpers::remove(mButtons, b);
                b->deleteLater();
                updateVector();
            });
            mButtonsWidget->addWidget(b);
            b->align(eAlignment::hcenter);
            mButtons.push_back(b);

            mButtonsWidget->stackVertically();
            mButtonsWidget->fitHeight();

            mInnerWidget->stackVertically();
            changeAction();
        });
        addButton->setText(eLanguage::text("add"));
        addButton->fitContent();
        mInnerWidget->addWidget(addButton);
        addButton->align(eAlignment::hcenter);

        mInnerWidget->stackVertically();
    }
private:
    void updateVector() {
        mTrade->clear();
        for(const auto b : mButtons) {
            const auto type = b->type();
            const int count = b->count();
            eResourceTrade rt;
            rt.fMax = count;
            rt.fType = type;
            rt.fUsed = 0;
            rt.fPrice = eResourceTypeHelpers::defaultPrice(type);
            mTrade->push_back(rt);
        }
    }

    std::vector<eResourceTrade>* mTrade = nullptr;
    eWidget* mInnerWidget = nullptr;
    eWidget* mButtonsWidget = nullptr;
    std::vector<eTradeResourceButton*> mButtons;
};

void eWorldTradeWidget::initialize(const std::string& name) {
    int iRes;
    int mult;
    iResAndMult(iRes, mult);

    setWidth(mult*75);

    if(true) { // editor mode
        const auto button = new eButton(window());

        button->setPressAction([this]() {
            if(!mTrade) return;
            const auto d = new eTradeEditWidget(window());
            const auto res = resolution();
            const int w = res.centralWidgetSmallWidth();
            const int h = res.centralWidgetSmallHeight();
            d->resize(w, h);
            d->initialize(mTrade, [this]() {
                setTrade(mTrade);
            });

            window()->execDialog(d);
            d->align(eAlignment::center);
        });

        mNameLabel = button;
    } else {
        mNameLabel = new eLabel(window());
    }
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
    const bool edit = mBoard ? mBoard->editorMode() : false;
    mBuysWidget->setTrade(buys);
    mSellsWidget->setTrade(sells);
    const bool neb = buys && !buys->empty();
    const bool nes = sells && !sells->empty();
    mBuysWidget->setVisible(neb && (!cc || edit));
    mSellsWidget->setVisible(nes && (!cc || edit));
    mGoodsLabel->setVisible(c.get() && (!cc || edit));
    mOrdersButton->setVisible((neb || nes) && (!cc || edit));
    updateTradeY();

    if(c) {
        const auto rel = c->relationship();
        if(rel == eWorldCityRelationship::rival) {
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
