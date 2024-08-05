#include "eworldmapwidget.h"

#include "textures/egametextures.h"
#include "textures/einterfacetextures.h"

#include "engine/egameboard.h"
#include "gameEvents/earmyreturnevent.h"
#include "gameEvents/einvasionevent.h"
#include "gameEvents/etroopsrequestfulfilledevent.h"
#include "elanguage.h"
#include "audio/esounds.h"
#include "estringhelpers.h"
#include "evectorhelpers.h"
#include "enumbers.h"

eWorldMapWidget::eWorldMapWidget(eMainWindow* const window) :
    eLabel(window) {}

void eWorldMapWidget::setSelectColonyMode(
        const bool scm, const eColonySelection& s) {
    mSelectColonyMode = scm;
    mColonySelection = s;
}

void eWorldMapWidget::setBoard(eGameBoard* const b) {
    mGameBoard = b;
    setWorldBoard(b ? b->getWorldBoard() : nullptr);
}

void eWorldMapWidget::setWorldBoard(eWorldBoard* const b) {
    mWorldBoard = b;
    if(b) setMap(b->map());
    updateWidgets();
}

void eWorldMapWidget::setSelectCityAction(const eSelectCityAction& s) {
    mSelectCityAction = s;
}

void eWorldMapWidget::setSetTextAction(const eSetTextAction& s) {
    mSetTextAction = s;
}

