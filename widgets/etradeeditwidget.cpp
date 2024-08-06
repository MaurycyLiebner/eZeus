#include "etradeeditwidget.h"

#include "evectorhelpers.h"
#include "elanguage.h"
#include "evaluebutton.h"
#include "eresourcebutton.h"
#include "ecancelbutton.h"

class eTradeResourceButton : public eWidget {
public:
    using eWidget::eWidget;

    void initialize(const eResourceType type, const int count,
                    const eAction& changeAction,
                    const eAction& removeAction) {
        setNoPadding();
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
        closeButton->align(eAlignment::vcenter);
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
void eTradeEditWidget::initialize(std::vector<eResourceTrade>* const trade) {
    const auto changeAction = [this]() {
        updateVector();
    };

    setType(eFrameType::message);

    const int p = 2*padding();

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
        b->initialize(r.fType, r.fMax, changeAction,
                      [this, b, changeAction]() {
            eVectorHelpers::remove(mButtons, b);
            b->deleteLater();
            changeAction();
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
        b->initialize(r, 12, changeAction,
                      [this, b, changeAction]() {
            eVectorHelpers::remove(mButtons, b);
            b->deleteLater();
            changeAction();
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
    addButton->setUnderline(false);
    addButton->fitContent();
    mInnerWidget->addWidget(addButton);
    addButton->align(eAlignment::hcenter);

    mInnerWidget->stackVertically();
}

void eTradeEditWidget::updateVector() {
    mTrade->clear();
    for(const auto b : mButtons) {
        const auto type = b->type();
        const int count = b->count();
        eResourceTrade rt;
        rt.fMax = count;
        rt.fType = type;
        rt.fUsed = 0;
        mTrade->push_back(rt);
    }
}
