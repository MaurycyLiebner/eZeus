#include "edemeter.h"

#include "engine/etile.h"

eDemeter::eDemeter(std::vector<eDemeterTextures>& texs) :
    mTextures(texs) {

}

eTexture eDemeter::getTexture(const eTileSize size) const {
    if(mAction == eDemeterAction::walk) {
        const int id = static_cast<int>(size);
        const int oid = static_cast<int>(mOrientation);
        const auto& coll = mTextures[id].fWalk[oid];
        return coll.getTexture((mTime/4) % coll.size());
    }
    return eTexture();
}

void eDemeter::setTile(eTile* const t) {
    mTile = t;
}

void eDemeter::incTime() {
    mTime++;
    if(mCharAction) mCharAction->increment();
}

void eDemeter::setOrientation(const eOrientation o) {
    mOrientation = o;
}

void eDemeter::setCharAction(eCharacterAction* const a) {
    mCharAction = a;
}
