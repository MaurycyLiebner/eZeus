#include "emilitarydatawidget.h"

#include "eviewmodebutton.h"

#include "engine/egameboard.h"
#include "elanguage.h"

void eForcesWidget::initialize(const std::string& title) {
    setNoPadding();
    const auto titleLabel = new eLabel(window());
    titleLabel->setTinyFontSize();
    titleLabel->setNoPadding();
    titleLabel->setText(title);
    titleLabel->fitContent();
    addWidget(titleLabel);
    titleLabel->align(eAlignment::hcenter);

    mWidget = new eWidget(window());
    mWidget->setNoPadding();
    addWidget(mWidget);

    stackVertically();
    fitHeight();
}

void eForcesWidget::setBanners(const eSoldierBanners& ss) {
    int iRes;
    int mult;
    iResAndMult(iRes, mult);
    const auto& intrfc = eGameTextures::interface();
    const auto& coll = intrfc[iRes];
    const auto& tops = coll.fInterfaceBannerTops;

    mWidget->removeChildren();
    eWidget* line = nullptr;
    int lineI = 0;
    const auto finishLine = [&]() {
        if(!line) return;
        line->stackHorizontally();
        line->fitContent();
        mWidget->addWidget(line);
        line = nullptr;
        lineI = 0;
    };
    for(const auto& s : ss) {
        if(!line) {
            line = new eWidget(window());
            line->setNoPadding();
        }
        const auto button = new eButtonBase(window());
        button->setNoPadding();

        {
            int topId = 0;
            switch(s->type()) {
            case eBannerType::horseman:
                topId = 0;
                break;
            case eBannerType::hoplite:
                topId = 1;
                break;
            case eBannerType::rockThrower:
                topId = 2;
                break;
            case eBannerType::amazon:
                topId = 4;
                break;
            case eBannerType::aresWarrior:
                topId = 5;
                break;
            }

            const auto& top = tops.getTexture(topId);
            button->setTexture(top);
        }
        button->fitContent();
        line->addWidget(button);
        lineI++;
        if(lineI >= 5) {
            finishLine();
        }
    }
    finishLine();
    mWidget->stackVertically();
    mWidget->fitContent();
    stackVertically();
    fitHeight();
}

void eMilitaryDataWidget::initialize() {
    {
        mSeeSecurity = new eViewModeButton(
                        eLanguage::text("see_security"),
                        eViewMode::husbandry,
                        window());
        addViewButton(mSeeSecurity);
    }

    eDataWidget::initialize();

    const auto inner = innerWidget();

    mInCity = new eForcesWidget(window());
    mInCity->setWidth(inner->width());
    mInCity->initialize(eLanguage::text("forces_in_city"));
    inner->addWidget(mInCity);
    mInCity->hide();

    mStandingDown = new eForcesWidget(window());
    mStandingDown->setWidth(inner->width());
    mStandingDown->initialize(eLanguage::text("standing_down"));
    inner->addWidget(mStandingDown);
    mStandingDown->hide();

    inner->stackVertically();
}

void eMilitaryDataWidget::paintEvent(ePainter& p) {
    const bool update = (++mTime % 20) == 0;
    if(update) {
        const auto inner = innerWidget();
        const auto& ss = mBoard.banners();
        using eSoldierBanners = std::vector<stdsptr<eSoldierBanner>>;
        eSoldierBanners inCity;
        eSoldierBanners standingDown;
        for(const auto& s : ss) {
            if(s->isHome()) {
                standingDown.push_back(s);
            } else {
                inCity.push_back(s);
            }
        }
        mInCity->setBanners(inCity);
        if(inCity.empty()) {
            mInCity->hide();
            mInCity->setHeight(0);
        }
        mStandingDown->setBanners(standingDown);
        if(standingDown.empty()) {
            mStandingDown->hide();
            mStandingDown->setHeight(0);
        }
        inner->stackVertically();
    }
    eWidget::paintEvent(p);
}
