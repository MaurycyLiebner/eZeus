#include "ebuildingwithresource.h"
#include "characters/ecarttransporter.h"

#include "characters/actions/ecarttransporteraction.h"
#include "characters/actions/efollowaction.h"

stdptr<eCartTransporter> eBuildingWithResource::spawnCart(
        const eCartActionTypeSupport s) {
    const auto t = centerTile();
    auto& board = getBoard();

    const auto c = e::make_shared<eCartTransporter>(board);
    c->changeTile(t);

    const auto a = e::make_shared<eCartTransporterAction>(
                       c.get(), this);
    c->setAction(a);
    c->setSupport(s);
    return c.get();
}
