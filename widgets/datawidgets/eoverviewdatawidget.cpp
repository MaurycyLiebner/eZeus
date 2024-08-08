#include "eoverviewdatawidget.h"

#include "eviewmodebutton.h"

#include "widgets/egamewidget.h"
#include "widgets/eframedbutton.h"

#include "elanguage.h"
#include "engine/egameboard.h"
#include "estringhelpers.h"
#include "buildings/eheroshall.h"
#include "gameEvents/ereceiverequestevent.h"
#include "gameEvents/etroopsrequestevent.h"
#include "widgets/elinewidget.h"
#include "widgets/eminimap.h"

class eOverviewEntry : public eWidget {
public:
    using eWidget::eWidget;

    void initialize(const std::string& title) {
        setNoPadding();
        mTitleLabel = new eLabel(window());
        mTitleLabel->setNoPadding();
        mTitleLabel->setTinyFontSize();
        mTitleLabel->setText(title);
        mTitleLabel->fitContent();
        addWidget(mTitleLabel);

        mValueLabel = new eLabel(window());
        mValueLabel->setYellowFontColor();
        mValueLabel->setNoPadding();
        mValueLabel->setTinyFontSize();
        addWidget(mValueLabel);

        fitHeight();
    }

    void setTitle(const std::string& title) {
        mTitleLabel->setText(title);
        mTitleLabel->fitContent();
    }

    void setText(const std::string& txt) {
        mValueLabel->setText(txt);
        mValueLabel->fitContent();
        mValueLabel->align(eAlignment::right);
    }
private:
    eLabel* mTitleLabel = nullptr;
    eLabel* mValueLabel = nullptr;
};

void eOverviewDataWidget::initialize() {
    mSeeProblems = new eViewModeButton(
                     eLanguage::zeusText(14, 18),
                     eViewMode::problems,
                     window());
    addViewButton(mSeeProblems);

    mSeeRoads = new eViewModeButton(
                     eLanguage::zeusText(14, 19),
                     eViewMode::roads,
                     window());
    addViewButton(mSeeRoads);

    eDataWidget::initialize();

    const auto inner = innerWidget();
    const int innerW = inner->width();

    mPopularity = new eOverviewEntry(window());
    mPopularity->setWidth(innerW);
    mPopularity->initialize(eLanguage::zeusText(61, 1)); // popularity
    inner->addWidget(mPopularity);

    mFoodLevel = new eOverviewEntry(window());
    mFoodLevel->setWidth(innerW);
    mFoodLevel->initialize(eLanguage::zeusText(61, 4)); // food level
    inner->addWidget(mFoodLevel);

    mUnemployment = new eOverviewEntry(window());
    mUnemployment->setWidth(innerW);
    mUnemployment->initialize(eLanguage::zeusText(61, 107)); // unemployment
    inner->addWidget(mUnemployment);

    mHygiene = new eOverviewEntry(window());
    mHygiene->setWidth(innerW);
    mHygiene->initialize(eLanguage::zeusText(61, 6)); // hygiene
    inner->addWidget(mHygiene);

    mUnrest = new eOverviewEntry(window());
    mUnrest->setWidth(innerW);
    mUnrest->initialize(eLanguage::zeusText(61, 7)); // unrest
    inner->addWidget(mUnrest);

    mFinances = new eOverviewEntry(window());
    mFinances->setWidth(innerW);
    mFinances->initialize(eLanguage::zeusText(61, 8)); // finances
    inner->addWidget(mFinances);

    const auto spacer1 = new eWidget(window());
    spacer1->setHeight(spacing());
    inner->addWidget(spacer1);

    const auto l1 = new eLineWidget(window());
    l1->setNoPadding();
    l1->fitContent();
    l1->setWidth(innerW);
    inner->addWidget(l1);

    const auto spacer2 = new eWidget(window());
    spacer2->setHeight(spacing());
    inner->addWidget(spacer2);

    const auto requestsLabel = new eLabel(window());
    requestsLabel->setTinyFontSize();
    requestsLabel->setNoPadding();
    requestsLabel->setText(eLanguage::zeusText(61, 195)); // requests
    requestsLabel->fitContent();
    inner->addWidget(requestsLabel);
    requestsLabel->align(eAlignment::hcenter);

    mQuestButtons = new eWidget(window());
    mQuestButtons->setNoPadding();
    mQuestButtons->setWidth(innerW);
    inner->addWidget(mQuestButtons);

    inner->stackVertically();

    updateRequestButtons();
}

