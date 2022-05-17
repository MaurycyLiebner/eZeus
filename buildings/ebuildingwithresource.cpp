#include "ebuildingwithresource.h"
#include "characters/ecarttransporter.h"

#include "characters/actions/ecarttransporteraction.h"
#include "characters/actions/efollowaction.h"

bool eBuildingWithResource::spawnCart(
        stdsptr<eCartTransporter>& cart) {
    const auto t = centerTile();
    auto& board = getBoard();

    cart = e::make_shared<eCartTransporter>(board);
    cart->changeTile(t);

    const eStdPointer<eBuildingWithResource> tptr(this);
    const auto finishAct = [tptr, &cart] {
        if(!tptr) return;
        if(cart) {
            cart->changeTile(nullptr);
            cart.reset();
        }
    };
    const auto a = e::make_shared<eCartTransporterAction>(
                       this, cart.get(),
                       finishAct, finishAct);
    cart->setAction(a);
    return true;
}
