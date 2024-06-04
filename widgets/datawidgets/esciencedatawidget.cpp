#include "esciencedatawidget.h"

#include "eviewmodebutton.h"
#include "widgets/elinewidget.h"
#include "engine/egameboard.h"
#include "elanguage.h"
#include "buildings/emuseum.h"

class eTwoCloseLabels : public eWidget {
public:
    using eWidget::eWidget;

    void initialize(const std::string& title) {
        setNoPadding();
        const auto titleLabel = new eLabel(window());
        titleLabel->setNoPadding();
        titleLabel->setTinyFontSize();
        titleLabel->setText(title);
        titleLabel->fitContent();
        addWidget(titleLabel);

        mLabel = new eLabel(window());
        mLabel->setNoPadding();
        mLabel->setTinyFontSize();
        mLabel->setYellowFontColor();
        mLabel->setText(title);
        mLabel->fitContent();
        mLabel->setText("");
        addWidget(mLabel);

        mLabel->setY(0.9*titleLabel->height());

        fitContent();
    }

    eLabel* label() const { return mLabel; }
private:
    eLabel* mLabel = nullptr;
};

void eScienceDataWidget::initialize() {
    const auto seeAstronomers = new eViewModeButton(
                     eLanguage::zeusText(14, 20), // see astronomers
                     eViewMode::astronomers,
                     window());
    addViewButton(seeAstronomers);

    const auto seeScholars = new eViewModeButton(
                     eLanguage::zeusText(14, 23),
                     eViewMode::scholars,
                     window());
    addViewButton(seeScholars);

    const auto seeInventors = new eViewModeButton(
                     eLanguage::zeusText(14, 22),
                     eViewMode::inventors,
                     window());
    addViewButton(seeInventors);

    const auto seeCurators = new eViewModeButton(
                     eLanguage::zeusText(14, 21),
                     eViewMode::curators,
                     window());
    addViewButton(seeCurators);

    const auto seeAllScience = new eViewModeButton(
                     eLanguage::zeusText(14, 24),
                     eViewMode::allScience,
                     window());
    addViewButton(seeAllScience);

    eDataWidget::initialize();

    const auto iw = innerWidget();

    const auto cw = new eWidget(window());
    cw->setNoPadding();

    const auto title = new eLabel(window());
    title->setTinyFontSize();
    title->setNoPadding();
    title->setWrapWidth(0.8*iw->width());
    title->setWrapAlignment(eAlignment::hcenter);
    title->setText(eLanguage::zeusText(58, 75)); // Science in the city
    title->fitContent();
    title->setWidth(iw->width());
    cw->addWidget(title);

    const auto line = new eLineWidget(window());
    line->setNoPadding();
    line->fitContent();
    line->setWidth(title->width());
    cw->addWidget(line);

    const auto astronomy = new eTwoCloseLabels(window());
    astronomy->initialize(eLanguage::zeusText(58, 76));
    mAstronomyCoverage = astronomy->label();
    cw->addWidget(astronomy);

    const auto research = new eTwoCloseLabels(window());
    research->initialize(eLanguage::zeusText(58, 77));
    mResearchCoverage = research->label();
    cw->addWidget(research);

    const auto learning = new eTwoCloseLabels(window());
    learning->initialize(eLanguage::zeusText(58, 78));
    mLearningCoverage = learning->label();
    cw->addWidget(learning);

    const auto exhibits = new eTwoCloseLabels(window());
    exhibits->initialize(eLanguage::zeusText(58, 79));
    mExhibits = exhibits->label();
    cw->addWidget(exhibits);

    updateCoverage();

    cw->stackVertically();
    cw->fitContent();
    iw->addWidget(cw);
    cw->setX(spacing()/2);
}

void eScienceDataWidget::updateCoverage() {
    {
        const int pc = mBoard.philosophyResearchCoverage();
        const auto pt = sCoverageToText(pc);
        const auto ptt = eLanguage::zeusText(58, pt);
        mResearchCoverage->setText(ptt);
        mResearchCoverage->fitContent();
    }

    {
        const int ac = mBoard.athleticsLearningCoverage();
        const auto at = sCoverageToText(ac);
        const auto att = eLanguage::zeusText(58, at);
        mLearningCoverage->setText(att);
        mLearningCoverage->fitContent();
    }

    {
        const int dc = mBoard.dramaAstronomyCoverage();
        const auto dt = sCoverageToText(dc);
        const auto dtt = eLanguage::zeusText(58, dt);
        mAstronomyCoverage->setText(dtt);
        mAstronomyCoverage->fitContent();
    }

    {
        const auto m = mBoard.museum();
        const bool exhibits = m ? m->available() : false;
        const auto ddtt = eLanguage::zeusText(18, exhibits ? 1 : 0);
        mExhibits->setText(ddtt);
        mExhibits->fitContent();
    }
}

void eScienceDataWidget::paintEvent(ePainter& p) {
    const bool update = ((mTime++) % 20) == 0;
    if(update) {
        updateCoverage();
    }
    eWidget::paintEvent(p);
}
