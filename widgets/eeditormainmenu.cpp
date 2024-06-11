#include "eeditormainmenu.h"

#include "eframedwidget.h"
#include "eframedbutton.h"
#include "elanguage.h"
#include "eworldwidget.h"
#include "egamewidget.h"
#include "emainwindow.h"
#include "audio/emusic.h"
#include "ebitmapwidget.h"

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
    editParentMap->setTooltip(eLanguage::zeusText(278, 4));
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
    editWorldMap->setTooltip(eLanguage::zeusText(278, 5));
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

    const auto nationality = new eFramedButton(window());
    nationality->setUnderline(false);
    const bool a = campaign->atlantean();
    nationality->setText(a ? eLanguage::zeusText(195, 60) : // atlantean
                             eLanguage::zeusText(195, 59)); // greek
    nationality->fitContent();
    nationality->setTooltip(eLanguage::zeusText(278, 10));
    nationality->setPressAction([campaign, nationality]() {
        const bool a = !campaign->atlantean();
        campaign->setAtlantean(a);
        nationality->setText(a ? eLanguage::zeusText(195, 60) : // atlantean
                                 eLanguage::zeusText(195, 59)); // greek
    });
    topButtons->addWidget(nationality);

    const auto bitmap = new eFramedButton(window());
    bitmap->setUnderline(false);
    bitmap->setText(eLanguage::zeusText(195, 47));
    bitmap->fitContent();
    bitmap->setTooltip(eLanguage::zeusText(278, 9));
    bitmap->setPressAction([this, campaign]() {
        const bool small = false;
        const int nRows = 3;
        const auto d = new eFramedWidget(window());
        d->setType(eFrameType::message);

        if(small) setSmallPadding();

        std::vector<eFramedButton*> buttons;

        for(int i = 0; i < 12; i++) {
            const auto b = new eFramedButton(window());
            b->setSmallPadding();
            b->setUnderline(false);
            if(small) {
                b->setSmallFontSize();
                b->setSmallPadding();
            }
            const auto bitmap = new eBitmapWidget(window());
            bitmap->setNoPadding();
            bitmap->setScaling(0.25);
            bitmap->setBitmap(i);
            bitmap->fitContent();
            b->addWidget(bitmap);
            b->fitContent();
            bitmap->align(eAlignment::center);
            b->setPressAction([d, campaign, i]() {
                campaign->setBitmap(i);
                d->deleteLater();
            });
            d->addWidget(b);
            buttons.push_back(b);
        }

        int colWidth = 0;
        for(const auto b : buttons) {
            const int w = b->width();
            if(w > colWidth) colWidth = w;
        }

        const int p = d->padding();

        int r = 0;
        int x = 2*p;
        int y = 2*p;

        for(const auto b : buttons) {
            b->setWidth(colWidth);
            b->move(x, y);
            y += b->height() + p;
            r++;
            if(r >= nRows) {
                r = 0;
                x += colWidth + p;
                y = 2*p;
            }
        }

        d->fitContent();

        window()->execDialog(d);
        d->align(eAlignment::center);
    });
    topButtons->addWidget(bitmap);

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
