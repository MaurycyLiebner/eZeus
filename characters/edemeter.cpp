#include "edemeter.h"

#include "engine/etile.h"
#include "textures/egametextures.h"

eDemeter::eDemeter(eGameBoard& board) :
    eCharacter(board), mTextures(eGameTextures::demeter()) {

}

eTexture eDemeter::getTexture(const eTileSize size) const {
    if(mAction == eDemeterAction::walk) {
        const int id = static_cast<int>(size);
        const int oid = static_cast<int>(orientation());
        const auto& coll = mTextures[id].fWalk[oid];
        return coll.getTexture(textureTime() % coll.size());
    }
    return eTexture();
}
