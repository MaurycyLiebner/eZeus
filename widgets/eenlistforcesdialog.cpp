#include "eenlistforcesdialog.h"

#include "eframedbutton.h"
#include "elanguage.h"
#include "evectorhelpers.h"
#include "escrollwidget.h"
#include "econtextmenu.h"
#include "emainwindow.h"
#include "echoosebutton.h"

enum class eEnlistType {
    horseman, hoplite, navy,
    hero,
    amazon, aresWarrior,
    ally
};

class eEnlistButton : public eButtonBase {
public:
    using eButtonBase::eButtonBase;

    void initialize(const bool abroad,
                    const eEnlistType type,
                    const int id,
                    const std::string& title,
                    const int troops,
                    const eAction& pressAction) {
        mAbroad = abroad;
        mType = type;
        setNoPadding();
        if(!abroad) {
            setPressAction([this, pressAction]() {
                const bool s = mSelected;
                if(pressAction) pressAction();
                setSelected(!s);
            });
        }

        int iRes;
        int mult;
        iResAndMult(iRes, mult);
        const auto& intrfc = eGameTextures::interface();
        const auto& coll = intrfc[iRes];

        if(type == eEnlistType::horseman ||
           type == eEnlistType::hoplite) {
            const auto& bnrs = coll.fInterfaceBanners;
            const auto& bnr = bnrs.getTexture(id % bnrs.size());
            const auto bnrl = new eLabel(window());
            bnrl->setTexture(bnr);
            bnrl->setNoPadding();
            bnrl->fitContent();
            addWidget(bnrl);
        }
        {
            const auto& tops = coll.fInterfaceBannerTops;
            bool valid = false;
            int topId = 0;
            switch(type) {
            case eEnlistType::horseman:
                topId = 0;
                valid = true;
                break;
            case eEnlistType::hoplite:
                topId = 1;
                valid = true;
                break;
            case eEnlistType::amazon:
                topId = 4;
                valid = true;
                break;
            case eEnlistType::aresWarrior:
                topId = 5;
                valid = true;
                break;
            default:
                topId = 0;
                valid = false;
                break;
            }

            const auto& top = tops.getTexture(topId);
            const auto bnrl = new eLabel(window());
            bnrl->setTexture(top);
            bnrl->setNoPadding();
            bnrl->fitContent();
            addWidget(bnrl);
            bnrl->setVisible(valid);
        }
        const auto titlel = new eLabel(window());
        titlel->setTinyFontSize();
        titlel->setNoPadding();
        titlel->setText(title);
        titlel->fitContent();
        addWidget(titlel);
        mLabels.push_back(titlel);

        fitHeight();
        stackHorizontally();

        if(troops != -1) {
            const auto troopsl = new eLabel(window());
            troopsl->setTinyFontSize();
            troopsl->setNoPadding();
            const auto troopsStr = std::to_string(troops);
            troopsl->setText(troopsStr);
            troopsl->fitContent();
            addWidget(troopsl);
            const int x = 2*width()/3 + 4*mult - troopsl->width()/2;
            troopsl->setX(x);

            mLabels.push_back(troopsl);
        }

        mEnlistedLabel = new eLabel(window());
        mEnlistedLabel->setYellowFontColor();
        mEnlistedLabel->setNoPadding();
        mEnlistedLabel->setTinyFontSize();
        if(abroad) {
            const auto etxt = eLanguage::text("abroad");
            mEnlistedLabel->setText(etxt);
        } else {
            const auto etxt = eLanguage::text("enlisted");
            mEnlistedLabel->setText(etxt);
        }
        mEnlistedLabel->fitContent();
        addWidget(mEnlistedLabel);
        mEnlistedLabel->setX(width() - mEnlistedLabel->width() - mult*5);

        setSelected(abroad);
    }

    eEnlistType type() const { return mType; }

    void setSelected(const bool b) {
        mSelected = b;
        for(const auto l : mLabels) {
            if(b) l->setYellowFontColor();
            else l->setLightFontColor();
        }
        mEnlistedLabel->setVisible(b);
    }

