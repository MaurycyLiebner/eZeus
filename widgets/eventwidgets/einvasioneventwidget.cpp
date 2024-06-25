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
    const auto board = e->worldBoard();
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

    const auto invasionPointButtonL = new eLabeledWidget(window());
    const auto invasionPointButton = new eValueButton(window());
    invasionPointButton->setValueChangeAction([e](const int p) {
        e->setInvasionPoint(p - 1);
    });
    invasionPointButton->initialize(0, 999);
    invasionPointButton->setValue(e->invasionPoint() + 1);
    invasionPointButtonL->setup(eLanguage::text("invasion_point:"), invasionPointButton);
    addWidget(invasionPointButtonL);

    const int p = padding();
    stackVertically(p);
    fitContent();

    setCity(cc.get());
}

void eInvasionEventWidget::setCity(eWorldCity* const c) {
    bool infantryVisible = false;
    bool cavalryVisible = false;
    bool archersVisible = false;
    if(c) {
        const auto nat = c->nationality();
        switch(nat) {
        case eNationality::greek:
            infantryVisible = true;
            cavalryVisible = true;
            archersVisible = true;
            break;
        case eNationality::trojan:
            infantryVisible = true;
            cavalryVisible = true;
            archersVisible = true;
            break;
        case eNationality::persian:
            infantryVisible = true;
            cavalryVisible = true;
            archersVisible = true;
            break;
        case eNationality::centaur:
            cavalryVisible = true;
            archersVisible = true;
            break;
        case eNationality::amazon:
            infantryVisible = true;
            archersVisible = true;
            break;

        case eNationality::egyptian:
            infantryVisible = true;
            cavalryVisible = true;
            archersVisible = true;
            break;
        case eNationality::mayan:
            infantryVisible = true;
            archersVisible = true;
            break;
        case eNationality::phoenician:
            cavalryVisible = true;
            archersVisible = true;
            break;
        case eNationality::oceanid:
            infantryVisible = true;
            archersVisible = true;
            break;
        case eNationality::atlantean:
            infantryVisible = true;
            cavalryVisible = true;
            archersVisible = true;
            break;

        default:
            break;
        }
    }

    mInfantryButtonL->setVisible(infantryVisible);
    mCavalryButtonL->setVisible(cavalryVisible);
    mArchersButtonL->setVisible(archersVisible);
}
