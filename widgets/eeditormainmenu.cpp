#include "eeditormainmenu.h"

#include "eframedwidget.h"
#include "eframedbutton.h"
#include "elanguage.h"
#include "eworldwidget.h"
#include "egamewidget.h"
#include "emainwindow.h"
#include "audio/emusic.h"

void eEditorMainMenu::initialize(const stdsptr<eCampaign>& campaign) {
    eMainMenuBase::initialize();

    mCampaign = campaign;

    const auto res = resolution();
    const int p = res.largePadding();

    const auto frame = new eFramedWidget(window());
    frame->setType(eFrameType::message);
    frame->setNoPadding();
    const int w = 4*width()/5;
    const int h = 4*height()/5;
    const auto iw = new eWidget(window());
    frame->resize(w, h);
    iw->resize(w - 2*p, h - 2*p);
    frame->addWidget(iw);
    iw->move(p, p);
    addWidget(frame);

    const auto topButtons = new eWidget(window());
    topButtons->setNoPadding();

    const auto editParentMap = new eFramedButton(window());
    editParentMap->setText(eLanguage::zeusText(195, 3));
    editParentMap->setUnderline(false);
    editParentMap->fitContent();
    editParentMap->setPressAction([this, campaign]() {
        const auto w = window();
        w->takeWidget();
        w->startGameAction([this, campaign, w]() {
            eMusic::playRandomMusic();
            const auto gw = new eGameWidget(w);
            gw->setBoard(&campaign->parentCityBoard());
            gw->resize(w->width(), w->height());
            gw->initialize();
            eGameWidgetSettings settings;
            settings.fPaused = true;
            gw->setSettings(settings);
            w->setWidget(gw);
            addGoBackButton(gw);
        });
    });
    topButtons->addWidget(editParentMap);

    const auto editWorldMap = new eFramedButton(window());
    editWorldMap->setText(eLanguage::zeusText(195, 4));
    editWorldMap->setUnderline(false);
    editWorldMap->fitContent();
    editWorldMap->setPressAction([this, campaign]() {
        const auto w = window();
        const auto ww = new eWorldWidget(window());
        ww->resize(w->width(), w->height());
        ww->initialize();
        ww->setWorldBoard(&campaign->worldBoard());
        w->takeWidget();
        w->setWidget(ww);
        addGoBackButton(ww);
    });
    topButtons->addWidget(editWorldMap);
    topButtons->stackHorizontally();
    topButtons->fitContent();
    iw->addWidget(topButtons);

    iw->stackVertically();
    frame->align(eAlignment::center);
}

void eEditorMainMenu::addGoBackButton(eWidget* const to) {
    const auto b = new eFramedButton(window());
    b->setUnderline(false);
    b->setText(eLanguage::text("return"));
    b->fitContent();
    b->setRenderBg(true);
    const auto res = resolution();
    const int p = res.largePadding();
    to->addWidget(b);
    b->move(2*p, to->height() - b->height() - 2*p);
    b->setPressAction([this]() {
        const auto w = window();
        w->setWidget(this);
    });
}
