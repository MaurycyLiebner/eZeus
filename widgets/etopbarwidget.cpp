#include "etopbarwidget.h"

#include "engine/egameboard.h"
#include "engine/boardData/epopulationdata.h"
#include "textures/egametextures.h"
#include "ebutton.h"
#include "edatewidget.h"

#include "emainwindow.h"

void eTopBarWidget::initialize() {
    const auto& intrfc = eGameTextures::interface();
    const auto uiScale = resolution().uiScale();
    const int icoll = static_cast<int>(uiScale);
    const int mult = icoll + 1;
    const auto& coll = intrfc[icoll];
    setPadding(0);

    const auto s0 = new eWidget(window());
    s0->setWidth(mult*25);

    mDrachmasWidget = new eTopWidget(window());
    mDrachmasWidget->initialize(coll.fDrachmasTopMenu, "-");

    const auto s1 = new eWidget(window());
    s1->setWidth(mult*55);

    mPopulationWidget = new eTopWidget(window());
    mPopulationWidget->initialize(coll.fPopulationTopMenu, "-");

    const auto s2 = new eWidget(window());
    s2->setWidth(mult*25);

    mDateLabel = new eButton(window());
    mDateLabel->setPressAction([this]() {
        if(!mBoard) return;
        const auto dw = new eDateWidget(window());
        dw->initialize([this](const eDate& d) {
            mBoard->setDate(d);
            mDateLabel->setText(d.shortString());
        }, false);
        dw->setDate(mBoard->date());
        window()->execDialog(dw);
        dw->align(eAlignment::center);
    });
    const eDate date(30, eMonth::january, -1500);
    mDateLabel->setSmallFontSize();
    mDateLabel->setText(date.shortString());
    mDateLabel->fitContent();
    mDateLabel->setEnabled(false);

    const auto s3 = new eWidget(window());
    s3->setWidth(mult*20);

    addWidget(s0);
    addWidget(mDrachmasWidget);
    addWidget(s1);
    addWidget(mPopulationWidget);
    addWidget(s2);
    addWidget(mDateLabel);
    addWidget(s3);

    setHeight(12*mult);

    mDrachmasWidget->align(eAlignment::vcenter);
    mPopulationWidget->align(eAlignment::vcenter);
    mDateLabel->align(eAlignment::vcenter);

    layoutHorizontally();
}

void eTopBarWidget::setBoard(eGameBoard* const board) {
    mBoard = board;
}

void eTopBarWidget::paintEvent(ePainter& p) {
    // const bool update = (++mTime % 60) == 0;
    if(mBoard) {
        const auto& popData = mBoard->populationData();
        const int pop = popData.population();
        mPopulationWidget->setText(std::to_string(pop));

        const int d = mBoard->drachmas();
        mDrachmasWidget->setText(std::to_string(d));

        mDateLabel->setText(mBoard->date().shortString());
        mDateLabel->setEnabled(mBoard->editorMode());

        int iRes;
        int mult;
        iResAndMult(iRes, mult);
        const auto& intrfc = eGameTextures::interface()[iRes];
        const auto& tex = intrfc.fGameTopBar;
        const int texWidth = tex->width();
        const auto& rend = p.renderer();
        bool flip = false;
        for(int x = width() - texWidth; x > -texWidth; x -= texWidth) {
            tex->render(rend, x, 0, flip);
            flip = !flip;
        }
    } else {
        mDateLabel->setEnabled(false);
    }
}
