#include "ecommonhouseinfowidget.h"

#include "buildings/esmallhouse.h"
#include "engine/eresourcetype.h"

#include "widgets/elabel.h"

#include "elanguage.h"

eCommonHouseInfoWidget::eCommonHouseInfoWidget(eMainWindow* const window) :
    eInfoWidget(window, true, true) {}

void eCommonHouseInfoWidget::initialize(eSmallHouse* const house) {
    std::string title;
    const int people = house->people();
    const int level = house->level();
    if(people <= 0) {
        title = "unoccupied_house";
    } else if(level == 0) {
        title = "hut_house";
    } else if(level == 1) {
        title = "shack_house";
    } else if(level == 2) {
        title = "hovel_house";
    } else if(level == 3) {
        title = "homestead_house";
    } else if(level == 4) {
        title = "tenement_house";
    } else if(level == 5) {
        title = "apartment_house";
    } else if(level == 6) {
        title = "townhouse_house";
    }
    eInfoWidget::initialize(eLanguage::text(title));

    const int p = padding();
    const auto fw = addFramedWidget(16*p);

    if(people <= 0) return;

    const auto miss = house->missing();
    std::string msg;
    switch(miss) {
    case eHouseMissing::water:
        msg = "missing_water";
        break;
    case eHouseMissing::food:
        msg = "missing_food";
        break;
    case eHouseMissing::fleece:
        msg = "missing_fleece";
        break;
    case eHouseMissing::oil:
        msg = "missing_oil";
        break;
    case eHouseMissing::venues:
        msg = "missing_venues";
        break;
    case eHouseMissing::appeal:
        msg = "missing_appeal";
        break;
    case eHouseMissing::nothing:
        msg = "missing_nothing";
        break;
    }

    const auto cw = centralWidget();
    const auto msgLabel = new eLabel(window());
    msgLabel->setSmallFontSize();
    msgLabel->setWidth(cw->width() - 2*p);
    msgLabel->setWrapWidth(msgLabel->width());
    msgLabel->setText(eLanguage::text(msg));
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

    const auto w = new eWidget(window());
    w->setNoPadding();

    const auto food = generateSupply(eResourceType::food, house->food());
    const auto fleece = generateSupply(eResourceType::fleece, house->fleece());
    const auto oil = generateSupply(eResourceType::oliveOil, house->oil());

    w->addWidget(food);
    w->addWidget(fleece);
    w->addWidget(oil);

    w->setWidth(cw->width());
    w->layoutHorizontally();
    w->fitContent();
    cw->addWidget(w);
    w->setY(msgLabel->y() + msgLabel->height() + p);

    const auto occ = new eLabel(window());
    occ->setSmallFontSize();
    occ->setSmallPadding();
    auto occstr = std::to_string(house->people()) + " " +
                  eLanguage::text("occupants");
    const int vacs = house->vacancies();
    if(vacs) {
        occstr += "  " + eLanguage::text("extra_room") + " " +
                  std::to_string(vacs);
    }
    occ->setText(occstr);
    occ->fitContent();
    fw->addWidget(occ);
    occ->align(eAlignment::hcenter);

    const auto taxLabel = new eLabel(window());
    {
        const bool paid = house->paidTaxes();
        taxLabel->setSmallFontSize();
        taxLabel->setTinyPadding();
        taxLabel->setWidth(fw->width());
        taxLabel->setWrapWidth(taxLabel->width());
        std::string paidstr;
        if(paid) {
            paidstr = "clerk_visited";
        } else {
            paidstr = "clerk_not_visited";
        }
        taxLabel->setText(eLanguage::text(paidstr));
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
        if(house->water() && house->food()) {
            satstr = "residents_happy";
        } else {
            satstr = "residents_dissatisfied";
        }
        satLabel->setText(eLanguage::text(satstr));
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
        foodLabel->setText(eLanguage::text("residents_no_food"));
        foodLabel->fitContent();
        fw->addWidget(foodLabel);
        foodLabel->setY(satLabel->y() + satLabel->height());
    }
}
