#include "etrailer.h"

#include "textures/egametextures.h"

eTrailer::eTrailer(eGameBoard& board) :
    eCharacter(board, eCharacterType::trailer) {}

std::shared_ptr<eTexture>
eTrailer::getTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& charTexs = eGameTextures::characters()[id];
    const int oid = static_cast<int>(orientation());
    const eTextureCollection* coll = nullptr;
    if(mResourceCount <= 0) {
        if(mIsBig) {
            coll = &charTexs.fEmptyBigTrailer;
        } else {
            coll = &charTexs.fEmptyTrailer;
        }
    } else {
        switch(mResourceType) {
        case eResourceType::marble: {
            if(mIsBig) {
                coll = &charTexs.fMarbleBigTrailer;
            } else {
                if(mResourceCount >= 4) {
                    coll = &charTexs.fMarbleTrailer2;
                } else {
                    coll = &charTexs.fMarbleTrailer1;
                }
            }
        } break;
        case eResourceType::wood: {
            if(mResourceCount >= 8) {
                coll = &charTexs.fWoodTrailer2;
            } else {
                coll = &charTexs.fWoodTrailer1;
            }
        } break;
        case eResourceType::sculpture: {
            coll = &charTexs.fSculptureTrailer;
        } break;
        default: {
            if(mIsBig) {
                coll = &charTexs.fEmptyBigTrailer;
            } else {
                coll = &charTexs.fEmptyTrailer;
            }
        }
        }
    }

    return coll->getTexture(oid);
}

void eTrailer::setResource(const eResourceType type,
                           const int count) {
    mResourceType = type;
    mResourceCount = count;
}
