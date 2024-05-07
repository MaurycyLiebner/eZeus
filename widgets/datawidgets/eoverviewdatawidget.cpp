#include "eoverviewdatawidget.h"

#include "eviewmodebutton.h"

#include "widgets/egamewidget.h"
#include "widgets/eframedbutton.h"

#include "elanguage.h"
#include "engine/egameboard.h"
#include "estringhelpers.h"
#include "buildings/eheroshall.h"
#include "gameEvents/egodquestfulfilledevent.h"

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
    mQuestButtons = new eWidget(window());
    const int p = mQuestButtons->padding();
    mQuestButtons->setNoPadding();
    mQuestButtons->setWidth(inner->width() - 2*p);
    inner->addWidget(mQuestButtons);
    mQuestButtons->move(p, p);
    updateQuestButtons();
}

void eOverviewDataWidget::updateQuestButtons() {
    mQuestButtons->removeChildren();
    const auto& qs = mBoard.godQuests();
    int id = 1;
    for(const auto q : qs) {
        const auto idStr = std::to_string(id);
        auto bStr = eLanguage::text("quest_button");
        eStringHelpers::replace(bStr, "%1", idStr);
        const auto b = new eFramedButton(window());
        b->setRenderBg(true);
        b->setSmallFontSize();
        b->setText(bStr);
        b->setUnderline(false);
        b->fitContent();
        b->setPressAction([this, q]() {
            const auto& hhs = mBoard.heroHalls();
            eHerosHall* hh = nullptr;
            for(const auto hhh : hhs) {
                if(hhh->heroType() == q.fHero) {
                    hh = hhh;
                }
            }
            const auto heroName = eHero::sHeroName(q.fHero);
            const auto gw = gameWidget();
            if(hh) {
                const auto s = hh->stage();
                if(s == eHeroSummoningStage::arrived) {
                    const auto acceptA = [this, hh, gw, q]() {
                        hh->sendHeroOnQuest();
                        mBoard.removeGodQuest(q);
                        gw->updateGodQuestButtons();

                        const auto e = e::make_shared<eGodQuestFulfilledEvent>(mBoard);
                        const auto boardDate = mBoard.date();
                        const int period = 150;
                        const auto date = boardDate + period;
                        e->initializeDate(date, period, 1);
                        e->setGod(q.fGod);
                        e->setHero(q.fHero);
                        e->setId(q.fId);
                        mBoard.addGameEvent(e);
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
        b->align(eAlignment::hcenter);
        id++;
    }
    mQuestButtons->stackVertically();
    mQuestButtons->fitHeight();
}
