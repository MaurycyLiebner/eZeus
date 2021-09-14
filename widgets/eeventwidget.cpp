#include "eeventwidget.h"

#include "textures/egametextures.h"

void eEventWidget::pushEvent(const eEvent e, eTile* const tile) {
    const auto button = new eEventButton(e, window());
    mButtons.insert(mButtons.begin(), button);
    if(mButtons.size() > 4) {
        const auto b = mButtons.back();
        b->deleteLater();
        mButtons.pop_back();
    }
    prependWidget(button);
    button->setPressAction([this, tile]() {
        if(mViewTileHandler) {
            mViewTileHandler(tile);
        }
    });
    setHeight(button->height());
    setWidth(4*button->width());
    stackHorizontally();
}

void eEventWidget::clear() {
    removeChildren();
}

void eEventWidget::setViewTileHandler(const eViewTileHandler& h) {
    mViewTileHandler = h;
}

eEventButton::eEventButton(const eEvent e,
                           eMainWindow* const window) :
    eButton(window) {
    const auto intrfc = eGameTextures::interface();
    int icoll;
    switch(resolution().uiScale()) {
    case eUIScale::small:
        icoll = 0;
        break;
    case eUIScale::medium:
        icoll = 1;
        break;
    default:
        icoll = 2;
    }
    const auto& texs = intrfc[icoll];
    const eTextureCollection* coll = nullptr;
    switch(e) {
    case eEvent::fire:
        coll = &texs.fFireAlert;
        break;
    case eEvent::collapse:
        coll = &texs.fCollapseAltert;
        break;

    case eEvent::aphroditeVisit:
    case eEvent::apolloVisit:
    case eEvent::aresVisit:
    case eEvent::artemisVisit:
    case eEvent::athenaVisit:
    case eEvent::atlasVisit:
    case eEvent::demeterVisit:
    case eEvent::dionysusVisit:
    case eEvent::hadesVisit:
    case eEvent::hephaestusVisit:
    case eEvent::heraVisit:
    case eEvent::hermesVisit:
    case eEvent::poseidonVisit:
    case eEvent::zeusVisit:
        coll = &texs.fGodVisitAlert;
        break;

    case eEvent::aphroditeInvasion:
    case eEvent::apolloInvasion:
    case eEvent::aresInvasion:
    case eEvent::artemisInvasion:
    case eEvent::athenaInvasion:
    case eEvent::atlasInvasion:
    case eEvent::demeterInvasion:
    case eEvent::dionysusInvasion:
    case eEvent::hadesInvasion:
    case eEvent::hephaestusInvasion:
    case eEvent::heraInvasion:
    case eEvent::hermesInvasion:
    case eEvent::poseidonInvasion:
    case eEvent::zeusInvasion:
        coll = &texs.fGodAttackAlert;
        break;
    default:
        return;
    }

    setTexture(coll->getTexture(0));
    setHoverTexture(coll->getTexture(1));
    setPressedTexture(coll->getTexture(2));

    setNoPadding();
    fitContent();
}