void eWorldMapWidget::paintEvent(ePainter& p) {
    mFrame++;
    eLabel::paintEvent(p);
    if(!mWorldBoard) return;

    const auto& intrfc = eGameTextures::interface();
    const auto res = resolution();
    const int iRes = static_cast<int>(res.uiScale());
    const auto& texs = intrfc[iRes];
    const bool poseidon = mWorldBoard->poseidonMode();
    const bool editor = mWorldBoard->editorMode();

    const auto handleCity = [&](const stdsptr<eWorldCity>& ct) {
        if(!mSelectColonyMode && !editor && !ct->active()) return;
        if(mSelectColonyMode) {
            const bool c = eVectorHelpers::contains(mColonySelection, ct);
            if(!c) return;
        }
        const auto t = ct->type();
        stdsptr<eTexture> tex;
        switch(t) {
        case eCityType::parentCity: {
            if(poseidon) tex = texs.fPoseidonMainCity;
            else tex = texs.fZeusMainCity;
        } break;
        case eCityType::colony: {
            const bool active = ct->active();
            if(active) {
                if(poseidon) tex = texs.fPoseidonCollony;
                else tex = texs.fZeusCollony;
            } else {
                if(poseidon) tex = texs.fPoseidonDisabledCollony;
                else tex = texs.fZeusDisabledCollony;
            }
        } break;
        case eCityType::foreignCity: {
            const auto nat = ct->nationality();
            switch(nat) {
            case eNationality::greek:
                tex = texs.fZeusGreekCity;
                break;
            case eNationality::trojan:
                tex = texs.fZeusTrojanCity;
                break;
            case eNationality::persian:
                tex = texs.fZeusPersianCity;
                break;
            case eNationality::centaur:
                tex = texs.fZeusCentaurCity;
                break;
            case eNationality::amazon:
                tex = texs.fZeusAmazonCity;
                break;

            case eNationality::egyptian:
                tex = texs.fPoseidonEgyptianCity;
                break;
            case eNationality::mayan:
                tex = texs.fPoseidonMayanCity;
                break;
            case eNationality::phoenician:
                tex = texs.fPoseidonPhoenicianCity;
                break;
            case eNationality::oceanid:
                tex = texs.fPoseidonOceanidCity;
                break;
            case eNationality::atlantean:
                tex = texs.fPoseidonAtlanteanCity;
                break;
            }
        } break;

        case eCityType::enchantedPlace:
            tex = texs.fZeusPlace;
            break;
        case eCityType::destroyedCity:
            tex = texs.fZeusRuins;
            break;

        case eCityType::distantCity: {
            const auto dir = ct->direction();
            switch(dir) {
            case eDistantDirection::none:
                tex = texs.fZeusDistantCity;
                break;
            case eDistantDirection::N:
                tex = texs.fZeusDistantCityN;
                break;
            case eDistantDirection::NE:
                tex = texs.fZeusDistantCityNE;
                break;
            case eDistantDirection::E:
                tex = texs.fZeusDistantCityE;
                break;
            case eDistantDirection::SE:
                tex = texs.fZeusDistantCitySE;
                break;
            case eDistantDirection::S:
                tex = texs.fZeusDistantCityS;
                break;
            case eDistantDirection::SW:
                tex = texs.fZeusDistantCitySW;
                break;
            case eDistantDirection::W:
                tex = texs.fZeusDistantCityW;
                break;
            case eDistantDirection::NW:
                tex = texs.fZeusDistantCityNW;
                break;
            }
        } break;

        }

        const int x = ct->x()*width();
        const int y = ct->y()*height();
        p.drawTexture(x, y, tex, eAlignment::center);

        const auto flagAl = eAlignment::hcenter | eAlignment::top;
        const int flagX = x + tex->width()/2;
        const int flagY = y + tex->height()/2;
        if(ct->isParentCity()) {
            p.drawTexture(flagX, flagY, texs.fMainCityFlag, flagAl);
        } else if(ct->isVassal() || ct->isColony()) {
            p.drawTexture(flagX, flagY, texs.fEmpireCityFlag, flagAl);
        } else if(ct->isAlly()) {
            const auto& coll = texs.fAllyCityFlag;
            const int cs = coll.size();
            const auto& tex = coll.getTexture(mFrame % cs);
            p.drawTexture(flagX, flagY, tex, flagAl);
        }

        const auto hc = mWorldBoard->currentCity();
        if(ct != hc &&
           t != eCityType::destroyedCity &&
           t != eCityType::distantCity &&
           t != eCityType::enchantedPlace) {
            const auto& aColl = texs.fCityArmy;
            const auto& wColl = texs.fCityWealth;
            const int s = editor ? ct->militaryStrength() :
                                   ct->shields();
            const int a = std::clamp(s, 1, 5);
            const int w = std::clamp(ct->wealth(), 1, 5);
            const int lp = res.largePadding();
            const int hp = res.hugePadding();
            int xx = x - hp;
            const int yy = y - hp;
            const auto& aTex = aColl.getTexture(a - 1);
            p.drawTexture(xx, yy, aTex, eAlignment::top);
            xx += lp + aTex->width()/2;
            const auto& wTex = wColl.getTexture(w - 1);
            p.drawTexture(xx, yy, wTex, eAlignment::top);
        }

        if(ct->rebellion() || ct->conqueredByRival()) {
            const auto& coll = texs.fCityRebellion;
            const int cs = coll.size();
            const auto tex = coll.getTexture(mFrame % cs);
            p.drawTexture(x, y, tex);
        }

        {
            const auto& name = ct->name();
            const auto nameFind = mNames.find(name);
            stdsptr<eTexture> nameTex;
            if(nameFind == mNames.end()) {
                nameTex = std::make_shared<eTexture>();
                const auto res = resolution();
                const int fontSize = res.smallFontSize();
                const auto font = eFonts::defaultFont(fontSize);
                nameTex->loadText(renderer(), name, eFontColor::light, *font);
                mNames[name] = nameTex;
            } else {
                nameTex = nameFind->second;
            }
            const int dx = x - nameTex->width()/2;
            const int dy = y + nameTex->height();
            p.drawTexture(dx, dy, nameTex);
        }
    };

    const auto hc = mWorldBoard->currentCity();
    const auto& cts = mWorldBoard->cities();
    for(const auto& ct : cts) {
        handleCity(ct);
    }

    const auto cityFigures = [&](const eNationality nat) {
        switch(nat) {
        case eNationality::greek:
            return &texs.fZeusGreekArmy;
        case eNationality::trojan:
            return &texs.fZeusTrojanArmy;
        case eNationality::persian:
            return &texs.fZeusPersianArmy;
        case eNationality::centaur:
            return &texs.fZeusCentaurArmy;
        case eNationality::amazon:
            return &texs.fZeusAmazonArmy;

        case eNationality::egyptian:
            return &texs.fPoseidonEgyptianArmy;
        case eNationality::mayan:
            return &texs.fPoseidonMayanArmy;
        case eNationality::phoenician:
            return &texs.fPoseidonPhoenicianArmy;
        case eNationality::oceanid:
            return &texs.fPoseidonOceanidArmy;
        case eNationality::atlantean:
            return &texs.fPoseidonAtlanteanArmy;
        default:
            return static_cast<const eTextureCollection*>(nullptr);
        }
        return static_cast<const eTextureCollection*>(nullptr);
    };

    if(mGameBoard) {
        const auto date = mGameBoard->date();
        const auto& cs = mGameBoard->armyEvents();
        for(const auto c : cs) {
            const auto cDate = c->startDate();
            const int days = cDate - date;
            const int totDays = eNumbers::sArmyTravelTime;
            const double frac = std::clamp(1. - (1.*days)/totDays, 0., 1.);
            const auto& cc = c->city();
            int x;
            int y;
            const bool reverse = dynamic_cast<eArmyReturnEvent*>(c);
            if(reverse) armyDrawXY(*cc, *hc, frac, x, y);
            else armyDrawXY(*hc, *cc, frac, x, y);
            const int dx = res.largePadding();
            const auto& forces = c->forces();
            const int s = forces.fSoldiers.size();
            if(s != 0) {
                const int n = std::clamp(s/3, 0, 2);
                const eTextureCollection* coll = nullptr;;
                if(poseidon) coll = &texs.fPoseidonPlayerArmy;
                else coll = &texs.fZeusPlayerArmy;;
                const auto& tex = coll->getTexture(n);
                p.drawTexture(x, y, tex, eAlignment::center);
                x += dx;
            }

            for(const auto& a : forces.fAllies) {
                const int n = std::clamp(a->shields()/2, 0, 2);
                const auto coll = cityFigures(a->nationality());
                const auto tex = coll ? coll->getTexture(n) : nullptr;
                int x;
                int y;
                if(reverse) armyDrawXY(*cc, *a, frac, x, y);
                else armyDrawXY(*a, *cc, frac, x, y);
                if(tex) p.drawTexture(x, y, tex, eAlignment::center);
            }

            for(const auto h : forces.fHeroes) {
                stdsptr<eTexture> tex;
                switch(h) {
                case eHeroType::achilles:
                    tex = texs.fZeusAchilles;
                    break;
                case eHeroType::atalanta:
                    tex = texs.fPoseidonAtalanta;
                    break;
                case eHeroType::bellerophon:
                    tex = texs.fPoseidonBellerophon;
                    break;
                case eHeroType::hercules:
                    tex = texs.fZeusHercules;
                    break;
                case eHeroType::jason:
                    tex = texs.fZeusJason;
                    break;
                case eHeroType::odysseus:
                    tex = texs.fZeusOdysseus;
                    break;
                case eHeroType::perseus:
                    tex = texs.fZeusPerseus;
                    break;
                case eHeroType::theseus:
                    tex = texs.fZeusTheseus;
                    break;
                }

                p.drawTexture(x, y, tex, eAlignment::center);
                x += dx;
            }
        }
        const auto& is = mGameBoard->invasions();
        for(const auto i : is) {
            if(!i->warned()) continue;
            const auto sDate = i->startDate();
            const auto wDate = i->firstWarning();
            const int days = sDate - date;
            const int totDays = sDate - wDate;
            const double frac = std::clamp(1. - (1.*days)/totDays, 0., 1.);
            const auto& cc = i->city();
            int x;
            int y;
            armyDrawXY(*cc, *hc, frac, x, y);

            const int n = std::clamp(cc->shields()/2, 0, 2);
            const auto coll = cityFigures(cc->nationality());
            const auto tex = coll ? coll->getTexture(n) : nullptr;
            p.drawTexture(x, y, tex, eAlignment::center);
        }
    }
}

