#include "eeventwidget.h"

#include "engine/egameboard.h"
#include "engine/eevent.h"
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
    const auto uiScale = resolution().uiScale();
    const int iRes = static_cast<int>(uiScale);
    const auto& texs = intrfc[iRes];
    const eTextureCollection* coll = nullptr;
    switch(e) {
    case eEvent::fire:
        coll = &texs.fFireAlert;
        break;
    case eEvent::collapse:
        coll = &texs.fCollapseAltert;
        break;

    case eEvent::godVisit:
        coll = &texs.fGodVisitAlert;
        break;

    case eEvent::godInvasion:
        coll = &texs.fGodAttackAlert;
        break;
    case eEvent::calydonianBoarInvasion:
    case eEvent::cerberusInvasion:
    case eEvent::chimeraInvasion:
    case eEvent::cyclopsInvasion:
    case eEvent::dragonInvasion:
    case eEvent::echidnaInvasion:
    case eEvent::harpiesInvasion:
    case eEvent::hectorInvasion:
    case eEvent::hydraInvasion:
    case eEvent::krakenInvasion:
    case eEvent::maenadsInvasion:
    case eEvent::medusaInvasion:
    case eEvent::minotaurInvasion:
    case eEvent::scyllaInvasion:
    case eEvent::sphinxInvasion:
    case eEvent::talosInvasion:
        coll = &texs.fMonsterAltert;
        break;
    case eEvent::achillesArrival:
    case eEvent::atalantaArrival:
    case eEvent::bellerophonArrival:
    case eEvent::herculesArrival:
    case eEvent::jasonArrival:
    case eEvent::odysseusArrival:
    case eEvent::perseusArrival:
    case eEvent::theseusArrival:
        coll = &texs.fHeroArrivalAlert;
        break;
    case eEvent::invasion:
        coll = &texs.fInvasionAlert;
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