    bool selected() const { return mSelected; }
    bool abroad() const { return mAbroad; }
protected:
    void paintEvent(ePainter& p) {
        if(!mAbroad && hovered()) {
            p.drawRect(rect(), {0, 0, 0, 255}, 1);
        }
        eButtonBase::paintEvent(p);
    }
private:
    bool mAbroad = false;
    bool mSelected = false;
    eEnlistType mType;

    std::vector<eLabel*> mLabels;
    eLabel* mEnlistedLabel = nullptr;
};

class eEnlistArea : public eWidget {
public:
    using eWidget::eWidget;

    struct eEnlistData {
        bool fAbroad;
        eEnlistType fType;
        int fId;
        std::string fTitle;
        int fTroops;
        eAction fAction;
    };

    void initialize(const eEnlistedForces& e,
                    const std::vector<bool>& heroesAbroad,
                    const eAction& selectionChanged) {
        std::vector<eEnlistData> data;
        for(const auto& s : e.fSoldiers) {
            auto& d = data.emplace_back();
            switch(s->type()) {
            case eBannerType::hoplite:
                d.fType = eEnlistType::hoplite;
                break;
            case eBannerType::horseman:
                d.fType = eEnlistType::horseman;
                break;
            case eBannerType::amazon:
                d.fType = eEnlistType::amazon;
                break;
            case eBannerType::aresWarrior:
                d.fType = eEnlistType::aresWarrior;
                break;
            default:
                continue;
                break;
            }
            d.fAbroad = s->isAbroad();
            d.fTitle = s->name();
            d.fId = s->id();
            d.fTroops = s->count();
            d.fAction = [this, s, selectionChanged]() {
                const bool selected = eVectorHelpers::contains(
                                          mSelected.fSoldiers, s);
                if(selected) {
                    eVectorHelpers::remove(mSelected.fSoldiers, s);
                } else {
                    mSelected.fSoldiers.push_back(s);
                }
                selectionChanged();
            };
        }

        const int iMax = e.fHeroes.size();
        for(int i = 0; i < iMax; i++) {
            const auto h = e.fHeroes[i];
            auto& d = data.emplace_back();
            d.fAbroad = heroesAbroad[i];
            d.fType = eEnlistType::hero;
            d.fTitle = eHero::sHeroName(h);
            d.fId = static_cast<int>(h);
            d.fTroops = -1;
            d.fAction = [this, h, selectionChanged]() {
                const bool selected = eVectorHelpers::contains(
                                          mSelected.fHeroes, h);
                if(selected) {
                    eVectorHelpers::remove(mSelected.fHeroes, h);
                } else {
                    mSelected.fHeroes.push_back(h);
                }
                selectionChanged();
            };
        }

        for(const auto& a : e.fAllies) {
            auto& d = data.emplace_back();
            d.fAbroad = a->abroad();
            d.fType = eEnlistType::ally;
            d.fTitle = a->name();
            d.fId = -1;
            d.fTroops = -1;
            d.fAction = [this, a, selectionChanged]() {
                const bool selected = eVectorHelpers::contains(
                                          mSelected.fAllies, a);
                if(selected) {
                    eVectorHelpers::remove(mSelected.fAllies, a);
                } else {
                    clearCities();
                    mSelected.fAllies.push_back(a);
                }
                selectionChanged();
            };
        }

        for(const auto& d : data) {
            const auto b = new eEnlistButton(window());
            b->setWidth(width());
            b->initialize(d.fAbroad, d.fType, d.fId,
                          d.fTitle, d.fTroops, d.fAction);
            addWidget(b);
            mButtons.push_back(b);
        }
        stackVertically();
    }

    void clearCities() {
        mSelected.fAllies.clear();
        for(const auto b : mButtons) {
            const auto t = b->type();
            if(t != eEnlistType::ally) continue;
            const bool abroad = b->abroad();
            if(!abroad) b->setSelected(false);
        }
    }

    void clearAll() {
        mSelected.clear();
        for(const auto b : mButtons) {
            const bool abroad = b->abroad();
            if(!abroad) b->setSelected(false);
        }
    }