bool eWorldMapWidget::mousePressEvent(const eMouseEvent& e) {
    if(e.button() == eMouseButton::right) {
        if(mSelectCityAction) mSelectCityAction(nullptr);
        return true;
    } else {
        return false;
    }
}

class eTransparentWidget : public eWidget {
public:
    using eWidget::eWidget;

    void setPressAction(const eAction& a) {
        mPressAction = a;
    }

    void setReleaseAction(const eAction& a) {
        mReleaseAction = a;
    }
protected:
    bool mousePressEvent(const eMouseEvent& e) {
        if(e.button() == eMouseButton::left) {
            if(mPressAction) mPressAction();
            eSounds::playButtonSound();
            return true;
        } else {
            return false;
        }
    }

    bool mouseReleaseEvent(const eMouseEvent& e) {
        if(e.button() == eMouseButton::left) {
            if(mReleaseAction) mReleaseAction();
            return true;
        } else {
            return false;
        }
    }

    bool mouseMoveEvent(const eMouseEvent& e) {
        (void)e;
        return true;
    }

    bool mouseEnterEvent(const eMouseEvent& e) {
        (void)e;
        return true;
    }

    bool mouseLeaveEvent(const eMouseEvent& e) {
        (void)e;
        return true;
    }
private:
    eAction mPressAction;
    eAction mReleaseAction;
};

