#include "eworldmapwidget.h"

#include "textures/egametextures.h"
#include "textures/einterfacetextures.h"

#include "engine/eworldboard.h"

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
            p.drawTexture(x, y, coll.getTexture(mFrame % coll.size()));
        }
    };

    const auto& hc = mBoard->homeCity();
    handleCity(hc);
    const auto& cts = mBoard->cities();
    for(const auto& ct : cts) {
        handleCity(ct);
    }
}
