#include "eworldmapwidget.h"

#include "textures/egametextures.h"
#include "textures/einterfacetextures.h"

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

void eWorldMapWidget::setBoard(eWorldBoard* const b) {
    mBoard = b;
}

void eWorldMapWidget::setSelectCityAction(const eSelectCityAction& s) {
    mSelectCityAction = s;
}

void eWorldMapWidget::paintEvent(ePainter& p) {
    mFrame++;
    eLabel::paintEvent(p);
    if(!mBoard) return;

    const auto& intrfc = eGameTextures::interface();
    const auto res = resolution();
    const int iRes = static_cast<int>(res.uiScale());
    const auto& texs = intrfc[iRes];

    const auto handleCity = [&](const stdsptr<eWorldCityBase>& ct) {
        const auto t = ct->type();
        const int ti = static_cast<int>(t);
        const auto& tex = texs.fWorldCities.getTexture(ti);
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
            p.drawTexture(flagX, flagY, coll.getTexture(mFrame % coll.size()), flagAl);
        }   break;
        default:
            break;
        }

        if(ct->rebellion()) {
            const auto& coll = texs.fCityRebellion;
            const auto tex = coll.getTexture(mFrame % coll.size());
            p.drawTexture(x, y, tex);
        }

        const auto& name = ct->name();
        const auto nameFind = mNames.find(name);
        stdsptr<eTexture> nameTex;
        if(nameFind == mNames.end()) {
            nameTex = std::make_shared<eTexture>();
            const auto font = eFonts::defaultFont(resolution().smallFontSize());
            const auto white = SDL_Color{255, 255, 255, 255};
            nameTex->loadText(renderer(), name, white, *font);
            mNames[name] = nameTex;
        } else {
            nameTex = nameFind->second;
        }
        p.drawTexture(x - nameTex->width()/2, y + nameTex->height(), nameTex);
    };

    const auto& hc = mBoard->homeCity();
    handleCity(hc);
    const auto& cts = mBoard->cities();
    for(const auto& ct : cts) {
        handleCity(ct);
    }
}

bool eWorldMapWidget::mousePressEvent(const eMouseEvent& e) {
    if(e.button() == eMouseButton::right) {
        mSelectCityAction(nullptr);
        return true;
    }
    if(!mBoard || !mSelectCityAction) return false;
    const auto& cts = mBoard->cities();
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