class eCityTransparentWidget : public eTransparentWidget {
public:
    using eTransparentWidget::eTransparentWidget;

    void setCity(const stdsptr<eWorldCity>& c) {
        mCity = c;
    }
protected:
    bool mousePressEvent(const eMouseEvent& e) {
        if(e.button() == eMouseButton::left) {
            mPressX = e.x();
            mPressY = e.y();
        }
        return eTransparentWidget::mousePressEvent(e);
    }

    bool mouseMoveEvent(const eMouseEvent& e) {
        if(static_cast<bool>(e.buttons() & eMouseButton::left)) {
            if(!mCity) return true;
            const auto p = parent();
            const double pw = p->width();
            const double ph = p->height();
            const double cx = (x() + width()/2 + e.x() - mPressX)/pw;
            const double cy = (y() + height()/2 + e.y() - mPressY)/ph;
            mCity->move(cx, cy);
        }
        return true;
    }
private:
    stdsptr<eWorldCity> mCity;

    int mPressX = 0;
    int mPressY = 0;
};

void eWorldMapWidget::updateWidgets() {
    removeAllWidgets();
    if(!mWorldBoard) return;
    const auto& intrfc = eGameTextures::interface();
    const auto res = resolution();
    const int iRes = static_cast<int>(res.uiScale());
    const auto& texs = intrfc[iRes];
    const auto& tex = texs.fZeusMainCity;
    const int w = tex->width();
    const int h = tex->height();
    const int w2 = 2*w;
    const int h2 = 2*h;

    const int group = 44;
    const int string = 334;
    const auto clickForInfo = eLanguage::zeusText(group, string);

    const bool editor = mWorldBoard->editorMode();

    const auto& hc = mWorldBoard->currentCity();
    if(mGameBoard) {
        const auto date = mGameBoard->date();
        const auto& cs = mGameBoard->armyEvents();
        for(const auto c : cs) {
            const auto cDate = c->startDate();
            const int days = cDate - date;
            const int totDays = eNumbers::sArmyTravelTime;
            const double frac = std::clamp(1. - (1.*days)/totDays, 0., 1.);
            const auto& cc = c->city();
            const bool reverse = dynamic_cast<eArmyReturnEvent*>(c);
            const auto& forces = c->forces();
            {
                int cx;
                int cy;
                if(reverse) armyDrawXY(*cc, *hc, frac, cx, cy);
                else armyDrawXY(*hc, *cc, frac, cx, cy);
                const int s = forces.fSoldiers.size();
                const bool hs = forces.fHeroes.empty();
                if(s != 0 || !hs) {
                    const int x = cx - w2/2;
                    const int y = cy - h2/2;
                    const auto ww = new eTransparentWidget(window());
                    ww->setPressAction([this, c, cc, reverse]() {
                        if(mSetTextAction) {
                            const int group = 47;
                            const bool help = dynamic_cast<eTroopsRequestFulfilledEvent*>(c);
                            const int string = reverse ? 15 : (help ? 9 : 11);
                            auto text = eLanguage::zeusText(group, string);
                            eStringHelpers::replace(text, "[city_name]", cc->name());
                            mSetTextAction(text);
                        }
                    });
                    ww->resize(w2, h2);
                    addWidget(ww);
                    ww->move(x, y);
                    ww->setTooltip(clickForInfo);
                }
            }

            for(const auto& a : forces.fAllies) {
                int cx;
                int cy;
                if(reverse) armyDrawXY(*cc, *a, frac, cx, cy);
                else armyDrawXY(*a, *cc, frac, cx, cy);
                const int x = cx - w2/2;
                const int y = cy - h2/2;
                const auto ww = new eTransparentWidget(window());
                ww->setPressAction([this, cc, reverse]() {
                    if(mSetTextAction) {
                        const int group = 47;
                        const int string = reverse ? 23 : 19;
                        auto text = eLanguage::zeusText(group, string);
                        eStringHelpers::replace(text, "[city_name]", cc->name());
                        mSetTextAction(text);
                    }
                });
                ww->resize(w2, h2);
                addWidget(ww);
                ww->move(x, y);
                ww->setTooltip(clickForInfo);
            }
        }
        const auto& is = mGameBoard->invasions();
        for(const auto i : is) {
            if(!i->warned()) continue;
            const auto sDate = i->startDate();
            const auto wDate = i->firstWarning();
            const int days = sDate - date;
            const int totDays = sDate - wDate;
            const double frac = std::clamp(1. - (1.*days)/totDays, 0., 1.);
            const auto& cc = i->city();
            int cx;
            int cy;
            armyDrawXY(*cc, *hc, frac, cx, cy);

            const int x = cx - w2/2;
            const int y = cy - h2/2;
            const auto ww = new eTransparentWidget(window());
            ww->setPressAction([this, cc]() {
                if(mSetTextAction) {
                    const int group = 47;
                    const int string = 25;
                    const auto text = eLanguage::zeusText(group, string);
                    mSetTextAction(text);
                }
            });
            ww->resize(w2, h2);
            addWidget(ww);
            ww->move(x, y);
            ww->setTooltip(clickForInfo);
        }
    }

    const auto& cts = mWorldBoard->cities();
    for(const auto& ct : cts) {
        if(!mSelectColonyMode && !editor && !ct->active()) continue;
        if(mSelectColonyMode) {
            const bool c = eVectorHelpers::contains(mColonySelection, ct);
            if(!c) continue;
        }
        const int cx = width()*ct->x();
        const int cy = height()*ct->y();
        const int x = cx - w/2;
        const int y = cy - h/2;
        const auto ww = new eCityTransparentWidget(window());
        if(editor) {
            ww->setCity(ct);
            ww->setReleaseAction([this]() {
                updateWidgets();
            });
        }
        ww->setPressAction([this, ct]() {
            if(mSelectColonyMode) {
                for(const auto& c : mColonySelection) {
                    c->setState(eCityState::inactive);
                }
                ct->setState(eCityState::active);
            }
            if(mSelectCityAction) mSelectCityAction(ct);
        });
        ww->resize(w, h);
        addWidget(ww);
        ww->move(x, y);
        ww->setTooltip(clickForInfo);
    }
}