void eOverviewDataWidget::shown() {
    eDataWidget::show();
    if(mMap) mMap->scheduleUpdate();
}

stdsptr<eTexture> sGodIcon(const eUIScale scale,
                           const eGodType god) {
    const auto& intrfc = eGameTextures::interface();
    const int iRes = static_cast<int>(scale);
    const auto& coll = intrfc[iRes];
    switch(god) {
    case eGodType::zeus:
        return coll.fZeusQuestIcon;
    case eGodType::poseidon:
        return coll.fPoseidonQuestIcon;
    case eGodType::demeter:
        return coll.fDemeterQuestIcon;
    case eGodType::apollo:
        return coll.fApolloQuestIcon;
    case eGodType::artemis:
        return coll.fArtemisQuestIcon;
    case eGodType::ares:
        return coll.fAresQuestIcon;
    case eGodType::aphrodite:
        return coll.fAphroditeQuestIcon;
    case eGodType::hermes:
        return coll.fHermesQuestIcon;
    case eGodType::athena:
        return coll.fAthenaQuestIcon;
    case eGodType::hephaestus:
        return coll.fHephaestusQuestIcon;
    case eGodType::dionysus:
        return coll.fDionysusQuestIcon;
    case eGodType::hades:
        return coll.fHadesQuestIcon;

    case eGodType::hera:
        return coll.fHeraQuestIcon;
    case eGodType::atlas:
        return coll.fAtlasQuestIcon;
    }
    return nullptr;
}

class eRequestButton : public eButtonBase {
protected:
    using eButtonBase::eButtonBase;

    using eViableChecker = std::function<bool()>;
    void initialize(const stdsptr<eTexture>& icon,
                    const std::string& txt,
                    const eViableChecker& checker) {
        setNoPadding();

        mViableChecker = checker;

        mStateLabel = new eLabel(window());
        mStateLabel->setNoPadding();
        addWidget(mStateLabel);
        setViable(false);
        mStateLabel->fitContent();

        const auto iconLabel = new eLabel(window());
        iconLabel->setNoPadding();
        iconLabel->setTexture(icon);
        iconLabel->fitContent();
        addWidget(iconLabel);

        const auto textLabel = new eLabel(window());
        textLabel->setTinyFontSize();
        textLabel->setNoPadding();
        textLabel->setText(txt);
        textLabel->fitContent();
        addWidget(textLabel);

        setMouseEnterAction([textLabel]() {
            textLabel->setYellowFontColor();
        });
        setMouseLeaveAction([textLabel]() {
            textLabel->setLightFontColor();
        });

        stackHorizontally();
        fitHeight();
        mStateLabel->align(eAlignment::vcenter);
        iconLabel->align(eAlignment::vcenter);
        textLabel->align(eAlignment::vcenter);
    }
protected:
    void paintEvent(ePainter& p) override {
        if(mViableChecker) {
            const bool v = mViableChecker();
            setViable(v);
        }
        eButtonBase::paintEvent(p);
    }
private:
    void setViable(const bool f) {
        const auto res = resolution();
        const auto scale = res.uiScale();
        const int iRes = static_cast<int>(scale);
        const auto& intrfc = eGameTextures::interface();
        const auto& texs = intrfc[iRes];
        const auto& coll = f ? texs.fRequestFulfilledBox :
                               texs.fRequestWaitingBox;
        const auto tex = coll.getTexture(0);
        mStateLabel->setTexture(tex);
    }

    eViableChecker mViableChecker;
    eLabel* mStateLabel = nullptr;
};

class eResourceRequestButton : public eRequestButton {
public:
    using eRequestButton::eRequestButton;

    void initialize(const eResourceType resource,
                    const stdsptr<eWorldCity>& city,
                    const eViableChecker& checker) {
        const auto cityName = city->name();
        const auto res = resolution();
        const auto uiScale = res.uiScale();
        const auto resIcon = eResourceTypeHelpers::icon(uiScale, resource);

        eRequestButton::initialize(resIcon, cityName, checker);
    }
};

