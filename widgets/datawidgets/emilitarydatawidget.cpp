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

void eForcesWidget::setBanners(const eSoldierBanners& ss,
                               const eSoldierBannerAction& act) {
    if(mBanners.size() == ss.size()) {
        bool foundDifference = false;
        const int iMax = mBanners.size();
        for(int i = 0; i < iMax; i++) {
            if(mBanners[i] != ss[i]) {
                foundDifference = true;
                break;
            }
        }
        if(!foundDifference) return;
    }
    mBanners = ss;
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
        button->setTooltip(s->name());
        button->setPressAction([s, act]() {
            if(act) act(s);
        });

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
        const auto act = [this](const eSB& s) {
            if(!s->registered()) return;
            mBoard.clearBannerSelection();
            mBoard.selectBanner(s.get());
            const auto t = s->tile();
            const auto gw = gameWidget();
            gw->viewTile(t);
        };
        mInCity->setBanners(inCity, act);
        if(inCity.empty()) {
            mInCity->hide();
            mInCity->setHeight(0);
        } else {
            mInCity->show();
        }
        mStandingDown->setBanners(standingDown, act);
        if(standingDown.empty()) {
            mStandingDown->hide();
            mStandingDown->setHeight(0);
        } else {
            mStandingDown->show();
        }
        inner->stackVertically();
    }
    eWidget::paintEvent(p);
}
