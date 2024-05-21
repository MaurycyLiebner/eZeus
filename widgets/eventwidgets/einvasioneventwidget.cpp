#include "einvasioneventwidget.h"

#include "engine/egameboard.h"

#include "widgets/eframedbutton.h"
#include "widgets/echoosebutton.h"
#include "elanguage.h"
#include "emainwindow.h"
#include "widgets/elabeledwidget.h"
#include "widgets/evaluebutton.h"
#include "widgets/ecitybutton.h"

void eInvasionEventWidget::initialize(eInvasionEvent* const e) {
    const auto cityButtonL = new eLabeledWidget(window());
    const auto cc = e->city();
    const auto cityButton = new eCityButton(window());
    auto& board = e->getBoard();
    cityButton->initialize(board, [this, e](const stdsptr<eWorldCity>& c){
        e->setCity(c);
        setCity(c.get());
    });
    cityButton->setCity(cc);
    cityButtonL->setup(eLanguage::text("city:"), cityButton);
    addWidget(cityButtonL);

    mInfantryButtonL = new eLabeledWidget(window());
    const auto infantryButton = new eValueButton(window());
    infantryButton->setValueChangeAction([e](const int p) {
        e->setInfantry(p);
    });
    infantryButton->initialize(0, 999);
    infantryButton->setValue(e->infantry());
    mInfantryButtonL->setup(eLanguage::text("infantry:"), infantryButton);
    addWidget(mInfantryButtonL);

    mCavalryButtonL = new eLabeledWidget(window());
    const auto cavalryButton = new eValueButton(window());
    cavalryButton->setValueChangeAction([e](const int p) {
        e->setCavalry(p);
    });
    cavalryButton->initialize(0, 999);
    cavalryButton->setValue(e->cavalry());
    mCavalryButtonL->setup(eLanguage::text("cavalry:"), cavalryButton);
    addWidget(mCavalryButtonL);

    mArchersButtonL = new eLabeledWidget(window());
    const auto archersButton = new eValueButton(window());
    archersButton->setValueChangeAction([e](const int p) {
        e->setArchers(p);
    });
    archersButton->initialize(0, 999);
    archersButton->setValue(e->archers());
    mArchersButtonL->setup(eLanguage::text("range:"), archersButton);
    addWidget(mArchersButtonL);

    const int p = padding();
    stackVertically(p);
    fitContent();

    setCity(cc.get());
}

void eInvasionEventWidget::setCity(eWorldCity* const c) {
    const auto type = c ? c->type() : eWorldCityType::ruins; ;
    bool infantryVisible = false;
    bool cavalryVisible = false;
    bool archersVisible = false;
    switch(type) {
    case eWorldCityType::greekCity:
        infantryVisible = true;
        cavalryVisible = true;
        archersVisible = true;
        break;
    case eWorldCityType::trojanCity:
        infantryVisible = true;
        cavalryVisible = true;
        archersVisible = true;
        break;
    case eWorldCityType::persianCity:
        infantryVisible = true;
        cavalryVisible = true;
        archersVisible = true;
        break;
    case eWorldCityType::centaurCity:
        cavalryVisible = true;
        archersVisible = true;
        break;
    case eWorldCityType::amazonCity:
        infantryVisible = true;
        archersVisible = true;
        break;

    case eWorldCityType::egyptianCity:
        infantryVisible = true;
        cavalryVisible = true;
        archersVisible = true;
        break;
    case eWorldCityType::mayanCity:
        infantryVisible = true;
        archersVisible = true;
        break;
    case eWorldCityType::phoenicianCity:
        cavalryVisible = true;
        archersVisible = true;
        break;
    case eWorldCityType::oceanidCity:
        infantryVisible = true;
        archersVisible = true;
        break;
    case eWorldCityType::atlanteanCity:
        infantryVisible = true;
        cavalryVisible = true;
        archersVisible = true;
        break;

    default:
        break;
    }

    mInfantryButtonL->setVisible(infantryVisible);
    mCavalryButtonL->setVisible(cavalryVisible);
    mArchersButtonL->setVisible(archersVisible);
}
