#include "egymnast.h"

eGymnast::eGymnast(std::vector<eCharacterTextures>& tex) :
    mTextures(tex) {

}

void eGymnast::setAction(const eGymnastAction a) {
    mAction = a;
    mActionStartTime = textureTime();
}

eTexture eGymnast::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& gym = mTextures[id].fGymnast;
    const eTextureCollection* coll = nullptr;
    if(mAction == eGymnastAction::walk) {
        const int oid = static_cast<int>(orientation());
        coll = &gym.fWalk[oid];
    } else if(mAction == eGymnastAction::die) {
        coll = &gym.fDie;
    }
    if(!coll) return eTexture();
    const int t = textureTime() - mActionStartTime;
    return coll->getTexture(t % coll->size());
}
