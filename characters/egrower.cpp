#include "egrower.h"

#include "textures/egametextures.h"

eGrower::eGrower(eGameBoard& board) :
    eCharacter(board, eCharacterType::grower) {

}

void eGrower::incGrapes() {
    mGrapes++;
}

void eGrower::incOlives() {
    mOlives++;
}

std::shared_ptr<eTexture> eGrower::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& texs = eGameTextures::characters();
    const auto& charTexs = texs[id].fGrower;
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
    const int s = coll->size();
    if(!coll || s == 0) return std::shared_ptr<eTexture>();
    int t = textureTime() - actionStartTime();
    if(!wrap) t = std::clamp(t, 0, s - 1);
    const int texId = t % s;
    return coll->getTexture(texId);
}
