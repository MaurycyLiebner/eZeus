#include "emythologydatawidget.h"

#include "eviewmodebutton.h"

#include "elanguage.h"
#include "widgets/elinewidget.h"
#include "engine/egameboard.h"
#include "widgets/ebuttonbase.h"
#include "evectorhelpers.h"

class eTitledWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize(const std::string& title) {
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
        const int w = width();
        mWidget->setWidth(w);
        addWidget(mWidget);

        stackVertically();
        fitHeight();
    }

    eWidget* widget() { return mWidget; }
private:
    eWidget* mWidget = nullptr;
};

class eMythologyButton : public eButtonBase {
public:
    using eButtonBase::eButtonBase;

    void initialize(const std::string& txt) {
        setYellowFontColor();
        setNoPadding();
        setTinyFontSize();
        setText(txt);
        fitContent();

        setMouseEnterAction([this]() {
            setLightFontColor();
        });
        setMouseLeaveAction([this]() {
            setYellowFontColor();
        });
    }
};

eWidget* createNoneLabel(eWidget* const parent,
                         eMainWindow* const w) {
    const auto none = new eMythologyButton(w);
    none->initialize(eLanguage::text("none"));
    parent->addWidget(none);
    none->align(eAlignment::hcenter);
    return none;
}

void eMythologyDataWidget::initialize() {
    {
        mSeeImmortals = new eViewModeButton(
                        eLanguage::text("see_immortals"),
                        eViewMode::immortals,
                        window());
        addViewButton(mSeeImmortals);
    }

    eDataWidget::initialize();

    const auto inner = innerWidget();
    const int innerW = inner->width();

    mSanctuaries = new eTitledWidget(window());
    mSanctuaries->setWidth(innerW);
    mSanctuaries->initialize(eLanguage::text("sanctuaries"));
    inner->addWidget(mSanctuaries);

    const auto saw = mSanctuaries->widget();
    createNoneLabel(saw, window());
    saw->stackVertically();
    saw->fitHeight();
    mSanctuaries->fitHeight();
    mSanctuaries->stackVertically();

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

    mGodsAttacking = new eTitledWidget(window());
    mGodsAttacking->setWidth(innerW);
    mGodsAttacking->initialize(eLanguage::text("gods_attacking"));
    inner->addWidget(mGodsAttacking);

    const auto gaw = mGodsAttacking->widget();
    createNoneLabel(gaw, window());
    gaw->stackVertically();
    gaw->fitHeight();
    mGodsAttacking->fitHeight();
    mGodsAttacking->stackVertically();

    mMonstersAttacking = new eTitledWidget(window());
    mMonstersAttacking->setWidth(innerW);
    mMonstersAttacking->initialize(eLanguage::text("monsters_attacking"));
    inner->addWidget(mMonstersAttacking);

    const auto maw = mMonstersAttacking->widget();
    createNoneLabel(maw, window());
    maw->stackVertically();
    maw->fitHeight();
    mMonstersAttacking->fitHeight();
    mMonstersAttacking->stackVertically();

    inner->stackVertically();
}

void eMythologyDataWidget::paintEvent(ePainter& p) {
    const bool update = ((mTime++) % 20) == 0;
    if(update) {
        {
            const auto ss = mBoard.sanctuaries();
            const bool changed = !eVectorHelpers::same(ss, mSanctuariesV);

            if(changed || mSanctuariesF) {
                mSanctuariesF = false;
                mSanctuariesV = ss;

                const auto w = mSanctuaries->widget();
                w->removeAllWidgets();

                for(const auto s : ss) {
                    const auto nameB = new eMythologyButton(window());
                    const auto gt = s->godType();
                    const auto name = eGod::sGodName(gt);
                    nameB->initialize(name);
                    w->addWidget(nameB);
                    nameB->align(eAlignment::hcenter);
                    const stdptr<eSanctuary> sptr(s);
                    nameB->setPressAction([this, sptr]() {
                        if(!sptr) return;
                        const auto g = sptr->god();
                        eTile* tile = nullptr;
                        if(g) {
                            tile = g->tile();
                        } else {
                            tile = sptr->centerTile();
                        }
                        if(!tile) return;
                        const auto gw = gameWidget();
                        gw->viewTile(tile);
                    });

                    const auto stateB = new eMythologyButton(window());
                    stateB->initialize(eLanguage::text("working"));
                    w->addWidget(stateB);
                    stateB->align(eAlignment::hcenter);
                    stateB->setPressAction([this, sptr]() {
                        if(!sptr) return;
                        const auto tile = sptr->centerTile();
                        if(!tile) return;
                        const auto gw = gameWidget();
                        gw->viewTile(tile);
                    });
                }

                if(ss.empty()) {
                    createNoneLabel(w, window());
                }

                w->stackVertically();
                w->fitHeight();
                mSanctuaries->stackVertically();
                mSanctuaries->fitHeight();
            }
        }

        {
            const auto ga = mBoard.attackingGods();
            const bool changed = !eVectorHelpers::same(ga, mGodsAttackingV);

            if(changed || mGodsAttackingF) {
                mGodsAttackingF = false;
                mGodsAttackingV = ga;

                const auto w = mGodsAttacking->widget();
                w->removeAllWidgets();

                for(const auto g : ga) {
                    const auto nameB = new eMythologyButton(window());
                    const auto ct = g->type();
                    const auto gt = eGod::sCharacterToGodType(ct);
                    const auto name = eGod::sGodName(gt);
                    nameB->initialize(name);
                    w->addWidget(nameB);
                    nameB->align(eAlignment::hcenter);
                    const stdptr<eCharacter> gptr(g);
                    nameB->setPressAction([this, gptr]() {
                        if(!gptr) return;
                        const auto tile = gptr->tile();
                        if(!tile) return;
                        const auto gw = gameWidget();
                        gw->viewTile(tile);
                    });
                }

                if(ga.empty()) {
                    createNoneLabel(w, window());
                }

                w->stackVertically();
                w->fitHeight();
                mGodsAttacking->stackVertically();
                mGodsAttacking->fitHeight();
            }
        }

        {
            const auto ma = mBoard.attackingMonsters();
            const bool changed = !eVectorHelpers::same(ma, mMonstersAttackingV);

            if(changed || mMonstersAttackingF) {
                mMonstersAttackingF = false;
                mMonstersAttackingV = ma;

                const auto w = mMonstersAttacking->widget();
                w->removeAllWidgets();

                for(const auto m : ma) {
                    const auto nameB = new eMythologyButton(window());
                    const auto ct = m->type();
                    const auto mt = eMonster::sCharacterToMonsterType(ct);
                    const auto name = eMonster::sMonsterName(mt);
                    nameB->initialize(name);
                    w->addWidget(nameB);
                    nameB->align(eAlignment::hcenter);
                    const stdptr<eCharacter> mptr(m);
                    nameB->setPressAction([this, mptr]() {
                        if(!mptr) return;
                        const auto tile = mptr->tile();
                        if(!tile) return;
                        const auto gw = gameWidget();
                        gw->viewTile(tile);
                    });
                }

                if(ma.empty()) {
                    createNoneLabel(w, window());
                }

                w->stackVertically();
                w->fitHeight();
                mMonstersAttacking->stackVertically();
                mMonstersAttacking->fitHeight();
            }
        }

        const auto inner = innerWidget();
        inner->stackVertically();
    }
    eWidget::paintEvent(p);
}
