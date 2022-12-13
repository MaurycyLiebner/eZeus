#include "eworldwidget.h"

#include "eworldmenu.h"
#include "eworldmapwidget.h"
#include "erequestdialog.h"
#include "egiftdialog.h"
#include "eeventbackground.h"
#include "emainwindow.h"
#include "egamewidget.h"

void eWorldWidget::initialize() {
    mWM = new eWorldMenu(window());
    const auto requestFunc = [this]() {
        openRequestDialog();
    };
    const auto giftFunc = [this]() {
        openGiftDialog();
    };
    mWM->initialize(requestFunc, giftFunc);

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
    const auto bg = new eEventBackground(window());
    bg->initialize(this, d, true, nullptr);
}

void eWorldWidget::openGiftDialog() {
    const auto d = new eGiftDialog(window());
    const auto func = [this, d](const eResourceType type) {

    };
    d->initialize(mCity, func, *mBoard);
    addWidget(d);
    d->align(eAlignment::vcenter);
    d->setX(mWMW->x() + (mWMW->width() - d->width())/2);
    const auto bg = new eEventBackground(window());
    bg->initialize(this, d, true, nullptr);
}

bool eWorldWidget::keyPressEvent(const eKeyPressEvent& e) {
    const auto k = e.key();
    if(k == SDL_SCANCODE_ESCAPE) {
        window()->showGame(nullptr, eGameWidgetSettings());
    }
    return true;
}
