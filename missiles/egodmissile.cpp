#include "egodmissile.h"

#include "textures/egametextures.h"
#include "characters/heroes/ehero.h"

eGodMissile::eGodMissile(eGameBoard& board,
                         const std::vector<ePathPoint>& path) :
    eMissile(board, eMissileType::god, path) {}

std::shared_ptr<eTexture>
eGodMissile::getTexture(const eTileSize size) const {
    using eTexPtr = eTextureCollection eDestructionTextures::*;
    eTexPtr texptr;
    if(mActionType == eCharacterActionType::bless) {
        eGameTextures::loadBless();
        texptr = &eDestructionTextures::fBless;
    } else if(mActionType == eCharacterActionType::curse) {
        eGameTextures::loadCurse();
        texptr = &eDestructionTextures::fCurse;
    } else {
        switch(mCharType) {
        case eCharacterType::aphrodite:
        case eCharacterType::apollo:
        case eCharacterType::ares:
        case eCharacterType::artemis:
        case eCharacterType::athena:
        case eCharacterType::atlas:
        case eCharacterType::demeter:
        case eCharacterType::dionysus:
        case eCharacterType::hades:
        case eCharacterType::hephaestus:
        case eCharacterType::hera:
        case eCharacterType::hermes:
        case eCharacterType::poseidon:
        case eCharacterType::zeus: {
            const auto gt = eGod::sCharacterToGodType(mCharType);
            texptr = eGod::sGodMissile(gt);
        } break;
        case eCharacterType::atalanta: {
            const auto ht = eHero::sCharacterToHeroType(mCharType);
            texptr = eHero::sHeroMissile(ht);
        } break;
        default:
            eGameTextures::loadMonsterMissile();
            texptr = &eDestructionTextures::fMonsterMissile;
        }
    }

    const int id = static_cast<int>(size);
    const auto& textures = eGameTextures::destrution();
    const auto& coll = textures[id].*texptr;
    const double a = angle();
    const auto o = sAngleOrientation(a);
    const int texId = static_cast<int>(o) + 8*textureTime();
    return coll.getTexture(texId % coll.size());
}

void eGodMissile::setTexture(const eCharacterType ct,
                             const eCharacterActionType cat) {
    mCharType = ct;
    mActionType = cat;
}

void eGodMissile::read(eReadStream& src) {
    eMissile::read(src);
    src >> mCharType;
    src >> mActionType;
}

void eGodMissile::write(eWriteStream& dst) const {
    eMissile::write(dst);
    dst << mCharType;
    dst << mActionType;
}
