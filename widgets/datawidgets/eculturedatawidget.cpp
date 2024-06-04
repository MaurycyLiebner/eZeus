#include "eculturedatawidget.h"

#include "eviewmodebutton.h"
#include "widgets/elinewidget.h"
#include "engine/egameboard.h"

#include "elanguage.h"

eWidget* eCultureDataWidget::createCoverageWidget(
        const int gamesName,
        const int disciplineName,
        eLabel** const clabel) {
    const auto gamesNameStr = eLanguage::zeusText(58, gamesName);
    const auto disciplineNameStr = eLanguage::zeusText(58, disciplineName);

    const auto cw = new eWidget(window());
    cw->setNoPadding();

    const auto gamesLabel = new eLabel(window());
    gamesLabel->setNoPadding();
    gamesLabel->setTinyFontSize();
    gamesLabel->setText(gamesNameStr);
    gamesLabel->fitContent();
    cw->addWidget(gamesLabel);

    const auto ccw = new eWidget(window());
    ccw->setNoPadding();

    const auto disciplineLabel = new eLabel(window());
    disciplineLabel->setNoPadding();
    disciplineLabel->setTinyFontSize();
    disciplineLabel->setText(disciplineNameStr);
    disciplineLabel->fitContent();
    ccw->addWidget(disciplineLabel);

    const auto covLabel = new eLabel(window());
    const int p = covLabel->padding()/2;
    covLabel->setNoPadding();
    covLabel->setTinyFontSize();
    covLabel->setText(eLanguage::zeusText(58, 14)); // terrible
    covLabel->fitContent();
    ccw->addWidget(covLabel);
    covLabel->setX(disciplineLabel->width() + p);
    covLabel->setYellowFontColor();

    ccw->fitContent();

    cw->addWidget(ccw);
    ccw->setY(gamesLabel->height());
    cw->fitContent();

    *clabel = covLabel;
    return cw;
}

void eCultureDataWidget::initialize() {
    mSeePhilosophers = new eViewModeButton(
                     eLanguage::zeusText(14, 12), // see philosophers
                     eViewMode::philosophers,
                     window());
    addViewButton(mSeePhilosophers);

    mSeeAthletes = new eViewModeButton(
                     eLanguage::zeusText(14, 13),
                     eViewMode::athletes,
                     window());
    addViewButton(mSeeAthletes);

    mSeeActors = new eViewModeButton(
                     eLanguage::zeusText(14, 14),
                     eViewMode::actors,
                     window());
    addViewButton(mSeeActors);

    mSeeAllCulture = new eViewModeButton(
                     eLanguage::zeusText(14, 10),
                     eViewMode::allCulture,
                     window());
    addViewButton(mSeeAllCulture);

    eDataWidget::initialize();

    const auto iw = innerWidget();

    const auto cw = new eWidget(window());
    cw->setNoPadding();

    const auto title = new eLabel(window());
    title->setTinyFontSize();
    title->setNoPadding();
    title->setWrapWidth(iw->width());
    title->setText(eLanguage::zeusText(58, 1)); // Likely standing in Panhellenic Games
    title->fitContent();
    cw->addWidget(title);

    const auto line = new eLineWidget(window());
    line->setNoPadding();
    line->fitContent();
    line->setWidth(title->width());
    cw->addWidget(line);

    const auto pwid = createCoverageWidget(2, // isthmian games
                                           3, // philosophy
                                           &mPhilosophyCoverage);
    cw->addWidget(pwid);

    const auto awid = createCoverageWidget(4, // nemean games
                                           5, // athletics
                                           &mAthleticsCoverage);
    cw->addWidget(awid);

    const auto dwid = createCoverageWidget(6, // pythian games
                                           7, // drama
                                           &mDramaCoverage);
    cw->addWidget(dwid);

    const auto allwid = createCoverageWidget(8, // olympian games
                                             9, // all
                                             &mAllCoverage);
    cw->addWidget(allwid);

    cw->stackVertically();
    cw->fitContent();
    iw->addWidget(cw);
    cw->setX(spacing()/2);

    updateCoverage();
}

void eCultureDataWidget::updateCoverage() {
    {
        const int pc = mBoard.philosophyResearchCoverage();
        const auto pt = sCoverageToText(pc);
        const auto ptt = eLanguage::zeusText(58, pt);
        mPhilosophyCoverage->setText(ptt);
        mPhilosophyCoverage->fitContent();
    }

    {
        const int ac = mBoard.athleticsLearningCoverage();
        const auto at = sCoverageToText(ac);
        const auto att = eLanguage::zeusText(58, at);
        mAthleticsCoverage->setText(att);
        mAthleticsCoverage->fitContent();
    }

    {
        const int dc = mBoard.dramaAstronomyCoverage();
        const auto dt = sCoverageToText(dc);
        const auto dtt = eLanguage::zeusText(58, dt);
        mDramaCoverage->setText(dtt);
        mDramaCoverage->fitContent();
    }

    {
        const int ddc = mBoard.allCultureScienceCoverage();
        const auto ddt = sCoverageToText(ddc);
        const auto ddtt = eLanguage::zeusText(58, ddt);
        mAllCoverage->setText(ddtt);
        mAllCoverage->fitContent();
    }
}

void eCultureDataWidget::paintEvent(ePainter& p) {
    const bool update = ((mTime++) % 20) == 0;
    if(update) {
        updateCoverage();
    }
    eWidget::paintEvent(p);
}
