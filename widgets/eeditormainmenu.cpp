#include "eeditormainmenu.h"

#include "eframedwidget.h"
#include "eframedbutton.h"
#include "elanguage.h"
#include "eworldwidget.h"
#include "egamewidget.h"
#include "emainwindow.h"
#include "audio/emusic.h"
#include "ebitmapwidget.h"
#include "eepisodeswidget.h"
#include "etextscroller.h"
#include "equestionwidget.h"

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
    editParentMap->setSmallFontSize();
    editParentMap->setSmallPadding();
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
    editWorldMap->setSmallFontSize();
    editWorldMap->setSmallPadding();
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
    nationality->setSmallFontSize();
    nationality->setSmallPadding();
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
    bitmap->setSmallFontSize();
    bitmap->setSmallPadding();
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

    const auto advTextB = new eFramedButton(window());
    advTextB->setUnderline(false);
    advTextB->setSmallPadding();
    advTextB->setSmallFontSize();
    advTextB->setText("x");
    advTextB->setTooltip(eLanguage::zeusText(278, 6));
    advTextB->fitContent();
    topButtons->addWidget(advTextB);

    const auto advTextL = new eLabel(window());
    advTextL->setNoPadding();
    advTextL->setTinyFontSize();
    advTextL->setText(eLanguage::zeusText(195, 5));
    advTextL->fitContent();
    topButtons->addWidget(advTextL);

    const auto saveButton = new eFramedButton(window());
    saveButton->setUnderline(false);
    saveButton->setSmallFontSize();
    saveButton->setSmallPadding();
    saveButton->setText(eLanguage::zeusText(44, 74));
    saveButton->fitContent();
    topButtons->addWidget(saveButton);
    saveButton->setPressAction([campaign]() {
        campaign->save();
    });

    const auto quitButton = new eFramedButton(window());
    quitButton->setUnderline(false);
    quitButton->setSmallFontSize();
    quitButton->setSmallPadding();
    quitButton->setText(eLanguage::zeusText(5, 0));
    quitButton->fitContent();
    topButtons->addWidget(quitButton);
    quitButton->setPressAction([campaign, this]() {
        const auto q = new eQuestionWidget(window());
        const auto saveA = [this, campaign]() {
            campaign->save();
            window()->showMainMenu();
        };
        const auto closeA = [this]() {
            window()->showMainMenu();
        };
        q->initialize(eLanguage::zeusText(195, 23),
                      eLanguage::zeusText(195, 25),
                      saveA, closeA);
        window()->execDialog(q);
        q->align(eAlignment::center);
    });

    topButtons->stackHorizontally(p);
    topButtons->fitContent();
    iw->addWidget(topButtons);
    advTextL->align(eAlignment::vcenter);

    const auto hW = new eWidget(window());
    hW->setNoPadding();

    const int eww = 2*iw->width()/3;
    const int ewww = iw->width() - eww - 4*p;

    const auto textW = new eWidget(window());
    textW->setNoPadding();
    textW->setWidth(ewww);

    textW->setHeight(iw->height() - topButtons->height());

    const auto titleTitle = new eLabel(window());
    titleTitle->setTinyFontSize();
    titleTitle->setNoPadding();
    titleTitle->setText(eLanguage::zeusText(195, 6));
    titleTitle->fitContent();
    textW->addWidget(titleTitle);
    titleTitle->align(eAlignment::hcenter);

    const auto titleText = new eFramedLabel(window());
    titleText->setTinyFontSize();
    titleText->setTinyPadding();
    titleText->setType(eFrameType::inner);
    titleText->setWidth(ewww);
    titleText->setText("Height");
    titleText->fitHeight();
    titleText->setText("");
    textW->addWidget(titleText);

    const int textH = (textW->height() - 4*titleTitle->height() -
                      titleText->height())/3;

    const auto introTitle = new eLabel(window());
    introTitle->setTinyFontSize();
    introTitle->setNoPadding();
    introTitle->setText(eLanguage::zeusText(195, 7));
    introTitle->fitContent();
    textW->addWidget(introTitle);
    introTitle->align(eAlignment::hcenter);

    const auto introText = new eTextScroller(window());
    introText->setWidth(ewww);
    introText->setHeight(textH);
    introText->initialize();
    introText->setTinyTextFontSize();
    introText->setTinyTextPadding();
    textW->addWidget(introText);

    const auto completeTitle = new eLabel(window());
    completeTitle->setTinyFontSize();
    completeTitle->setNoPadding();
    completeTitle->setText(eLanguage::zeusText(195, 8));
    completeTitle->fitContent();
    textW->addWidget(completeTitle);
    completeTitle->align(eAlignment::hcenter);

    const auto completeText = new eTextScroller(window());
    completeText->setWidth(ewww);
    completeText->setHeight(textH);
    completeText->initialize();
    completeText->setTinyTextFontSize();
    completeText->setTinyTextPadding();
    textW->addWidget(completeText);

    const auto selectionTitle = new eLabel(window());
    selectionTitle->setTinyFontSize();
    selectionTitle->setNoPadding();
    selectionTitle->setText(eLanguage::zeusText(195, 58));
    selectionTitle->fitContent();
    textW->addWidget(selectionTitle);
    selectionTitle->align(eAlignment::hcenter);

    const auto selectionText = new eTextScroller(window());
    selectionText->setWidth(ewww);
    selectionText->setHeight(textH);
    selectionText->initialize();
    selectionText->setTinyTextFontSize();
    selectionText->setTinyTextPadding();
    textW->addWidget(selectionText);

    textW->stackVertically();

    const auto vW = new eWidget(window());
    vW->setNoPadding();

    const auto eW = new eEpisodesWidget(window());
    eW->setWidth(eww);
    const int ehh = 2*frame->height()/3;
    eW->setHeight(ehh);
    const auto setTextE = [advTextB, campaign,
                           titleTitle, titleText,
                           introTitle, introText,
                           completeTitle, completeText,
                           selectionTitle, selectionText](const int id) {
        advTextB->setText("");

        campaign->loadStrings();
        const auto& es = campaign->parentCityEpisodes();
        const auto e = es[id];

        titleTitle->setVisible(!e->fTitle.empty());
        titleText->setText(e->fTitle);
        titleText->setVisible(!e->fTitle.empty());

        introTitle->setVisible(!e->fIntroduction.empty());
        introText->setText(e->fIntroduction);
        introText->setVisible(!e->fIntroduction.empty());

        completeTitle->setVisible(!e->fComplete.empty());
        completeText->setText(e->fComplete);
        completeText->setVisible(!e->fComplete.empty());

        selectionTitle->hide();
        selectionText->hide();
    };

    const auto pressE = [advTextB, eW, campaign,
                        titleTitle, titleText,
                        introTitle, introText,
                        completeTitle, completeText,
                        selectionTitle, selectionText]() {
        advTextB->setText("x");
        eW->deselectText();

        campaign->loadStrings();

        const auto t = campaign->titleText();
        titleTitle->setVisible(!t.empty());
        titleText->setText(t);
        titleText->setVisible(!t.empty());

        const auto i = campaign->introductionText();
        introTitle->setVisible(!i.empty());
        introText->setText(i);
        introText->setVisible(!i.empty());

        const auto c = campaign->completeText();
        completeTitle->setVisible(!c.empty());
        completeText->setText(c);
        completeText->setVisible(!c.empty());

        selectionTitle->hide();
        selectionText->hide();
    };

    advTextB->setPressAction(pressE);

    eW->intialize(campaign, setTextE);
    vW->addWidget(eW);

    vW->stackVertically();
    vW->fitContent();
    hW->addWidget(vW);

    hW->addWidget(textW);

    hW->stackHorizontally();
    hW->fitContent();
    iw->addWidget(hW);

    iw->stackVertically();
    frame->align(eAlignment::center);

    pressE();
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
