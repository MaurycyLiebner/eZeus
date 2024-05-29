#include "eworldmapwidget.h"

#include "textures/egametextures.h"
#include "textures/einterfacetextures.h"

#include "engine/egameboard.h"
#include "gameEvents/earmyreturnevent.h"
#include "gameEvents/einvasionevent.h"

eWorldMapWidget::eWorldMapWidget(eMainWindow* const window) :
    eLabel(window) {}

void eWorldMapWidget::initialize() {
    const auto& intrfc = eGameTextures::interface();
    const auto res = resolution();
    const int iRes = static_cast<int>(res.uiScale());
    const auto& texs = intrfc[iRes];

    setTexture(texs.fMapOfGreece);
    fitContent();
}

void eWorldMapWidget::setBoard(eGameBoard* const b) {
    mGameBoard = b;
    mWorldBoard = b ? &b->getWorldBoard() : nullptr;
}

void eWorldMapWidget::setSelectCityAction(const eSelectCityAction& s) {
    mSelectCityAction = s;
}

void eWorldMapWidget::paintEvent(ePainter& p) {
    mFrame++;
    eLabel::paintEvent(p);
    if(!mWorldBoard) return;

    const auto& intrfc = eGameTextures::interface();
    const auto res = resolution();
    const int iRes = static_cast<int>(res.uiScale());
    const auto& texs = intrfc[iRes];
    const bool poseidon = mGameBoard->poseidonMode();

    const auto handleCity = [&](const stdsptr<eWorldCityBase>& ct) {
        const auto t = ct->type();
        stdsptr<eTexture> tex;
        switch(t) {
        case eWorldCityType::mainCity: {
            if(poseidon) tex = texs.fPoseidonMainCity;
            else tex = texs.fZeusMainCity;
        } break;
        case eWorldCityType::collony: {
            if(poseidon) tex = texs.fPoseidonCollony;
            else tex = texs.fZeusCollony;
        } break;
        case eWorldCityType::disabledColony: {
            if(poseidon) tex = texs.fPoseidonDisabledCollony;
            else tex = texs.fZeusDisabledCollony;
        } break;

        case eWorldCityType::greekCity:
            tex = texs.fZeusGreekCity;
            break;
        case eWorldCityType::trojanCity:
            tex = texs.fZeusTrojanCity;
            break;
        case eWorldCityType::persianCity:
            tex = texs.fZeusPersianCity;
            break;
        case eWorldCityType::centaurCity:
            tex = texs.fZeusCentaurCity;
            break;
        case eWorldCityType::amazonCity:
            tex = texs.fZeusAmazonCity;
            break;

        case eWorldCityType::egyptianCity:
            tex = texs.fPoseidonEgyptianCity;
            break;
        case eWorldCityType::mayanCity:
            tex = texs.fPoseidonMayanCity;
            break;
        case eWorldCityType::phoenicianCity:
            tex = texs.fPoseidonPhoenicianCity;
            break;
        case eWorldCityType::oceanidCity:
            tex = texs.fPoseidonOceanidCity;
            break;
        case eWorldCityType::atlanteanCity:
            tex = texs.fPoseidonAtlanteanCity;
            break;

        case eWorldCityType::place:
            tex = texs.fZeusPlace;
            break;
        case eWorldCityType::ruins:
            tex = texs.fZeusRuins;
            break;

        case eWorldCityType::distantCity:
            tex = texs.fZeusDistantCity;
            break;
        case eWorldCityType::distantCityN:
            tex = texs.fZeusDistantCityN;
            break;
        case eWorldCityType::distantCityNE:
            tex = texs.fZeusDistantCityNE;
            break;
        case eWorldCityType::distantCityE:
            tex = texs.fZeusDistantCityE;
            break;
        case eWorldCityType::distantCitySE:
            tex = texs.fZeusDistantCitySE;
            break;
        case eWorldCityType::distantCityS:
            tex = texs.fZeusDistantCityS;
            break;
        case eWorldCityType::distantCitySW:
            tex = texs.fZeusDistantCitySW;
            break;
        case eWorldCityType::distantCityW:
            tex = texs.fZeusDistantCityW;
            break;
        case eWorldCityType::distantCityNW:
            tex = texs.fZeusDistantCityNW;
            break;

        }

        const int x = ct->x()*width();
        const int y = ct->y()*height();
        p.drawTexture(x, y, tex, eAlignment::center);

        const auto flagAl = eAlignment::hcenter | eAlignment::top;
        const int flagX = x + tex->width()/2;
        const int flagY = y + tex->height()/2;
        switch(ct->relationship()) {
        case eWorldCityRelationship::mainCity:
            p.drawTexture(flagX, flagY, texs.fMainCityFlag, flagAl);
            break;
        case eWorldCityRelationship::vassal:
        case eWorldCityRelationship::collony:
            p.drawTexture(flagX, flagY, texs.fEmpireCityFlag, flagAl);
            break;
        case eWorldCityRelationship::ally: {
            const auto& coll = texs.fAllyCityFlag;
            const int cs = coll.size();
            const auto& tex = coll.getTexture(mFrame % cs);
            p.drawTexture(flagX, flagY, tex, flagAl);
        }   break;
        default:
            break;
        }

        const auto hc = mWorldBoard->homeCity();
        if(ct != hc) {
            const auto wt = static_cast<eWorldCity*>(ct.get());
            const auto& aColl = texs.fCityArmy;
            const auto& wColl = texs.fCityWealth;
            const int a = std::clamp(wt->army(), 1, 5);
            const int w = std::clamp(wt->wealth(), 1, 5);
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

        if(ct->rebellion()) {
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

    const auto& hc = mWorldBoard->homeCity();
    handleCity(hc);
    const auto& cts = mWorldBoard->cities();
    for(const auto& ct : cts) {
        handleCity(ct);
    }

    const auto armyDrawXY = [&](eWorldCity& c1, eWorldCity& c2,
                               const double frac, int& x, int& y) {
        const double hx = c1.x();
        const double hy = c1.y();
        const double ccx = c2.x();
        const double ccy = c2.y();
        x = (hx + (ccx - hx)*frac)*width();
        y = (hy + (ccy - hy)*frac)*height();
    };

    const auto cityFigures = [&](const eWorldCityType wct) {
        switch(wct) {
        case eWorldCityType::greekCity:
            return &texs.fZeusGreekArmy;
        case eWorldCityType::trojanCity:
            return &texs.fZeusTrojanArmy;
        case eWorldCityType::persianCity:
            return &texs.fZeusPersianArmy;
        case eWorldCityType::centaurCity:
            return &texs.fZeusCentaurArmy;
        case eWorldCityType::amazonCity:
            return &texs.fZeusAmazonArmy;

        case eWorldCityType::egyptianCity:
            return &texs.fPoseidonEgyptianArmy;
        case eWorldCityType::mayanCity:
            return &texs.fPoseidonMayanArmy;
        case eWorldCityType::phoenicianCity:
            return &texs.fPoseidonPhoenicianArmy;
        case eWorldCityType::oceanidCity:
            return &texs.fPoseidonOceanidArmy;
        case eWorldCityType::atlanteanCity:
            return &texs.fPoseidonAtlanteanArmy;
        default:
            return static_cast<const eTextureCollection*>(nullptr);
        }
        return static_cast<const eTextureCollection*>(nullptr);
    };

    const auto date = mGameBoard->date();
    const auto& cs = mGameBoard->armyEvents();
    for(const auto c : cs) {
        const auto cDate = c->startDate();
        const int days = cDate - date;
        const int totDays = eArmyEventBase::sWaitTime;
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
            const int n = std::clamp(a->army()/2, 0, 2);
            const auto coll = cityFigures(a->type());
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

        const int n = std::clamp(cc->army()/2, 0, 2);
        const auto coll = cityFigures(cc->type());
        const auto tex = coll ? coll->getTexture(n) : nullptr;
        p.drawTexture(x, y, tex, eAlignment::center);
    }
}

bool eWorldMapWidget::mousePressEvent(const eMouseEvent& e) {
    if(e.button() == eMouseButton::right) {
        mSelectCityAction(nullptr);
        return true;
    }
    if(!mWorldBoard || !mSelectCityAction) return false;
    const auto& cts = mWorldBoard->cities();
    stdsptr<eWorldCity> closestCt;
    int minDist = width()/50;
    for(const auto& ct : cts) {
        const int px = width()*ct->x();
        const int py = height()*ct->y();
        const int dx = e.x() - px;
        const int dy = e.y() - py;
        const int dist = sqrt(dx*dx + dy*dy);
        if(dist < minDist) {
            closestCt = ct;
            minDist = dist;
        }
    }
    mSelectCityAction(closestCt);
    return true;
}