void eWorldMapWidget::armyDrawXY(eWorldCity& c1, eWorldCity& c2,
                                 const double frac, int& x, int& y) {
    const double hx = c1.x();
    const double hy = c1.y();
    const double ccx = c2.x();
    const double ccy = c2.y();
    x = (hx + (ccx - hx)*frac)*width();
    y = (hy + (ccy - hy)*frac)*height();
}

void eWorldMapWidget::setMap(const eWorldMap map) {
    const auto& intrfc = eGameTextures::interface();
    const auto res = resolution();
    const int iRes = static_cast<int>(res.uiScale());
    const auto& texs = intrfc[iRes];

    stdsptr<eTexture> tex;
    switch(map) {
    case eWorldMap::greece1:
        eGameTextures::loadMapOfGreece1();
        tex = texs.fMapOfGreece1;
        break;
    case eWorldMap::greece2:
        eGameTextures::loadMapOfGreece2();
        tex = texs.fMapOfGreece2;
        break;
    case eWorldMap::greece3:
        eGameTextures::loadMapOfGreece3();
        tex = texs.fMapOfGreece3;
        break;
    case eWorldMap::greece4:
        eGameTextures::loadMapOfGreece4();
        tex = texs.fMapOfGreece4;
        break;
    case eWorldMap::greece5:
        eGameTextures::loadMapOfGreece5();
        tex = texs.fMapOfGreece5;
        break;
    case eWorldMap::greece6:
        eGameTextures::loadMapOfGreece6();
        tex = texs.fMapOfGreece6;
        break;
    case eWorldMap::greece7:
        eGameTextures::loadMapOfGreece7();
        tex = texs.fMapOfGreece7;
        break;
    case eWorldMap::greece8:
        eGameTextures::loadMapOfGreece8();
        tex = texs.fMapOfGreece8;
        break;

    case eWorldMap::poseidon1:
        eGameTextures::loadPoseidonMap1();
        tex = texs.fPoseidonMap1;
        break;
    case eWorldMap::poseidon2:
        eGameTextures::loadPoseidonMap2();
        tex = texs.fPoseidonMap2;
        break;
    case eWorldMap::poseidon3:
        eGameTextures::loadPoseidonMap3();
        tex = texs.fPoseidonMap3;
        break;
    case eWorldMap::poseidon4:
        eGameTextures::loadPoseidonMap4();
        tex = texs.fPoseidonMap4;
        break;
    }

    setTexture(tex);
    fitContent();
}
