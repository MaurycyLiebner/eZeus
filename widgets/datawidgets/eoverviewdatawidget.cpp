#include "eoverviewdatawidget.h"

#include "eviewmodebutton.h"

#include "widgets/egamewidget.h"
#include "widgets/eframedbutton.h"

#include "elanguage.h"
#include "engine/egameboard.h"
#include "estringhelpers.h"
#include "buildings/eheroshall.h"
#include "gameEvents/ereceiverequestevent.h"
#include "widgets/elinewidget.h"

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
                     eLanguage::text("see_problems"),
                     eViewMode::problems,
                     window());
    addViewButton(mSeeProblems);

    mSeeRoads = new eViewModeButton(
                     eLanguage::text("see_roads"),
                     eViewMode::roads,
                     window());
    addViewButton(mSeeRoads);

    eDataWidget::initialize();

    const auto inner = innerWidget();
    const int innerW = inner->width();

    mPopularity = new eOverviewEntry(window());
    mPopularity->setWidth(innerW);
    mPopularity->initialize(eLanguage::text("popularity"));
    inner->addWidget(mPopularity);

    mFoodLevel = new eOverviewEntry(window());
    mFoodLevel->setWidth(innerW);
    mFoodLevel->initialize(eLanguage::text("food_level"));
    inner->addWidget(mFoodLevel);

    mUnemployment = new eOverviewEntry(window());
    mUnemployment->setWidth(innerW);
    mUnemployment->initialize(eLanguage::text("unemployment"));
    inner->addWidget(mUnemployment);

    mHygiene = new eOverviewEntry(window());
    mHygiene->setWidth(innerW);
    mHygiene->initialize(eLanguage::text("hygiene"));
    inner->addWidget(mHygiene);

    mUnrest = new eOverviewEntry(window());
    mUnrest->setWidth(innerW);
    mUnrest->initialize(eLanguage::text("unrest"));
    inner->addWidget(mUnrest);

    mFinances = new eOverviewEntry(window());
    mFinances->setWidth(innerW);
    mFinances->initialize(eLanguage::text("finances"));
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
    requestsLabel->setText(eLanguage::text("requests"));
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
        const auto godIcon = eResourceTypeHelpers::icon(uiScale, resource);

        eRequestButton::initialize(godIcon, cityName, checker);
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

void eOverviewDataWidget::paintEvent(ePainter& p) {
    const bool update = ((mTime++) % 20) == 0;
    if(update) {
        {
            const int pop = mBoard.popularity();
            std::string txt;
            if(pop > 80) {
                txt = "great";
            } else if(pop > 60) {
                txt = "good";
            } else {
                txt = "bad";
            }
            mPopularity->setText(eLanguage::text(txt));
        }
        {
            const auto& husbData = mBoard.husbandryData();
            const int a = husbData.canSupport();
            const int pop = mBoard.population();
            std::string txt;
            if(pop == 0 || a < 0.75*pop) {
                txt = "too_low";
            } else {
                txt = "high";
            }
            mFoodLevel->setText(eLanguage::text(txt));
        }
        {
            const auto& emplData = mBoard.employmentData();
            const int w = emplData.employable();
            const int u = emplData.unemployed();
            if(u == 0) {
                mUnemployment->setTitle(eLanguage::text("employment"));
                mUnemployment->setText(eLanguage::text("good"));
            } else {
                mUnemployment->setTitle(eLanguage::text("unemployment"));
                int per = w == 0 ? 0 : std::round(100.*u/w);
                per = std::clamp(per, 0, 100);
                mUnemployment->setText(std::to_string(per) + "%");
            }
        }
        {
            const int hygiene = mBoard.health();
            std::string txt;
            if(hygiene > 90) {
                txt = "excellent";
            } else if(hygiene > 80) {
                txt = "very_good";
            } else if(hygiene > 70) {
                txt = "good";
            } else if(hygiene > 50) {
                txt = "ok";
            } else { // bad
                txt = "bad";
            }
            mHygiene->setText(eLanguage::text(txt));
        }
        {
            const int unrest = mBoard.unrest();
            std::string txt;
            if(unrest == 0) {
                txt = "none";
            } else if(unrest > 5) {
                txt = "high";
            }
            mUnrest->setText(eLanguage::text(txt));
        }
        {
            std::string txt;
            txt = "down";
            mFinances->setText(eLanguage::text(txt));
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
                const auto title = eLanguage::text("request");
                const auto text = eLanguage::text("dispatch_goods");
                gw->showQuestion(title, text, acceptA);
            } else {
                const auto tip = eLanguage::text("request_tip_not_enough");
                gw->showTip(tip);
            }
        });
        mQuestButtons->addWidget(b);
    }
}
