#include "eworldwidget.h"

#include "eworldmenu.h"
#include "eworldmapwidget.h"
#include "erequestdialog.h"
#include "eeventbackground.h"
#include "emainwindow.h"
#include "egamewidget.h"

void eWorldWidget::initialize() {
    mWM = new eWorldMenu(window());
    mWM->initialize([this]() {
        openRequestDialog();
    });
    addWidget(mWM);
    mWM->align(eAlignment::right | eAlignment::top);

    mWMW = new eWorldMapWidget(window());
    mWMW->initialize();
    addWidget(mWMW);
    mWMW->align(eAlignment::center);
    mWMW->setX((width() - mWM->width() - mWMW->width())/2);

    mWMW->setSelectCityAction([this](const stdsptr<eWorldCity>& ct) {
        mCity = ct;
        mWM->setCity(ct);
    });
}

void eWorldWidget::setBoard(eGameBoard* const board) {
    mBoard = board;
    mWMW->setBoard(board ? &board->getWorldBoard() : nullptr);
}

void eWorldWidget::openRequestDialog() {
    const auto d = new eRequestDialog(window());
    const auto func = [this, d](const eResourceType type) {
        mBoard->request(mCity, type);
        d->deleteLater();
    };
    d->initialize(mCity, func);
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
