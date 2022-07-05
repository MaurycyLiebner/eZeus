#include "eculturedatawidget.h"

#include "eviewmodebutton.h"
#include "widgets/elinewidget.h"

#include "elanguage.h"

eCultureDataWidget::eCultureDataWidget(
        eGameBoard& board, eMainWindow* const window) :
    eDataWidget(window), mBoard(board) {}

eWidget* eCultureDataWidget::createCoverageWidget(
        const std::string& gamesName,
        const std::string& disciplineName,
        eLabel** const clabel) {
    const auto gamesNameStr = eLanguage::text(gamesName);
    const auto disciplineNameStr = eLanguage::text(disciplineName);

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
    covLabel->setText("Terrible");
    covLabel->fitContent();
    ccw->addWidget(covLabel);
    covLabel->setX(disciplineLabel->width() + p);

    ccw->fitContent();

    cw->addWidget(ccw);
    ccw->setY(gamesLabel->height());
    cw->fitContent();

    *clabel = covLabel;
    return cw;
}

void eCultureDataWidget::initialize() {
    mSeePhilosophers = new eViewModeButton(
                     eLanguage::text("see_philosophers"),
                     eViewMode::philosophers,
                     window());
    addViewButton(mSeePhilosophers);

    mSeeAthletes = new eViewModeButton(
                     eLanguage::text("see_athletes"),
                     eViewMode::athletes,
                     window());
    addViewButton(mSeeAthletes);

    mSeeActors = new eViewModeButton(
                     eLanguage::text("see_actors"),
                     eViewMode::actors,
                     window());
    addViewButton(mSeeActors);

    mSeeAllCulture = new eViewModeButton(
                     eLanguage::text("see_all_culture"),
                     eViewMode::allCulture,
                     window());
    addViewButton(mSeeAllCulture);

    eDataWidget::initialize();

    const auto iw = innerWidget();

    const auto cw = new eWidget(window());
    const int p = cw->padding()/2;
    cw->setNoPadding();

    const auto title = new eLabel(window());
    title->setTinyFontSize();
    title->setNoPadding();
    title->setWrapWidth(iw->width() - 2*p);
    title->setText(eLanguage::text("games_standing"));
    title->fitContent();
    cw->addWidget(title);

    const auto line = new eLineWidget(window());
    line->setNoPadding();
    line->fitContent();
    line->setWidth(title->width());
    cw->addWidget(line);

    const auto pwid = createCoverageWidget("isthmian_games",
                                           "philosophy_discipline",
                                           &mPhilosophyCoverage);
    cw->addWidget(pwid);

    const auto awid = createCoverageWidget("nemean_games",
                                           "athletics_discipline",
                                           &mAthleticsCoverage);
    cw->addWidget(awid);

    const auto dwid = createCoverageWidget("pythian_games",
                                           "drama_discipline",
                                           &mDramaCoverage);
    cw->addWidget(dwid);

    const auto allwid = createCoverageWidget("olympian_games",
                                             "all_discipline",
                                             &mAllCoverage);
    cw->addWidget(allwid);

    cw->stackVertically();
    cw->fitContent();
    iw->addWidget(cw);
    cw->move(p, p/2);

    updateCoverage();
}

std::string coverageToText(const int c) {
    if(c < 20) return "terrible_coverage";
    if(c < 40) return "poor_coverage";
    if(c < 60) return "not_bad_coverage";
    if(c < 80) return "ok_coverage";
    return "good_coverage";
}

void eCultureDataWidget::updateCoverage() {
    {
        const int pc = mBoard.philosophyCoverage();
        const auto pt = coverageToText(pc);
        const auto ptt = eLanguage::text(pt);
        mPhilosophyCoverage->setText(ptt);
        mPhilosophyCoverage->fitContent();
    }

    {
        const int ac = mBoard.athleticsCoverage();
        const auto at = coverageToText(ac);
        const auto att = eLanguage::text(at);
        mAthleticsCoverage->setText(att);
        mAthleticsCoverage->fitContent();
    }

    {
        const int dc = mBoard.dramaCoverage();
        const auto dt = coverageToText(dc);
        const auto dtt = eLanguage::text(dt);
        mDramaCoverage->setText(dtt);
        mDramaCoverage->fitContent();
    }

    {
        const int ddc = mBoard.dramaCoverage();
        const auto ddt = coverageToText(ddc);
        const auto ddtt = eLanguage::text(ddt);
        mAllCoverage->setText(ddtt);
        mAllCoverage->fitContent();
    }
}