    void selectAll() {
        mSelected = mAll;
        auto& allies = mSelected.fAllies;
        if(!allies.empty()) {
            allies.clear();
            for(const auto& a : mAll.fAllies) {
                const bool abroad = a->abroad();
                if(abroad) continue;
                allies.push_back(a);
                break;
            }
        }
        bool citySelected = false;
        for(const auto b : mButtons) {
            const auto t = b->type();
            const bool isAlly = t == eEnlistType::ally;
            const bool isAbroad = b->abroad();
            if(isAlly && !isAbroad) {
                if(citySelected) {
                    b->setSelected(false);
                    continue;
                }
                citySelected = true;
            }

            b->setSelected(true);
        }
    }

    const eEnlistedForces& selected() const {
        return mSelected;
    }
private:
    eEnlistedForces mAll;
    eEnlistedForces mSelected;
    std::vector<eEnlistButton*> mButtons;
};

class eEnlistWidget : public eFramedWidget {
public:
    using eFramedWidget::eFramedWidget;

    void initialize(const eEnlistedForces& e,
                    const std::vector<bool>& heroesAbroad,
                    const eAction& selectionChanged,
                    const std::string& title,
                    const bool troops) {
        const auto r = resolution();

        setType(eFrameType::inner);
        const int w = width();
        const int h = height();

        const auto innerWid = new eWidget(window());
        addWidget(innerWid);
        const int p = r.tinyPadding();
        innerWid->setNoPadding();
        innerWid->move(p, p);
        innerWid->resize(w - 2*p, h - 2*p);

        const auto titleLabel = new eLabel(title, window());
        titleLabel->setTinyFontSize();
        titleLabel->setNoPadding();
        titleLabel->fitContent();
        innerWid->addWidget(titleLabel);
        titleLabel->align(eAlignment::top | eAlignment::left);

        if(troops) {
            const auto text = eLanguage::text("troops");
            const auto troopsLabel = new eLabel(text, window());
            troopsLabel->setTinyFontSize();
            troopsLabel->setNoPadding();
            troopsLabel->fitContent();
            innerWid->addWidget(troopsLabel);
            troopsLabel->align(eAlignment::top | eAlignment::right);
            troopsLabel->setX(11*width()/18);
        }

        mArea = new eEnlistArea(window());

        const int ww = innerWid->width();
        const int hh = innerWid->height() - titleLabel->height();
        mArea->resize(ww, hh);
        mArea->initialize(e, heroesAbroad, selectionChanged);
        mArea->fitHeight();
        const auto scrollW = new eScrollWidget(window());
        scrollW->setScrollArea(mArea);
        scrollW->resize(ww, hh);
        innerWid->addWidget(scrollW);
        scrollW->align(eAlignment::bottom | eAlignment::hcenter);
    }

    void clearAll() {
        mArea->clearAll();
    }

    void selectAll() {
        mArea->selectAll();
    }

    eEnlistedForces selected() const {
        return mArea->selected();
    }
private:
    eEnlistArea* mArea = nullptr;
};

eEnlistedForces extractType(const eBannerType type,
                            const eEnlistedForces& from) {
    eEnlistedForces result;
    for(const auto& s : from.fSoldiers) {
        const auto t = s->type();
        if(t == type) {
            result.fSoldiers.push_back(s);
        }
    }
    return result;
}

