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
    const int resCount = mFollow ? mFollow->resCount() : mResCount;
    const auto resType = mFollow ? mFollow->resType() : mResType;
    mResCount = resCount;
    mResType = resType;
    if(resCount <= 0) {
        if(mIsBig) {
            coll = &charTexs.fEmptyBigTrailer;
        } else {
            coll = &charTexs.fEmptyTrailer;
        }
    } else {
        switch(resType) {
        case eResourceType::marble: {
            if(mIsBig) {
                coll = &charTexs.fMarbleBigTrailer;
            } else {
                if(resCount >= 4) {
                    coll = &charTexs.fMarbleTrailer2;
                } else {
                    coll = &charTexs.fMarbleTrailer1;
                }
            }
        } break;
        case eResourceType::wood: {
            if(resCount >= 8) {
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

void eTrailer::read(eReadStream& src) {
    eCharacter::read(src);
    src.readCharacter(&getBoard(), [this](eCharacter* const c) {
        mFollow = static_cast<eCartTransporter*>(c);
    });
    src >> mIsBig;
    src >> mResCount;
    src >> mResType;
}

void eTrailer::write(eWriteStream& dst) const {
    eCharacter::write(dst);
    dst.writeCharacter(mFollow);
    dst << mIsBig;
    dst << mResCount;
    dst << mResType;
}
