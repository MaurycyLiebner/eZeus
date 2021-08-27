#include "etopbarwidget.h"

#include "engine/egameboard.h"
#include "engine/boardData/epopulationdata.h"
#include "textures/egametextures.h"

void eTopBarWidget::initialize() {
    const auto& intrfc = eGameTextures::interface();
    int mult;
    int icoll;
    switch(resolution()) {
    case eRes::p480:
        mult = 1;
        icoll = 0;
        break;
    case eRes::p720:
    case eRes::p1080:
        mult = 2;
        icoll = 1;
        break;
    default:
        mult = 4;
        icoll = 2;
    }
    const auto& coll = intrfc[icoll];
    setPadding(0);

    mDrachmasWidget = new eTopWidget(window());
    mDrachmasWidget->initialize(coll.fDrachmasTopMenu, "-");

    const auto s = new eWidget(window());
    s->setWidth(mult*35);

    mPopulationWidget = new eTopWidget(window());
    mPopulationWidget->initialize(coll.fPopulationTopMenu, "-");

    const auto s2 = new eWidget(window());
    s2->setWidth(mult*15);

    addWidget(mDrachmasWidget);
    addWidget(s);
    addWidget(mPopulationWidget);
    addWidget(s2);

    setHeight(16*mult);
    setWidth(25*mult + mDrachmasWidget->width() + s->width() +
             mPopulationWidget->width() + s2->width());

    mDrachmasWidget->align(eAlignment::vcenter);
    mPopulationWidget->align(eAlignment::vcenter);

    layoutHorizontally();
}

void eTopBarWidget::setBoard(eGameBoard* const b) {
    mBoard = b;
}

void eTopBarWidget::paintEvent(ePainter& p) {
    const bool update = (++mTime % 60) == 0;
    if(update && mBoard) {
        const auto& popData = mBoard->populationData();
        const int pop = popData.population();
        mPopulationWidget->setText(std::to_string(pop));

        const int d =  mBoard->drachmas();
        mDrachmasWidget->setText(std::to_string(d));
    }
    eFramedWidget::paintEvent(p);
}