class eTroopsRequestButton : public eRequestButton {
public:
    using eRequestButton::eRequestButton;

    void initialize(const stdsptr<eWorldCity>& city,
                    const eViableChecker& checker) {
        const auto cityName = city->name();
        const auto res = resolution();
        const auto uiScale = res.uiScale();
        const int iRes = static_cast<int>(uiScale);
        const auto& intrfc = eGameTextures::interface();
        const auto& texs = intrfc[iRes];
        const auto& troopsIcon = texs.fTroopsRequestIcon;
        eRequestButton::initialize(troopsIcon, cityName, checker);
    }
};

class eGodQuestButton : public eRequestButton {
public:
    using eRequestButton::eRequestButton;

    void initialize(const eGodType god,
                    const eViableChecker& checker) {
        const auto godName = eGod::sGodName(god);
        const auto res = resolution();
        const auto uiScale = res.uiScale();
        const auto godIcon = sGodIcon(uiScale, god);

        eRequestButton::initialize(godIcon, godName, checker);
    }
};

void eOverviewDataWidget::updateRequestButtons() {
    mQuestButtons->removeChildren();
    addGodQuests();
    addCityRequests();
    mQuestButtons->stackVertically();
    mQuestButtons->fitHeight();
}

void eOverviewDataWidget::setMap(eMiniMap* const map) {
    mMap = map;
}

void eOverviewDataWidget::paintEvent(ePainter& p) {
    const bool update = ((mTime++) % 20) == 0;
    if(update) {
        {
            const int pop = mBoard.popularity();
            int string = -1;
            if(pop > 90) {
                string = 38; // superb
            } else if(pop > 85) {
                string = 37; // great
            } else if(pop > 80) {
                string = 36; // high
            } else if(pop > 75) {
                string = 34; // good
            } else if(pop > 70) {
                string = 33; // ok
            } else if(pop > 60) {
                string = 32; // poor
            } else if(pop > 50) {
                string = 31; // bad
            } else if(pop > 40) {
                string = 28; // awful
            }else {
                string = 27; // terrible
            }
            mPopularity->setText(eLanguage::zeusText(61, string));
        }
        {
            const auto& husbData = mBoard.husbandryData();
            const int a = husbData.canSupport();
            const int pop = mBoard.population();
            int string = -1;
            if(pop == 0 || a < 0.75*pop) {
                string = 94; // too low
            } else if(a < 0.85*pop) {
                string = 95; // low
            } else {
                string = 97; // good
            }
            mFoodLevel->setText(eLanguage::zeusText(61, string));
        }
        {
            const auto& emplData = mBoard.employmentData();
            const int f = emplData.freeJobVacancies();
            const int w = emplData.employable();
            const int u = emplData.unemployed();
            if(u == 0) {
                mUnemployment->setTitle(eLanguage::zeusText(61, 115)); // employment good
                mUnemployment->setText("");
            } else if(f > 0) {
                mUnemployment->setTitle(eLanguage::zeusText(61, 111)); // workers needed
                mUnemployment->setText(std::to_string(f));
            } else {
                mUnemployment->setTitle(eLanguage::zeusText(61, 107)); // unemployment
                int per = w == 0 ? 0 : std::round(100.*u/w);
                per = std::clamp(per, 0, 100);
                mUnemployment->setText(std::to_string(per) + "%");
            }
        }
        {
            const int hygiene = mBoard.health();
            int string = -1;
            if(hygiene > 90) {
                string = 137; // perfect
            } else if(hygiene > 85) {
                string = 136; // great
            } else if(hygiene > 80) {
                string = 135; // excellent
            } else if(hygiene > 75) {
                string = 134; // very good
            } else if(hygiene > 70) {
                string = 133; // good
            } else if(hygiene > 65) {
                string = 132; // ok
            } else if(hygiene > 60) {
                string = 131; // not good
            } else if(hygiene > 55) {
                string = 130; // poort
            } else if(hygiene > 50) {
                string = 129; // bad
            } else if(hygiene > 45) {
                string = 128; // terrible
            } else {
                string = 127; // appalling
            }
            mHygiene->setText(eLanguage::zeusText(61, string));
        }
        {
            const int unrest = mBoard.unrest();
            int string = -1;
            if(unrest == 0) {
                string = 149; // none
            } else if(unrest > 10) {
                string = 144; // severe
            } else if(unrest > 5) {
                string = 146; // high
            } else {
                string = 148; // low
            }
            mUnrest->setText(eLanguage::zeusText(61, string));
        }
        {
            int string = -1;
            string = 153; // up
            string = 154; // ok
            string = 155; // down
            mFinances->setText(eLanguage::zeusText(61, string));
        }
    }
    eWidget::paintEvent(p);
}

