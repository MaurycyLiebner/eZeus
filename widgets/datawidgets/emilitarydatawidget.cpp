#include "emilitarydatawidget.h"

#include "eviewmodebutton.h"

#include "engine/egameboard.h"
#include "elanguage.h"
#include "evectorhelpers.h"
#include "widgets/emicrobutton.h"
#include "widgets/ebasicbutton.h"
#include "widgets/emilitarymoreinfowidget.h"

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
    const bool changed = !eVectorHelpers::same(mBanners, ss);
    if(!changed) return;
    mBanners = ss;
    int iRes;
    int mult;
    iResAndMult(iRes, mult);
    const auto& intrfc = eGameTextures::interface();
    const auto& coll = intrfc[iRes];
    const auto& tops = coll.fInterfaceBannerTops;
    const auto& pTops = coll.fPoseidonInterfaceBannerTops;

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
            const auto sType = s->type();
            auto& board = s->getBoard();
            const bool p = board.poseidonMode();
            if(!p || sType == eBannerType::amazon ||
               sType == eBannerType::aresWarrior) {
                switch(sType) {
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
                default:
                    break;
                }

                const auto& top = tops.getTexture(topId);
                button->setTexture(top);
            } else {
                switch(sType) {
                case eBannerType::horseman:
                    topId = 0;
                    break;
                case eBannerType::rockThrower:
                    topId = 1;
                    break;
                case eBannerType::hoplite:
                    topId = 2;
                    break;
                default:
                    break;
                }

                const auto& top = pTops.getTexture(topId);
                button->setTexture(top);
            }
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
                        eLanguage::zeusText(14, 16),
                        eViewMode::security,
                        window());
        addViewButton(mSeeSecurity);
    }
    const auto res = resolution();
    const auto uiScale = res.uiScale();
    const int iRes = static_cast<int>(uiScale);
    const auto& intrfc = eGameTextures::interface()[iRes];

    eDataWidget::initialize();

    const auto inner = innerWidget();
    const int iw = inner->width();

    mForcesWidget = new eWidget(window());
    mForcesWidget->setNoPadding();
    mForcesWidget->setWidth(iw);

    mAbroad = new eForcesWidget(window());
    mAbroad->setWidth(iw);
    mAbroad->initialize(eLanguage::zeusText(51, 1)); // forces abroad
    mForcesWidget->addWidget(mAbroad);
    mAbroad->hide();

    mInCity = new eForcesWidget(window());
    mInCity->setWidth(iw);
    mInCity->initialize(eLanguage::zeusText(51, 0)); // forces in city
    mForcesWidget->addWidget(mInCity);
    mInCity->hide();

    mStandingDown = new eForcesWidget(window());
    mStandingDown->setWidth(iw);
    mStandingDown->initialize(eLanguage::zeusText(51, 2)); // standing down
    mForcesWidget->addWidget(mStandingDown);
    mStandingDown->hide();

    mForcesWidget->stackVertically();
    mForcesWidget->fitHeight();
    inner->addWidget(mForcesWidget);

    const auto buttonsW = new eWidget(window());
    buttonsW->setNoPadding();
    buttonsW->setWidth(iw);

    const double mult = res.multiplier();

    const int microW = std::round(84*mult);
    const auto microButtonsW = new eWidget(window());
    microButtonsW->setNoPadding();
    microButtonsW->setWidth(microW);
    mAtPalace = new eMicroButton(window());
    mAtPalace->setNoPadding();
    mAtPalace->setTinyFontSize();
    mAtPalace->setText(eLanguage::zeusText(51, 82));
    mAtPalace->setTooltip(eLanguage::zeusText(68, 37));
    mAtPalace->setWidth(microW);
    mAtPalace->fitHeight();
    microButtonsW->addWidget(mAtPalace);

    const int iconX = std::round(-10*mult);
    const auto soldiersIcon = new eLabel(window());
    soldiersIcon->setTexture(intrfc.fSoldiersIcon);
    soldiersIcon->fitContent();
    mAtPalace->addWidget(soldiersIcon);
    soldiersIcon->setX(iconX - soldiersIcon->width()/2);
    soldiersIcon->align(eAlignment::vcenter);

    mNoShips = new eMicroButton(window());
    mNoShips->setNoPadding();
    mNoShips->setTinyFontSize();
    mNoShips->setText(eLanguage::zeusText(51, 83));
    mNoShips->setTooltip(eLanguage::zeusText(68, 38));
    mNoShips->setWidth(microW);
    mNoShips->fitHeight();
    microButtonsW->addWidget(mNoShips);

    const auto shipsIcon = new eLabel(window());
    shipsIcon->setTexture(intrfc.fShipsIcon);
    shipsIcon->fitContent();
    mNoShips->addWidget(shipsIcon);
    shipsIcon->setX(iconX - shipsIcon->width()/2);
    shipsIcon->align(eAlignment::vcenter);

    mNoTowers = new eMicroButton(window());
    mNoTowers->setNoPadding();
    mNoTowers->setTinyFontSize();
    mNoTowers->setText(eLanguage::zeusText(51, 84));
    mNoTowers->setTooltip(eLanguage::zeusText(68, 39));
    mNoTowers->setWidth(microW);
    mNoTowers->fitHeight();
    microButtonsW->addWidget(mNoTowers);

    const auto towersIcon = new eLabel(window());
    towersIcon->setTexture(intrfc.fTowersIcon);
    towersIcon->fitContent();
    mNoTowers->addWidget(towersIcon);
    towersIcon->setX(iconX - towersIcon->width()/2);
    towersIcon->align(eAlignment::vcenter);

    const int microP = std::round(4*mult);
    microButtonsW->stackVertically(microP);
    microButtonsW->fitHeight();
    buttonsW->addWidget(microButtonsW);
    microButtonsW->setX(std::round(18*mult));

    const auto coll = &eInterfaceTextures::fMilitaryControlManual;
    const auto controlButton = new eBasicButton(coll, window());
    buttonsW->addWidget(controlButton);
    controlButton->setX(std::round(106*mult));

    buttonsW->fitHeight();
    inner->addWidget(buttonsW);
    buttonsW->align(eAlignment::bottom);

    showMoreInfoButton();
}

