#include "ecalydonianboar.h"

#include "textures/egametextures.h"

eCalydonianBoar::eCalydonianBoar(eGameBoard& board) :
    eMonster(board, eMonsterType::calydonianBoar) {}

std::shared_ptr<eTexture>
eCalydonianBoar::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& monsterTexs = eGameTextures::characters()[id];
    const auto& texs = monsterTexs.fCalydonianBoar;
    const eTextureCollection* coll = nullptr;
    bool reverse = false;
    bool wrap = true;
    const int oid = static_cast<int>(orientation());
    const auto a = actionType();
    switch(a) {
    case eCharacterActionType::stand:
        return texs.fWalk[oid].getTexture(0);
    case eCharacterActionType::collect:
    case eCharacterActionType::fight:
    case eCharacterActionType::bless: {
        wrap = true;
        coll = &texs.fFight[oid];
    } break;
    case eCharacterActionType::carry:
    case eCharacterActionType::walk: {
        coll = &texs.fWalk[oid];
    } break;
    case eCharacterActionType::disappear:
    case eCharacterActionType::die:
        wrap = false;
        coll = &texs.fDie[oid];
        break;
    default:
        return std::shared_ptr<eTexture>();
    }

    const int s = coll->size();
    if(!coll || s == 0) return std::shared_ptr<eTexture>();
    int t = textureTime() - actionStartTime();
    if(reverse) {
        t = coll->size() - t;
    }
    if(!wrap) t = std::clamp(t, 0, s - 1);
    const int texId = t % s;
    return coll->getTexture(texId);
}
