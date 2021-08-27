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

    mDateLabel = new eLabel(window());
    const eDate date(30, eMonth::january, -1500);
    mDateLabel->setText(date.shortString());
    mDateLabel->fitContent();

    const auto s3 = new eWidget(window());
    s3->setWidth(mult*20);

    addWidget(s0);
    addWidget(mDrachmasWidget);
    addWidget(s1);
    addWidget(mPopulationWidget);
    addWidget(s2);
    addWidget(mDateLabel);
    addWidget(s3);

    setHeight(16*mult);
    setWidth(s0->width() +
             mDrachmasWidget->width() + s1->width() +
             mPopulationWidget->width() + s2->width() +
             mDateLabel->width() + s3->width());

    mDrachmasWidget->align(eAlignment::vcenter);
    mPopulationWidget->align(eAlignment::vcenter);
    mDateLabel->align(eAlignment::vcenter);

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

        mDateLabel->setText(mBoard->date().shortString());
    }
    eFramedWidget::paintEvent(p);
}
