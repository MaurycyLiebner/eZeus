#include "ebuildingwithresource.h"

#include "characters/etrailer.h"
#include "characters/eox.h"
#include "characters/eoxhandler.h"
#include "characters/etrailer.h"

#include "characters/actions/ecarttransporteraction.h"
#include "characters/actions/efollowaction.h"

bool eBuildingWithResource::spawnGiveCart(
        stdsptr<eTransporterBase>& cart,
        int& spawnTime, const int waitTime,
        const eResourceType resType) {
    if(count(resType) <= 0) return false;
    auto& board = getBoard();
    const auto t = centerTile();
    if(resType == eResourceType::marble ||
       resType == eResourceType::wood ||
       resType == eResourceType::sculpture) {
        cart = e::make_shared<eOxHandler>(board);
        const auto ox = e::make_shared<eOx>(board);
        const auto aox = e::make_shared<eFollowAction>(
                           cart.get(), ox.get(),
                           []() {}, []() {});
        ox->setAction(aox);
        ox->changeTile(t);
        const auto tr = e::make_shared<eTrailer>(cart.get(), board);
        const auto atr = e::make_shared<eFollowAction>(
                           ox.get(), tr.get(),
                           []() {}, []() {});
        tr->setAction(atr);
        tr->changeTile(t);
    } else {
        cart = e::make_shared<eCartTransporter>(board);
    }
    cart->changeTile(t);

    const eStdPointer<eBuildingWithResource> tptr(this);
    const eStdPointer<eTransporterBase> hptr(cart);
    const auto foundAct = [tptr, this, hptr, resType] {
        if(!tptr || !hptr) return;
        int max = 8;
        if(resType == eResourceType::marble) {
            max = 4;
        } else if(resType == eResourceType::sculpture) {
            max = 1;
        }
        const int took = take(resType, max);
        hptr->setResource(resType, took);
    };
    const auto finishAct = [tptr, this, hptr,
                            &cart, &spawnTime, waitTime]() {
        if(hptr) {
            hptr->changeTile(nullptr);
        }
        if(tptr) {
            spawnTime = time() + waitTime;
            cart.reset();
        }
    };
    const auto failAct = [hptr, tptr, this, finishAct]() {
        if(!hptr || !tptr) return;
        add(hptr->resType(), hptr->resCount());
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
        stdsptr<eTransporterBase>& cart,
        int& spawnTime, const int waitTime) {
    if(!cart) return false;
    const auto resType = cart->resType();
    if(spaceLeft(resType) <= 0) return false;
    const int count = cart->resCount();
    const int added = add(resType, count);
    cart->setResource(resType, count - added);
    const int newCount = cart->resCount();
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
        stdsptr<eTransporterBase>& cart,
        int& spawnTime, const int waitTime,
        const eResourceType resType) {
    if(cart) depositFromCart(cart, spawnTime, waitTime);
    if(spaceLeft(resType) <= 0) return false;
    const auto t = centerTile();
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
