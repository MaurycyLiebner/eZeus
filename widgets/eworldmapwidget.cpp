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
