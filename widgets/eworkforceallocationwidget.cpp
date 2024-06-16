#include "eworkforceallocationwidget.h"

#include "widgets/esmallupbutton.h"
#include "widgets/esmalldownbutton.h"

#include "engine/eemploymentdistributor.h"
#include "engine/egameboard.h"
#include "elanguage.h"

eWorkforceAllocationWidget::eWorkforceAllocationWidget(
        eMainWindow* const window) :
    eInfoWidget(window, false, false) {}

void eWorkforceAllocationWidget::initialize(eGameBoard& board) {
    mBoard = &board;

    const auto title = eLanguage::zeusText(50, 0);
    eInfoWidget::initialize(title);

    const bool a = board.poseidonMode();
    auto& distributor = board.employmentDistributor();
    const auto distrPtr = &distributor;

    const auto allocationW = new eWidget(window());
    allocationW->setNoPadding();

    const auto res = resolution();
    const double mult = res.multiplier();

    const int c0w = std::round(150*mult);
    const int c1w = std::round(240*mult);
    const int c2w = std::round(60*mult);
    const int c3w = std::round(60*mult);

    const int iMin = static_cast<int>(eSector::husbandry);
    const int iMax = static_cast<int>(eSector::military);
    for(int i = iMin; i <= iMax; i++) {
        const auto s = static_cast<eSector>(i);

        int x = 0;

        const auto w = new eWidget(window());
        w->setNoPadding();

        const auto w0 = new eWidget(window());
        w0->setNoPadding();

        const auto name = eSectorHelpers::sName(s, a);

        const auto pL = new eLabel(window());

        const auto down = new eSmallDownButton(window());
        w0->addWidget(down);
        down->setPressAction([this, distrPtr, s, pL]() {
            auto p = distrPtr->priority(s);
            if(p == ePriority::noPriority) return;
            p = static_cast<ePriority>(static_cast<int>(p) - 1);
            distrPtr->setPriority(s, p);
            pL->setText(ePriorityHelpers::sName(p));
            pL->fitContent();
            updateLabels();
        });
        const auto up = new eSmallUpButton(window());
        w0->addWidget(up);
        up->setPressAction([this, distrPtr, s, pL]() {
            auto p = distrPtr->priority(s);
            if(p == ePriority::veryHigh) return;
            p = static_cast<ePriority>(static_cast<int>(p) + 1);
            distrPtr->setPriority(s, p);
            pL->setText(ePriorityHelpers::sName(p));
            pL->fitContent();
            updateLabels();
        });

        pL->setNoPadding();
        pL->setSmallFontSize();
        const auto prio = distributor.priority(s);
        pL->setText(ePriorityHelpers::sName(prio));
        pL->fitContent();
        w0->addWidget(pL);

        w0->stackHorizontally();
        w0->fitHeight();
        w0->setX(x);
        w0->setWidth(c0w);
        w->addWidget(w0);

        x += c0w;

        const auto w1 = new eWidget(window());
        w1->setNoPadding();

        const auto w1L = new eLabel(window());
        w1L->setNoPadding();
        w1L->setSmallFontSize();
        w1L->setText(name);
        w1L->fitContent();
        w1->addWidget(w1L);

        w1->fitHeight();
        w1->setX(x);
        w1->setWidth(c1w);
        w->addWidget(w1);

        x += c1w;

        const auto w2 = new eWidget(window());
        w2->setNoPadding();

        const auto w2L = new eLabel(window());
        w2L->setNoPadding();
        w2L->setSmallFontSize();
        const int maxE = distributor.maxEmployees(s);
        w2L->setText(std::to_string(maxE));
        w2L->fitContent();
        w2->addWidget(w2L);

        w2->fitHeight();
        w2->setX(x);
        w2->setWidth(c2w);
        w->addWidget(w2);

        x += c2w;

        const auto w3 = new eWidget(window());
        w3->setNoPadding();

        const auto w3L = new eLabel(window());
        w3L->setNoPadding();
        w3L->setSmallFontSize();
        const int e = distributor.employees(s);
        w3L->setText(std::to_string(e));
        if(e == maxE) {
            w3L->setLightFontColor();
        } else {
            w3L->setYellowFontColor();
        }
        w3L->fitContent();
        w3->addWidget(w3L);
        mEmplLabels[s] = w3L;

        w3->fitHeight();
        w3->setX(x);
        w3->setWidth(c3w);
        w->addWidget(w3);

        w->fitContent();

        allocationW->addWidget(w);
    }

    const auto colLabels = new eWidget(window());
    colLabels->setNoPadding();

    const auto priorityL = new eLabel(window());
    priorityL->setNoPadding();
    priorityL->setTinyFontSize();
    priorityL->setText(eLanguage::zeusText(50, 18));
    priorityL->fitContent();
    priorityL->setWidth(c0w);
    colLabels->addWidget(priorityL);

    const auto sectorL = new eLabel(window());
    sectorL->setNoPadding();
    sectorL->setTinyFontSize();
    sectorL->setText(eLanguage::zeusText(50, 19));
    sectorL->fitContent();
    sectorL->setWidth(c1w);
    colLabels->addWidget(sectorL);

    const auto needL = new eLabel(window());
    needL->setNoPadding();
    needL->setTinyFontSize();
    needL->setText(eLanguage::zeusText(50, 10));
    needL->fitContent();
    needL->setWidth(c2w);
    colLabels->addWidget(needL);

    const auto haveL = new eLabel(window());
    haveL->setNoPadding();
    haveL->setTinyFontSize();
    haveL->setText(eLanguage::zeusText(50, 11));
    haveL->fitContent();
    haveL->setWidth(c3w);
    colLabels->addWidget(haveL);

    const int p = res.largePadding();
    colLabels->stackHorizontally();
    colLabels->fitHeight();

    addInfoWidget(colLabels);

    allocationW->stackVertically();
    allocationW->fitHeight();

    const int totH = allocationW->height() + 2*p;
    const auto aw = addFramedWidget(totH);
    aw->addWidget(allocationW);
    allocationW->setWidth(aw->width());

    setCloseAction([this]() {
        deleteLater();
    });
}

void eWorkforceAllocationWidget::updateLabels() {
    auto& distributor = mBoard->employmentDistributor();

    const int iMin = static_cast<int>(eSector::husbandry);
    const int iMax = static_cast<int>(eSector::military);
    for(int i = iMin; i <= iMax; i++) {
        const auto s = static_cast<eSector>(i);
        const auto l = mEmplLabels[s];
        const int e = distributor.employees(s);
        const int maxE = distributor.maxEmployees(s);
        l->setText(std::to_string(e));
        l->fitContent();
        if(e == maxE) {
            l->setLightFontColor();
        } else {
            l->setYellowFontColor();
        }
    }
}