void eEnlistForcesDialog::initialize(
        const eEnlistedForces& enlistable,
        const std::vector<bool>& heroesAbroad,
        const eEnlistAction& action,
        const std::vector<eResourceType>& plunderResources) {
    const auto r = resolution();

    setType(eFrameType::message);
    const int w = r.centralWidgetLargeWidth();
    const int h = r.centralWidgetLargeHeight();
    resize(w, h);
    align(eAlignment::center);

    const auto innerWid = new eWidget(window());
    addWidget(innerWid);
    const int p = r.hugePadding();
    innerWid->setNoPadding();
    innerWid->move(p, p);
    const int ww = w - 2*p;
    const int hh = h - 2*p;
    innerWid->resize(ww, hh);

    const int pp = r.tinyPadding();

    int hhh = hh;

    {
        const auto titleW = new eWidget(window());
        titleW->setNoPadding();
        titleW->setWidth(innerWid->width());
        innerWid->addWidget(titleW);

        {
            const auto text = eLanguage::text("enlist_forces");
            const auto titleLabel = new eLabel(window());
            titleLabel->setTinyPadding();
            titleLabel->setText(text);
            titleLabel->fitContent();
            titleW->addWidget(titleLabel);
            if(plunderResources.empty()) {
                titleLabel->align(eAlignment::top | eAlignment::hcenter);
            } else {
                titleLabel->align(eAlignment::top | eAlignment::left);
            }
        }

        if(!plunderResources.empty()) {
            const auto plunderW = new eWidget(window());
            plunderW->setNoPadding();
            titleW->addWidget(plunderW);

            const auto text = eLanguage::text("select_plunder");
            const auto titleLabel = new eLabel(window());
            titleLabel->setSmallFontSize();
            titleLabel->setSmallPadding();
            titleLabel->setText(text);
            titleLabel->fitContent();
            plunderW->addWidget(titleLabel);

            const auto button = new eFramedButton(window());
            button->setUnderline(false);
            button->setSmallPadding();
            button->setSmallFontSize();
            button->setText(eLanguage::text("any_resource_plunder"));
            button->fitContent();
            button->setWidth(titleLabel->width());
            plunderW->addWidget(button);

            button->setPressAction([this, button, plunderResources]() {
                const auto choose = new eChooseButton(window());
                std::vector<std::string> names;
                for(const auto r : plunderResources) {
                    const auto name = r == eResourceType::none ?
                                          eLanguage::text("any_resource_plunder") :
                                          eResourceTypeHelpers::typeName(r);
                    names.push_back(name);
                }
                const auto act = [this, button, plunderResources, names](const int val) {
                    const auto r = plunderResources[val];
                    button->setText(names[val]);
                    mSelectedPlunder = r;
                };
                choose->initialize(8, names, act);

                window()->execDialog(choose);
                choose->align(eAlignment::center);
            });

            plunderW->stackHorizontally();
            plunderW->fitContent();
            plunderW->align(eAlignment::right);

            titleLabel->align(eAlignment::vcenter);
            button->align(eAlignment::vcenter);
        }

        titleW->fitHeight();
        hhh -= titleW->height();
    }

    const auto horsemen = new eEnlistWidget(window());
    const auto hoplite = new eEnlistWidget(window());
    const auto navy = new eEnlistWidget(window());
    const auto heroes = new eEnlistWidget(window());
    const auto mythical = new eEnlistWidget(window());
    const auto allies = new eEnlistWidget(window());

    const auto buttonsWid = new eWidget(window());
    {
        const auto cancelButt = new eFramedButton(window());
        cancelButt->setTinyFontSize();
        cancelButt->setUnderline(false);
        cancelButt->setText(eLanguage::text("cancel"));
        cancelButt->fitContent();
        const auto cancelAct = [this]() {
            deleteLater();
        };
        cancelButt->setPressAction(cancelAct);
        buttonsWid->addWidget(cancelButt);

        const auto enlistAllButt = new eFramedButton(window());
        enlistAllButt->setTinyFontSize();
        enlistAllButt->setUnderline(false);
        enlistAllButt->setText(eLanguage::text("enlist_all"));
        enlistAllButt->fitContent();
        const auto enlistAllAct = [this, enlistable,
                                  horsemen,
                                  hoplite,
                                  navy,
                                  heroes,
                                  mythical,
                                  allies]() {
            mSelected = enlistable;
            horsemen->selectAll();
            hoplite->selectAll();
            navy->selectAll();
            heroes->selectAll();
            mythical->selectAll();
            allies->selectAll();
        };
        enlistAllButt->setPressAction(enlistAllAct);
        buttonsWid->addWidget(enlistAllButt);

        const auto clearAllButt = new eFramedButton(window());
        clearAllButt->setTinyFontSize();
        clearAllButt->setUnderline(false);
        clearAllButt->setText(eLanguage::text("clear_all"));
        clearAllButt->fitContent();
        const auto clearAllAct = [this,
                                 horsemen,
                                 hoplite,
                                 navy,
                                 heroes,
                                 mythical,
                                 allies]() {
            mSelected.clear();
            horsemen->clearAll();
            hoplite->clearAll();
            navy->clearAll();
            heroes->clearAll();
            mythical->clearAll();
            allies->clearAll();
        };
        clearAllButt->setPressAction(clearAllAct);
        buttonsWid->addWidget(clearAllButt);

        const auto dispatchButt = new eFramedButton(window());
        dispatchButt->setTinyFontSize();
        dispatchButt->setUnderline(false);
        dispatchButt->setText(eLanguage::text("dispatch"));
        dispatchButt->fitContent();
        const auto dispatchAct = [this, action]() {
            if(action) action(mSelected, mSelectedPlunder);
            deleteLater();
        };
        dispatchButt->setPressAction(dispatchAct);
        buttonsWid->addWidget(dispatchButt);

        buttonsWid->setNoPadding();
        buttonsWid->fitContent();
        buttonsWid->setWidth(innerWid->width());
        buttonsWid->layoutHorizontallyWithoutSpaces();
        hhh -= buttonsWid->height();
    }

    hhh -= 2*pp;

    {
        const auto selWid = new eWidget(window());
        innerWid->addWidget(selWid);
        selWid->resize(ww, hhh);

        const auto selectionChanged = [this,
                                      horsemen,
                                      hoplite,
                                      navy,
                                      heroes,
                                      mythical,
                                      allies]() {
            mSelected.clear();
            mSelected.add(horsemen->selected());
            mSelected.add(hoplite->selected());
            mSelected.add(navy->selected());
            mSelected.add(heroes->selected());
            mSelected.add(mythical->selected());
            mSelected.add(allies->selected());
        };

        {
            const auto col1 = new eWidget(window());
            const int www = ww/2 - pp;
            col1->resize(www, hhh);
            selWid->addWidget(col1);

            const int hhhh = hhh/2 - pp;

            horsemen->resize(www, hhhh);
            const auto hef = extractType(eBannerType::horseman, enlistable);
            horsemen->initialize(hef, {}, selectionChanged,
                                 eLanguage::text("horsemen"), true);
            col1->addWidget(horsemen);

            hoplite->resize(www, hhhh);
            const auto hhef = extractType(eBannerType::hoplite, enlistable);
            hoplite->initialize(hhef, {}, selectionChanged,
                                eLanguage::text("hoplite"), true);
            col1->addWidget(hoplite);

            col1->layoutVerticallyWithoutSpaces();
        }
        {
            const auto col2 = new eWidget(window());
            const int www = ww/2 - pp;
            col2->resize(www, hhh);
            selWid->addWidget(col2);

            const int hhhh = hhh/4 - pp;

            navy->resize(www, hhhh);
            navy->initialize(eEnlistedForces(), {}, selectionChanged,
                             eLanguage::text("navy"), false);
            col2->addWidget(navy);

            heroes->resize(www, hhhh);
            eEnlistedForces efh;
            efh.fHeroes = enlistable.fHeroes;
            heroes->initialize(efh, heroesAbroad, selectionChanged,
                               eLanguage::text("heroes"), false);
            col2->addWidget(heroes);

            mythical->resize(www, hhhh);
            eEnlistedForces hhef;
            for(const auto& s : enlistable.fSoldiers) {
                const auto t = s->type();
                if(t == eBannerType::amazon ||
                   t == eBannerType::aresWarrior) {
                    hhef.fSoldiers.push_back(s);
                }
            }
            mythical->initialize(hhef, {}, selectionChanged,
                                eLanguage::text("mythical_warriors"), true);
            col2->addWidget(mythical);

            allies->resize(www, hhhh);
            eEnlistedForces efa;
            efa.fAllies = enlistable.fAllies;
            allies->initialize(efa, {}, selectionChanged,
                               eLanguage::text("support_from_allies"), false);
            col2->addWidget(allies);

            col2->layoutVerticallyWithoutSpaces();
        }

        selWid->layoutHorizontallyWithoutSpaces();
    }

    innerWid->addWidget(buttonsWid);
    innerWid->layoutVerticallyWithoutSpaces();
}
