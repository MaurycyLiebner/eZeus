#include "eselectcolonywidget.h"

#include "eworldmapwidget.h"
#include "eproceedbutton.h"
#include "eworldmenu.h"
#include "engine/ecampaign.h"
#include "elanguage.h"

void eSelectColonyWidget::initialize(const eColonySelection& sel,
                                     const eCitySelected& s,
                                     eWorldBoard* const board) {
    const auto menu = new eWorldMenu(window());
    menu->initialize(nullptr, nullptr, nullptr, nullptr, false);

    const auto res = resolution();
    const double mult = res.multiplier();

    const auto tw = new eLabel(window());
    tw->setNoPadding();
    tw->setSmallFontSize();
    menu->addWidget(tw);
    tw->move(18*mult, 31*mult);
    tw->resize(155*mult, 58*mult);

    const auto w = new eWidget(window());
    w->setNoPadding();
    menu->addWidget(w);
    w->move(17*mult, 178*mult);
    w->resize(158*mult, 216*mult);

    const auto cityLabel = new eLabel(window());
    cityLabel->setNoPadding();
    cityLabel->setSmallFontSize();
    cityLabel->setWrapWidth(w->width());
    w->addWidget(cityLabel);

    const auto buttonW = new eWidget(window());
    buttonW->setNoPadding();

    const auto proceedL = new eLabel(window());
    proceedL->setNoPadding();
    proceedL->setTinyFontSize();
    proceedL->setText(eLanguage::zeusText(62, 38));
    proceedL->fitContent();
    buttonW->addWidget(proceedL);

    const auto selectedCity = std::make_shared<stdsptr<eWorldCity>>();

    const auto proceed = new eProceedButton(window());
    proceed->setPressAction([s, selectedCity]() {
        s(*selectedCity);
    });
    buttonW->addWidget(proceed);

    buttonW->stackHorizontally();
    buttonW->fitContent();
    proceedL->align(eAlignment::vcenter);
    proceed->align(eAlignment::vcenter);

    w->addWidget(buttonW);
    buttonW->align(eAlignment::bottom | eAlignment::right);

    const auto citySelectedA = [cityLabel, tw, sel, selectedCity](
                               const stdsptr<eWorldCity>& c) {
        c->setState(eCityState::active);
        *selectedCity = c;
        for(const auto ep : sel) {
            const auto cc = ep->fCity;
            if(cc != c) continue;
            cityLabel->setText(ep->fSelection);
            cityLabel->fitContent();
            break;
        }
        tw->setText(c->name());
    };

    std::vector<stdsptr<eWorldCity>> selC;
    for(const auto ep : sel) {
        selC.push_back(ep->fCity);
    }

    const auto wmw = new eWorldMapWidget(window());
    addWidget(wmw);
    wmw->setSelectColonyMode(true, selC);
    wmw->setSelectCityAction(citySelectedA);
    wmw->setWorldBoard(board);
    wmw->align(eAlignment::center);
    wmw->setX((width() - menu->width() - wmw->width())/2);

    addWidget(menu);
    menu->align(eAlignment::right | eAlignment::top);

    citySelectedA(selC[0]);
}
