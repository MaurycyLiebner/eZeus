#include "eworldwidget.h"

#include "eworldmenu.h"
#include "eworldmapwidget.h"
#include "erequestdialog.h"
#include "egiftdialog.h"
#include "emainwindow.h"
#include "egamewidget.h"
#include "egiftsizedialog.h"
#include "evectorhelpers.h"

#include "gameEvents/eplayerconquestevent.h"

#include "buildings/eheroshall.h"

void eWorldWidget::initialize() {
    mWM = new eWorldMenu(window());
    const auto requestFunc = [this]() {
        openRequestDialog();
    };
    const auto giftFunc = [this]() {
        openGiftDialog();
    };
    const auto raidFunc = [this]() {
        const auto enlistAction = [this](const eEnlistedForces& forces) {
            mBoard->enlistForces(forces);
        };
        openEnlistForcesDialog(enlistAction, mCity);
    };
    const auto conquerFunc = [this]() {
        const auto enlistAction = [this](const eEnlistedForces& forces) {
            mBoard->enlistForces(forces);
            const auto e = e::make_shared<ePlayerConquestEvent>(
                               eGameEventBranch::root, *mBoard);
            const auto boardDate = mBoard->date();
            const int period = 150;
            const auto date = boardDate + period;
            e->initializeDate(date, period, 1);
            e->initialize(forces, mCity);
            mBoard->addRootGameEvent(e);
        };
        openEnlistForcesDialog(enlistAction, mCity);
    };
    mWM->initialize(requestFunc, giftFunc, raidFunc, conquerFunc);

    mWMW = new eWorldMapWidget(window());
    mWMW->initialize();
    addWidget(mWMW);
    mWMW->align(eAlignment::center);
    mWMW->setX((width() - mWM->width() - mWMW->width())/2);

    mWMW->setSelectCityAction([this](const stdsptr<eWorldCity>& ct) {
        mCity = ct;
        mWM->setCity(ct);
    });

    addWidget(mWM);
    mWM->align(eAlignment::right | eAlignment::top);
}

void eWorldWidget::setBoard(eGameBoard* const board) {
    mBoard = board;
    mWMW->setBoard(board ? &board->getWorldBoard() : nullptr);
}

void eWorldWidget::openRequestDialog() {
    const auto d = new eRequestDialog(window());
    const auto func = [this, d](const eResourceType type) {
        mBoard->request(mCity, type);
        const auto wb = mBoard->getWorldBoard();
        const auto& cts = wb.cities();
        for(const auto& ct : cts) {
            ct->incAttitude(-10);
        }
        mCity->incAttitude(-10);
        mWM->updateRelationshipLabel();
        d->deleteLater();
    };
    d->initialize(mCity, func);
    addWidget(d);
    d->align(eAlignment::vcenter);
    d->setX(mWMW->x() + (mWMW->width() - d->width())/2);
    window()->execDialog(d);
}

void eWorldWidget::openGiftDialog() {
    const auto d = new eGiftDialog(window());
    const auto func = [this, d](const eResourceType type) {
        const auto dd = new eGiftSizeDialog(window());
        const auto func = [this, d, dd](const eResourceType type,
                                        const int count) {
            mBoard->giftTo(mCity, type, count);
            d->deleteLater();
            dd->deleteLater();
        };
        dd->initialize(type, mCity, func, *mBoard);
        addWidget(dd);
        dd->align(eAlignment::vcenter);
        dd->setX(mWMW->x() + (mWMW->width() - dd->width())/2);
        window()->execDialog(dd);
    };
    d->initialize(mCity, func, *mBoard);
    addWidget(d);
    d->align(eAlignment::vcenter);
    d->setX(mWMW->x() + (mWMW->width() - d->width())/2);
    window()->execDialog(d);
}

void eWorldWidget::openEnlistForcesDialog(
        const eEnlistAction& a,
        const stdsptr<eWorldCity>& exclude) {
    auto f = mBoard->getEnlistableForces();
    eVectorHelpers::remove(f.fAllies, exclude);

//    {
//        f.fHeroes.push_back(eHeroType::achilles);
//        f.fHeroes.push_back(eHeroType::hercules);
//        f.fHeroes.push_back(eHeroType::bellerophon);

//        for(int i = 0; i < 20; i ++) {
//            const auto b = e::make_shared<eSoldierBanner>(eBannerType::hoplite, *mBoard);
//            b->incCount();
//            const auto n = new stdsptr<eSoldierBanner>(b);
//            f.fSoldiers.push_back(b);
//        }

//        for(int i = 0; i < 4; i ++) {
//            const auto b = e::make_shared<eSoldierBanner>(eBannerType::horseman, *mBoard);
//            b->incCount();
//            const auto n = new stdsptr<eSoldierBanner>(b);
//            f.fSoldiers.push_back(b);
//        }


//        for(int i = 0; i < 2; i ++) {
//            const auto b = e::make_shared<eSoldierBanner>(eBannerType::amazon, *mBoard);
//            b->incCount();
//            const auto n = new stdsptr<eSoldierBanner>(b);
//            f.fSoldiers.push_back(b);
//        }
//    }

    const auto d = new eEnlistForcesDialog(window());
    std::vector<bool> heroesAbroad;
    for(const auto h : f.fHeroes) {
        const auto hh = mBoard->heroHall(h);
        const bool abroad = !hh ? true : hh->heroOnQuest();
        heroesAbroad.push_back(abroad);
    }
    d->initialize(f, heroesAbroad, a);
    addWidget(d);
    d->align(eAlignment::vcenter);
    d->setX(mWMW->x() + (mWMW->width() - d->width())/2);
    window()->execDialog(d);
}

bool eWorldWidget::keyPressEvent(const eKeyPressEvent& e) {
    const auto k = e.key();
    if(k == SDL_SCANCODE_ESCAPE) {
        window()->showGame(nullptr, eGameWidgetSettings());
    }
    return true;
}
