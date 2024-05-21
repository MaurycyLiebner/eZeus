#include "eworldmapwidget.h"

#include "textures/egametextures.h"
#include "textures/einterfacetextures.h"

#include "engine/egameboard.h"
#include "gameEvents/earmyreturnevent.h"

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
            p.drawTexture(flagX, flagY, coll.getTexture(mFrame % cs), flagAl);
        }   break;
        default:
            break;
        }

        if(ct->rebellion()) {
            const auto& coll = texs.fCityRebellion;
            const int cs = coll.size();
            const auto tex = coll.getTexture(mFrame % cs);
            p.drawTexture(x, y, tex);
        }

        const auto& name = ct->name();
        const auto nameFind = mNames.find(name);
        stdsptr<eTexture> nameTex;
        if(nameFind == mNames.end()) {
            nameTex = std::make_shared<eTexture>();
            const auto font = eFonts::defaultFont(resolution().smallFontSize());
            nameTex->loadText(renderer(), name, eFontColor::light, *font);
            mNames[name] = nameTex;
        } else {
            nameTex = nameFind->second;
        }
        p.drawTexture(x - nameTex->width()/2, y + nameTex->height(), nameTex);
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
            const eTextureCollection* coll = nullptr;
            switch(a->type()) {
            case eWorldCityType::greekCity:
                coll = &texs.fZeusGreekArmy;
                break;
            case eWorldCityType::trojanCity:
                coll = &texs.fZeusTrojanArmy;
                break;
            case eWorldCityType::persianCity:
                coll = &texs.fZeusPersianArmy;
                break;
            case eWorldCityType::centaurCity:
                coll = &texs.fZeusCentaurArmy;
                break;
            case eWorldCityType::amazonCity:
                coll = &texs.fZeusAmazonArmy;
                break;

            case eWorldCityType::egyptianCity:
                coll = &texs.fPoseidonEgyptianArmy;
                break;
            case eWorldCityType::mayanCity:
                coll = &texs.fPoseidonMayanArmy;
                break;
            case eWorldCityType::phoenicianCity:
                coll = &texs.fPoseidonPhoenicianArmy;
                break;
            case eWorldCityType::oceanidCity:
                coll = &texs.fPoseidonOceanidArmy;
                break;
            case eWorldCityType::atlanteanCity:
                coll = &texs.fPoseidonAtlanteanArmy;
                break;
            default:
                break;
            }

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