bool sHeroReady(eGameBoard& board, const eHeroType hero) {
    const auto hh = board.heroHall(hero);
    if(!hh) return false;
    const auto s = hh->stage();
    return s == eHeroSummoningStage::arrived;
}

void eOverviewDataWidget::addGodQuests() {
    const auto& qs = mBoard.godQuests();
    for(const auto qq : qs) {
        const auto q = qq->godQuest();
        const auto god = q.fGod;
        const auto b = new eGodQuestButton(window());
        b->setWidth(mQuestButtons->width());
        b->initialize(god, [this, q]() {
            return sHeroReady(mBoard, q.fHero);
        });
        b->setPressAction([this, q, qq]() {
            const auto hh = mBoard.heroHall(q.fHero);
            const auto heroName = eHero::sHeroName(q.fHero);
            const auto gw = gameWidget();
            if(hh) {
                const auto s = hh->stage();
                if(s == eHeroSummoningStage::arrived) {
                    const auto acceptA = [qq]() {
                        qq->fulfill();
                    };
                    const auto title = eLanguage::text("quest_question_title");
                    auto text = eLanguage::text("quest_question");
                    eStringHelpers::replace(text, "%1", heroName);
                    gw->showQuestion(title, text, acceptA);
                } else {
                    auto tip = eLanguage::text("quest_tip_summon_hero");
                    eStringHelpers::replace(tip, "%1", heroName);
                    gw->showTip(tip);
                }
            } else {
                auto tip = eLanguage::text("quest_tip_build_hh");
                eStringHelpers::replace(tip, "%1", heroName);
                gw->showTip(tip);
            }
        });
        mQuestButtons->addWidget(b);
    }
}

void eOverviewDataWidget::addCityRequests() {
    const auto& qs = mBoard.cityRequests();
    for(const auto& qq : qs) {
        const auto q = qq->cityRequest();
        const auto b = new eResourceRequestButton(window());
        b->setWidth(mQuestButtons->width());
        b->initialize(q.fType, q.fCity, [this, q]() {
            const auto count = mBoard.resourceCount(q.fType);
            return count >= q.fCount;
        });
        b->setPressAction([this, q, qq]() {
            const auto gw = gameWidget();
            const auto count = mBoard.resourceCount(q.fType);
            if(count >= q.fCount) {
                const auto acceptA = [qq]() {
                    qq->dispatch();
                };
                const auto title = eLanguage::zeusText(5, 6); // Request
                const auto text = eLanguage::zeusText(5, 7); // Dispatch goods?
                gw->showQuestion(title, text, acceptA);
            } else {
                const auto tip = eLanguage::zeusText(5, 9); // You do not have enough to fulfill the request
                gw->showTip(tip);
            }
        });
        mQuestButtons->addWidget(b);
    }
    const auto& qqs = mBoard.cityTroopsRequests();
    for(const auto& qq : qqs) {
        const auto b = new eTroopsRequestButton(window());
        b->setWidth(mQuestButtons->width());
        b->initialize(qq->city(), [this]() {
            const auto& bs = mBoard.banners();
            for(const auto& b : bs) {
                const bool a = b->isAbroad();
                if(!a) return true;
            }
            const auto& hs = mBoard.heroHalls();
            for(const auto h : hs) {
                const bool a = h->heroOnQuest();
                if(!a) return true;
            }
            return false;
        });
        b->setPressAction([qq]() {
            qq->dispatch();
        });
        mQuestButtons->addWidget(b);
    }
}
