#include "ebuildingwithresource.h"

#include "characters/actions/ecarttransporteraction.h"

bool eBuildingWithResource::spawnGiveCart(
        stdsptr<eCartTransporter>& cart,
        int& spawnTime, const int waitTime,
        const eResourceType resType) {
    if(count(resType) <= 0) return false;
    cart = e::make_shared<eCartTransporter>(getBoard());
    const auto t = tile();
    cart->changeTile(t);

    const eStdPointer<eBuildingWithResource> tptr(this);
    const eStdPointer<eCartTransporter> hptr(cart);
    const auto foundAct = [tptr, this, hptr, resType] {
        if(!tptr || !hptr) return;
        const int took = take(resType, 8);
        hptr->setResource(resType, took);
    };
    const auto finishAct = [tptr, this, hptr,
                            &cart, &spawnTime, waitTime]() {
        if(hptr) {
            hptr->changeTile(nullptr);
        }
        if(tptr) {
            cart.reset();
            spawnTime = time() + waitTime;
        }
    };
    const auto failAct = [hptr, tptr, this, finishAct]() {
        if(!hptr || !tptr) return;
        add(hptr->resourceType(), hptr->resourceCount());
        finishAct();
    };
    const auto a = e::make_shared<eCartTransporterAction>(
                       this, cart.get(),
                       eCartActionType::give, resType,
                       foundAct, failAct, finishAct);
    cart->setAction(a);
    return true;
}

bool eBuildingWithResource::depositFromCart(
        stdsptr<eCartTransporter>& cart,
        int& spawnTime, const int waitTime) {
    if(!cart) return false;
    const auto resType = cart->resourceType();
    if(spaceLeft(resType) <= 0) return false;
    const int count = cart->resourceCount();
    const int added = add(resType, count);
    cart->setResource(resType, count - added);
    const int newCount = cart->resourceCount();
    if(newCount <= 0) {
        spawnTime = time() + waitTime;
        cart->changeTile(nullptr);
        cart.reset();
    } else {
        cart->setActionType(eCharacterActionType::stand);
    }
    return true;
}

bool eBuildingWithResource::spawnTakeCart(
        stdsptr<eCartTransporter>& cart,
        int& spawnTime, const int waitTime,
        const eResourceType resType) {
    if(cart) depositFromCart(cart, spawnTime, waitTime);
    if(spaceLeft(resType) <= 0) return false;
    const auto t = tile();
    if(!cart) cart = e::make_shared<eCartTransporter>(getBoard());
    cart->changeTile(t);
    const eStdPointer<eBuildingWithResource> tptr(this);
    const auto failAct = [tptr, this, &cart,
                         &spawnTime, waitTime] {
        if(!tptr) return;
        spawnTime = time() + waitTime;
        if(cart) {
            cart->changeTile(nullptr);
            cart.reset();
        }
    };
    const auto finishAct = [tptr, this, &cart,
                           &spawnTime, waitTime]() {
        if(!tptr) return;
        depositFromCart(cart, spawnTime, waitTime);
    };
    const auto a = e::make_shared<eCartTransporterAction>(
                       this, cart.get(),
                       eCartActionType::take,
                       resType,
                       failAct, finishAct);
    cart->setAction(a);
    return true;
}
