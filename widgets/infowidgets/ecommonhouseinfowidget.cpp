#include "ecommonhouseinfowidget.h"

#include "buildings/esmallhouse.h"
#include "buildings/eelitehousing.h"
#include "engine/eresourcetype.h"

#include "widgets/elabel.h"

#include "elanguage.h"

eCommonHouseInfoWidget::eCommonHouseInfoWidget(eMainWindow* const window) :
    eInfoWidget(window, true, true) {}

void eCommonHouseInfoWidget::initialize(eHouseBase* const house) {
    const int people = house->people();
    const int level = house->level();
    const auto type = house->type();
    int titleGroup = 29;
    int titleString = 0;
    if(type == eBuildingType::commonHouse) {
        if(people <= 0) {
            titleGroup = 128;
            titleString = 0;
        } else if(level == 0) {
            titleString = 0;
        } else if(level == 1) {
            titleString = 1;
        } else if(level == 2) {
            titleString = 2;
        } else if(level == 3) {
            titleString = 3;
        } else if(level == 4) {
            titleString = 4;
        } else if(level == 5) {
            titleString = 5;
        } else if(level == 6) {
            titleString = 6;
        }
    } else { // elite
        if(people <= 0) {
            titleString = 7;
        } else if(level == 0) {
            titleString = 8;
        } else if(level == 1) {
            titleString = 9;
        } else if(level == 2) {
            titleString = 10;
        } else if(level == 3) {
            titleString = 11;
        } else if(level == 4) {
            titleString = 12;
        }
    }
    const auto title = eLanguage::zeusText(titleGroup, titleString);
    eInfoWidget::initialize(title);
    addCentralWidget();

    const int p = padding();
    const auto fw = addFramedWidget(16*p);

    if(people <= 0) return;

    const auto miss = house->missing();
    int needString;
    switch(miss) {
    case eHouseMissing::water:
        needString = 49;
        break;
    case eHouseMissing::food:
        needString = 51;
        break;
    case eHouseMissing::fleece:
        needString = 54;
        break;
    case eHouseMissing::oil:
        needString = 55;
        break;
    case eHouseMissing::venues:
        needString = 50;
        break;
    case eHouseMissing::appeal:
        needString = 48;
        break;
    case eHouseMissing::wine:
        needString = 53;
        break;
    case eHouseMissing::arms:
        needString = 57;
        break;
    case eHouseMissing::horse:
        needString = 56;
        break;
    case eHouseMissing::nothing:
        needString = 46;
        break;
    }
    const auto msg = eLanguage::zeusText(127, needString);

    const auto cw = centralWidget();
    const auto msgLabel = new eLabel(window());
    msgLabel->setSmallFontSize();
    msgLabel->setWidth(cw->width() - 2*p);
    msgLabel->setWrapWidth(msgLabel->width());
    msgLabel->setText(msg);
    msgLabel->fitContent();
    cw->addWidget(msgLabel);

    const auto supplies = new eWidget(window());
    supplies->setNoPadding();
    const auto generateSupply = [&](const eResourceType type,
                                    const int count) {
        const auto w = new eWidget(window());
        w->setNoPadding();

        const auto res = resolution();
        const auto tex = eResourceTypeHelpers::icon(res.uiScale(), type);
        const auto iconLabel = new eLabel(window());
        iconLabel->setTexture(tex);
        iconLabel->fitContent();
        w->addWidget(iconLabel);

        const auto countLabel = new eLabel(window());
        countLabel->setSmallFontSize();
        const auto cStr = std::to_string(count);
        countLabel->setText(cStr);
        countLabel->fitContent();
        w->addWidget(countLabel);

        w->stackHorizontally();
        w->fitContent();
        iconLabel->align(eAlignment::vcenter);
        countLabel->align(eAlignment::vcenter);

        return w;
    };

    const auto generateSupplyWidget = [&](const std::vector<eWidget*>& wids) {
        const auto w = new eWidget(window());
        w->setNoPadding();

        for(const auto wid : wids) {
            w->addWidget(wid);
        }

        w->setWidth(cw->width());
        w->layoutHorizontally();
        w->fitContent();
        cw->addWidget(w);
        return w;
    };

    {
        const auto food = generateSupply(eResourceType::food, house->food());
        const auto fleece = generateSupply(eResourceType::fleece, house->fleece());
        const auto oil = generateSupply(eResourceType::oliveOil, house->oil());

        const auto w = generateSupplyWidget({food, fleece, oil});
        w->setY(msgLabel->y() + msgLabel->height() + p);

        if(house->type() == eBuildingType::eliteHousing) {
            const auto eh = static_cast<eEliteHousing*>(house);

            const auto wine = generateSupply(eResourceType::wine, eh->wine());
            const auto arms = generateSupply(eResourceType::armor, eh->arms());
            const auto horse = generateSupply(eResourceType::horse, eh->horses());

            const auto ww = generateSupplyWidget({wine, arms, horse});
            ww->setY(w->y() + 3*p);
        }
    }

    const auto occ = new eLabel(window());
    occ->setSmallFontSize();
    occ->setSmallPadding();
    auto occstr = std::to_string(house->people()) + " " +
                  eLanguage::zeusText(127, 15);
    const int vacs = house->vacancies();
    if(vacs) {
        occstr += "  " + eLanguage::zeusText(127, 17) + " " +
                  std::to_string(vacs);
    }
    occ->setText(occstr);
    occ->fitContent();
    fw->addWidget(occ);
    occ->align(eAlignment::hcenter);

    const auto taxLabel = new eLabel(window());
    {
        const int paid = house->paidTaxes();
        taxLabel->setSmallFontSize();
        taxLabel->setTinyPadding();
        taxLabel->setWidth(fw->width());
        taxLabel->setWrapWidth(taxLabel->width());
        std::string taxStr;
        if(paid) {
            taxStr = eLanguage::zeusText(127, 19);
            taxStr += " " + std::to_string(paid) + " ";
            taxStr += eLanguage::zeusText(8, 1) + " ";
            taxStr += eLanguage::zeusText(127, 20);
        } else {
            taxStr = eLanguage::zeusText(127, 18);
        }
        taxLabel->setText(taxStr);
        taxLabel->fitContent();
        fw->addWidget(taxLabel);
        taxLabel->setY(occ->y() + occ->height());
    }

    const auto satLabel = new eLabel(window());
    {
        satLabel->setSmallFontSize();
        satLabel->setTinyPadding();
        satLabel->setWidth(fw->width());
        satLabel->setWrapWidth(satLabel->width());
        std::string satstr;
        if(type == eBuildingType::commonHouse) {
            const auto ch = static_cast<eSmallHouse*>(house);
            const int sat = ch->satisfaction();
            int n = std::floor((100 - sat)/(100./7));
            n = std::clamp(n, 0, 6);
            satstr = eLanguage::zeusText(127, 21 + n);
        } else { // elite
            satstr = eLanguage::zeusText(127, 21);
        }
        satLabel->setText(satstr);
        satLabel->fitContent();
        fw->addWidget(satLabel);
        satLabel->setY(taxLabel->y() + taxLabel->height());
    }

    if(!house->food()) {
        const auto foodLabel = new eLabel(window());
        foodLabel->setSmallFontSize();
        foodLabel->setTinyPadding();
        foodLabel->setWidth(fw->width());
        foodLabel->setWrapWidth(foodLabel->width());
        foodLabel->setText(eLanguage::zeusText(127, 28));
        foodLabel->fitContent();
        fw->addWidget(foodLabel);
        foodLabel->setY(satLabel->y() + satLabel->height());
    }
}
