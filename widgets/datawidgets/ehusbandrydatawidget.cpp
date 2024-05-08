#include "ehusbandrydatawidget.h"

#include "engine/egameboard.h"

#include "eviewmodebutton.h"

#include "elanguage.h"
#include "widgets/elinewidget.h"
#include "widgets/emultilinelabel.h"

void eHusbandryDataWidget::initialize() {
    {
        mSeeHusbandry = new eViewModeButton(
                        eLanguage::text("see_husbandry"),
                        eViewMode::husbandry,
                        window());
        addViewButton(mSeeHusbandry);
    }

    eDataWidget::initialize();


    const auto iw = innerWidget();

    const auto canSupport1 = new eMultiLineLabel(window());
    canSupport1->setTinyFontSize();
    canSupport1->setNoPadding();
    canSupport1->setText(eLanguage::text("current_food_can_support_1"));
    canSupport1->fitContent();
    iw->addWidget(canSupport1);
    canSupport1->align(eAlignment::hcenter);

    mCanSupportLabel = new eLabel("0", window());
    mCanSupportLabel->setNoPadding();
    mCanSupportLabel->setYellowFontColor();
    mCanSupportLabel->fitContent();
    iw->addWidget(mCanSupportLabel);
    mCanSupportLabel->align(eAlignment::hcenter);

    const auto canSupport2 = new eMultiLineLabel(window());
    canSupport2->setTinyFontSize();
    canSupport2->setNoPadding();
    canSupport2->setText(eLanguage::text("current_food_can_support_2"));
    canSupport2->fitContent();
    iw->addWidget(canSupport2);
    canSupport2->align(eAlignment::hcenter);

    const auto spacer1 = new eWidget(window());
    spacer1->setHeight(spacing());
    iw->addWidget(spacer1);

    const auto l1 = new eLineWidget(window());
    l1->setNoPadding();
    l1->fitContent();
    l1->setWidth(iw->width());
    iw->addWidget(l1);

    const auto spacer2 = new eWidget(window());
    spacer2->setHeight(spacing());
    iw->addWidget(spacer2);

    const auto storedFood1 = new eMultiLineLabel(window());
    storedFood1->setTinyFontSize();
    storedFood1->setNoPadding();
    storedFood1->setText(eLanguage::text("stored_food_for_1"));
    storedFood1->fitContent();
    iw->addWidget(storedFood1);
    storedFood1->align(eAlignment::hcenter);

    mStoredFoodLabel = new eLabel("0", window());
    mStoredFoodLabel->setNoPadding();
    mStoredFoodLabel->setYellowFontColor();
    mStoredFoodLabel->fitContent();
    iw->addWidget(mStoredFoodLabel);
    mStoredFoodLabel->align(eAlignment::hcenter);

    const auto storedFood2 = new eMultiLineLabel(window());
    storedFood2->setTinyFontSize();
    storedFood2->setNoPadding();
    storedFood2->setText(eLanguage::text("stored_food_for_2"));
    storedFood2->fitContent();
    iw->addWidget(storedFood2);
    storedFood2->align(eAlignment::hcenter);

    iw->stackVertically();
}

void eHusbandryDataWidget::paintEvent(ePainter& p) {
    const bool update = (++mTime % 20) == 0;
    if(update) {
        mBoard.updateResources();
        const auto& husbData = mBoard.husbandryData();

        const int a = husbData.canSupport();
        mCanSupportLabel->setText(std::to_string(a));
        mCanSupportLabel->fitContent();
        mCanSupportLabel->align(eAlignment::hcenter);

        const int v = husbData.storedFood();
        mStoredFoodLabel->setText(std::to_string(v));
        mStoredFoodLabel->fitContent();
        mStoredFoodLabel->align(eAlignment::hcenter);
    }
    eWidget::paintEvent(p);
}

