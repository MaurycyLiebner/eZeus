#include "eepisodeintroductionwidget.h"

#include "textures/egametextures.h"

#include "eframedwidget.h"
#include "engine/ecampaign.h"

#include "etextscroller.h"
#include "eproceedbutton.h"

#include "elanguage.h"
#include "emainwindow.h"
#include "eupbutton.h"
#include "edownbutton.h"
#include "egamewidget.h"

#include "audio/emusic.h"

void eEpisodeIntroductionWidget::initialize(
        const std::shared_ptr<eCampaign>& c) {
    const auto& intrfc = eGameTextures::interface();
    const auto res = resolution();
    const int iRes = static_cast<int>(res.uiScale());
    const auto& texs = intrfc[iRes];
    setTexture(texs.fIntroductionImage);

    const auto frame = new eFramedWidget(window());
    frame->setType(eFrameType::message);
    const int h = 2*height()/3;
    const int w = 3*h/2;
    frame->resize(w, h);

    const int p = res.hugePadding();

    const auto inner = new eWidget(window());
    inner->setNoPadding();
    const int iw = w - 2*p;
    const int ih = h - 2*p;
    inner->resize(iw, ih);
    inner->move(p, p);
    frame->addWidget(inner);

    const auto mainTitle = new eLabel(window());
    mainTitle->setNoPadding();
    mainTitle->setHugeFontSize();
    mainTitle->setText(c->titleText());
    mainTitle->fitContent();
    inner->addWidget(mainTitle);
    mainTitle->align(eAlignment::hcenter);

    const auto e = c->currentEpisode();
    const auto et = c->currentEpisodeType();

    const auto subTitle = new eLabel(window());
    subTitle->setNoPadding();
    subTitle->setText(e->fTitle);
    subTitle->fitContent();
    inner->addWidget(subTitle);

    const auto goalsFrame = new eFramedWidget(window());
    goalsFrame->setType(eFrameType::inner);
    goalsFrame->setNoPadding();
    goalsFrame->setWidth(iw);

    const auto goalsInner = new eWidget(window());
    goalsInner->setNoPadding();

    const auto& goals = e->fGoals;
    for(const auto& g : goals) {
        const auto w = new eWidget(window());
        w->setNoPadding();

        const auto checkBox = new eLabel(window());
        checkBox->setNoPadding();
        const auto& ctexs = texs.fCheckBox;
        checkBox->setTexture(ctexs.getTexture(1));
        checkBox->fitContent();
        w->addWidget(checkBox);

        const bool col = et == eEpisodeType::colony;
        const auto t = g->text(col, e->fAtlantean);
        const auto l = new eLabel(window());
        l->setSmallFontSize();
        l->setTinyPadding();
        l->setText(t);
        l->fitContent();
        w->addWidget(l);
        w->stackHorizontally(p);
        w->fitContent();
        checkBox->align(eAlignment::vcenter);
        l->align(eAlignment::vcenter);
        goalsInner->addWidget(w);
    }

    goalsInner->stackVertically();
    goalsInner->fitHeight();
    goalsInner->setWidth(iw - 2*p);
    goalsInner->move(p, p);
    goalsFrame->addWidget(goalsInner);
    goalsFrame->setHeight(goalsInner->height() + 2*p);
    inner->addWidget(goalsFrame);

    const auto lowerButtons = new eWidget(window());
    lowerButtons->setNoPadding();
    lowerButtons->setWidth(iw);

    const auto diffW = new eWidget(window());
    diffW->setNoPadding();

    const auto diffLabel = new eLabel(window());
    diffLabel->setNoPadding();
    diffLabel->setSmallFontSize();
    const auto diffText = eLanguage::zeusText(44, 219);
    const auto defDiff = eDifficulty::hero;
    const auto diff = std::make_shared<eDifficulty>(defDiff);
    c->setDifficulty(defDiff);
    const auto hdiff = eDifficultyHelpers::name(*diff);
    diffLabel->setText("  " + diffText + "  " + hdiff);
    diffLabel->fitContent();

    const auto up = new eUpButton(window());
    diffW->addWidget(up);
    up->setPressAction([diff, diffLabel, diffText, c]() {
        if(*diff == eDifficulty::olympian) return;
        const int diffi = static_cast<int>(*diff);
        *diff = static_cast<eDifficulty>(diffi + 1);
        const auto hdiff = eDifficultyHelpers::name(*diff);
        diffLabel->setText("  " + diffText + "  " + hdiff);
        diffLabel->fitContent();
        c->setDifficulty(*diff);
    });

    const auto down = new eDownButton(window());
    diffW->addWidget(down);
    down->setPressAction([diff, diffLabel, diffText, c]() {
        if(*diff == eDifficulty::beginner) return;
        const int diffi = static_cast<int>(*diff);
        *diff = static_cast<eDifficulty>(diffi - 1);
        const auto hdiff = eDifficultyHelpers::name(*diff);
        diffLabel->setText("  " + diffText + " " + hdiff);
        diffLabel->fitContent();
        c->setDifficulty(*diff);
    });

    diffW->addWidget(diffLabel);

    diffW->stackHorizontally();
    diffW->fitContent();
    lowerButtons->addWidget(diffW);

    const auto proceedW = new eWidget(window());
    proceedW->setNoPadding();

    const auto proceedLabel = new eLabel(window());
    proceedLabel->setSmallFontSize();
    proceedLabel->setSmallPadding();
    proceedLabel->setText(eLanguage::zeusText(62, 5));
    proceedLabel->fitContent();
    proceedW->addWidget(proceedLabel);

    const auto proceedB = new eProceedButton(window());
    proceedB->setPressAction([this, c]() {
        c->startEpisode();
        const auto w = window();
        w->startGameAction([w, c]() {
            eGameWidgetSettings settings;
            settings.fPaused = true;
            w->showGame(c, settings);
        });
    });
    proceedW->addWidget(proceedB);

    proceedW->stackHorizontally(2*p);
    proceedW->fitContent();
    proceedLabel->align(eAlignment::vcenter);
    proceedB->align(eAlignment::vcenter);

    lowerButtons->addWidget(proceedW);

    lowerButtons->layoutHorizontallyWithoutSpaces();
    lowerButtons->fitHeight();

    const auto introText = new eTextScroller(window());
    introText->setWidth(iw);
    int ith = ih - 4*p;
    ith -= mainTitle->height();
    ith -= subTitle->height();
    ith -= goalsFrame->height();
    ith -= lowerButtons->height();
    introText->setHeight(ith);
    introText->initialize();
    introText->setSmallTextFontSize();
    introText->setTinyTextPadding();
    introText->setText(e->fIntroduction);
    inner->addWidget(introText);

    inner->addWidget(lowerButtons);

    inner->stackVertically(p);

    addWidget(frame);
    frame->align(eAlignment::center);
}