void eMilitaryDataWidget::paintEvent(ePainter& p) {
    const bool update = ((mTime++) % 20) == 0;
    if(update) {
        updateWidgets();
    }
    eWidget::paintEvent(p);
}

void eMilitaryDataWidget::openMoreInfoWiget() {
    const auto w = new eMilitaryMoreInfoWidget(window());
    w->initialize(mBoard);
    const auto gw = gameWidget();
    gw->openDialog(w);
}

void eMilitaryDataWidget::updateWidgets() {
    const auto& ss = mBoard.banners();
    using eSoldierBanners = std::vector<stdsptr<eSoldierBanner>>;
    eSoldierBanners abroad;
    eSoldierBanners inCity;
    eSoldierBanners standingDown;
    for(const auto& s : ss) {
        if(s->isAbroad()) {
            abroad.push_back(s);
        } else if(s->isHome()) {
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
    mAbroad->setBanners(abroad, act);
    if(abroad.empty()) {
        mAbroad->hide();
        mAbroad->setHeight(0);
    } else {
        mAbroad->show();
    }
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
    mForcesWidget->stackVertically();
    mForcesWidget->fitHeight();

    const auto towers = mBoard.buildings(eBuildingType::tower);

    if(inCity.empty() && standingDown.empty()) {
        mAtPalace->setText(eLanguage::zeusText(51, 82)); // no soldiers
        mAtPalace->setTooltip(eLanguage::zeusText(68, 37)); // no soldiers to command
        mAtPalace->setPressAction(nullptr);
    } else if(!inCity.empty()) {
        mAtPalace->setText(eLanguage::zeusText(51, 6)); // all called
        mAtPalace->setTooltip(eLanguage::zeusText(68, 170)); // click to send all soldiers home
        mAtPalace->setPressAction([this]() {
            mBoard.sendAllSoldiersHome();
            updateWidgets();
        });
    } else {
        mAtPalace->setText(eLanguage::zeusText(51, 8)); // at palace
        mAtPalace->setTooltip(eLanguage::zeusText(68, 171)); // click to muster all
        mAtPalace->setPressAction([this]() {
            mBoard.musterAllSoldiers();
            updateWidgets();
        });
    }
    if(towers.empty()) {
        mNoTowers->setText(eLanguage::zeusText(51, 84)); // no towers
        mNoTowers->setTooltip(eLanguage::zeusText(68, 39)); // no towers to man
        mNoTowers->setPressAction(nullptr);
    } else if(mBoard.manTowers()) {
        mNoTowers->setText(eLanguage::zeusText(51, 11)); // manning
        mNoTowers->setTooltip(eLanguage::zeusText(68, 174)); // click to send home
        mNoTowers->setPressAction([this]() {
            mBoard.setManTowers(false);
            updateWidgets();
        });
    } else {
        mNoTowers->setText(eLanguage::zeusText(51, 12)); // not manning
        mNoTowers->setTooltip(eLanguage::zeusText(68, 175)); // click to man
        mNoTowers->setPressAction([this]() {
            mBoard.setManTowers(true);
            updateWidgets();
        });
    }
}
