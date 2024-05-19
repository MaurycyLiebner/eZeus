#include "egrower.h"

#include "textures/egametextures.h"

eGrower::eGrower(eGameBoard& board) :
    eCharacter(board, eCharacterType::grower) {
    eGameTextures::loadGrower();
}

void eGrower::incGrapes(const int i) {
    mGrapes += i;
}

void eGrower::incOlives(const int i) {
    mOlives += i;
}

void eGrower::incOranges(const int i) {
    mOranges += i;
}

std::shared_ptr<eTexture> eGrower::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& texs = eGameTextures::characters();
    const auto& colls = texs[id];
    switch(mType) {
    case eGrowerType::grapesAndOlives:
        return getGrapesAndOlivesTex(colls);
    case eGrowerType::oranges:
        return getOrangesTex(colls);
    }
    return nullptr;
}

std::shared_ptr<eTexture> eGrower::getGrapesAndOlivesTex(
        const eCharacterTextures& texs) const {
    const auto& charTexs = texs.fGrower;
    const eTextureCollection* coll = nullptr;
    const int oid = static_cast<int>(orientation());
    bool wrap = true;
    const auto a = actionType();
    switch(a) {
    case eCharacterActionType::stand:
        return charTexs.fWalk[oid].getTexture(0);
    case eCharacterActionType::workOnGrapes:
        coll = &charTexs.fWorkOnGrapes[oid];
        break;
    case eCharacterActionType::fight:
    case eCharacterActionType::workOnOlives:
        coll = &charTexs.fWorkOnOlives[oid];
        break;
    case eCharacterActionType::collectGrapes:
        coll = &charTexs.fCollectGrapes[oid];
        break;
    case eCharacterActionType::collectOlives:
        coll = &charTexs.fCollectOlives[oid];
        break;
    case eCharacterActionType::carry:
    case eCharacterActionType::walk:
        coll = &charTexs.fWalk[oid];
        break;
    case eCharacterActionType::die:
        wrap = false;
        coll = &charTexs.fDie;
        break;
    default: return std::shared_ptr<eTexture>();
    }

    return eCharacter::getTexture(coll, wrap, false);
}

std::shared_ptr<eTexture> eGrower::getOrangesTex(
        const eCharacterTextures& texs) const {
    const auto& charTexs = texs.fOrangeTender;
    const eTextureCollection* coll = nullptr;
    const int oid = static_cast<int>(orientation());
    bool wrap = true;
    const auto a = actionType();
    switch(a) {
    case eCharacterActionType::stand:
        return charTexs.fWalk[oid].getTexture(0);
    case eCharacterActionType::fight:
    case eCharacterActionType::workOnOranges:
        coll = &charTexs.fWorkOnTree[oid];
        break;
    case eCharacterActionType::collectOranges:
        coll = &charTexs.fCollect[oid];
        break;
    case eCharacterActionType::carry:
    case eCharacterActionType::walk:
        coll = &charTexs.fWalk[oid];
        break;
    case eCharacterActionType::die:
        wrap = false;
        coll = &charTexs.fDie;
        break;
    default:
        return nullptr;
    }

    return eCharacter::getTexture(coll, wrap, false);
}
