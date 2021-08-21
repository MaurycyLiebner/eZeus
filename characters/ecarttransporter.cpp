#include "ecarttransporter.h"

#include "textures/egametextures.h"

eCartTransporter::eCartTransporter(eGameBoard& board) :
    eBasicPatroler(board, &eCharacterTextures::fTransporter,
                   eCharacterType::cartTransporter) {
    setHasSecondaryTexture(true);
}

eTexture eCartTransporter::getSecondaryTexture(const eTileSize size) const {
    const int id = static_cast<int>(size);
    const auto& texs = eGameTextures::characters()[id];
    const int oi = static_cast<int>(orientation());

    int ci = 0;

    switch(mResourceType) {
    case eResourceType::urchin:
    case eResourceType::fish:
    case eResourceType::meat:
    case eResourceType::cheese:
    case eResourceType::carrots:
    case eResourceType::onions:
    case eResourceType::wheat:
    case eResourceType::grapes:
    case eResourceType::olives:
        ci = std::clamp(mResourceCount/4, 0, 2);
        break;
    case eResourceType::wine:
    case eResourceType::oliveOil:
    case eResourceType::fleece:
    case eResourceType::bronze:
    case eResourceType::armor:
        ci = std::clamp(mResourceCount/4, 0, 1);
        break;
    default: break;
    }

    if(mResourceCount <= 0) {
        return texs.fEmptyCart.getTexture(oi);
    } else {
        switch(mResourceType) {
        case eResourceType::urchin:
            return texs.fUrchinCart[oi].getTexture(ci);
        case eResourceType::fish:
            return texs.fFishCart[oi].getTexture(ci);
        case eResourceType::meat:
            return texs.fMeatCart[oi].getTexture(ci);
        case eResourceType::cheese:
            return texs.fCheeseCart[oi].getTexture(ci);
        case eResourceType::carrots:
            return texs.fCarrotsCart[oi].getTexture(ci);
        case eResourceType::onions:
            return texs.fOnionsCart[oi].getTexture(ci);
        case eResourceType::wheat:
            return texs.fWheatCart[oi].getTexture(ci);
        case eResourceType::grapes:
            return texs.fGrapesCart[oi].getTexture(ci);
        case eResourceType::olives:
            return texs.fOlivesCart[oi].getTexture(ci);
        case eResourceType::wine:
            return texs.fWineCart[oi].getTexture(ci);
        case eResourceType::oliveOil:
            return texs.fOliveOilCart[oi].getTexture(ci);
        case eResourceType::fleece:
            return texs.fFleeceCart[oi].getTexture(ci);
        case eResourceType::bronze:
            return texs.fBronzeCart[oi].getTexture(ci);
        case eResourceType::armor:
            return texs.fArmorCart[oi].getTexture(ci);
        default:
            return texs.fEmptyCart.getTexture(oi);
        }
    }
}

void eCartTransporter::setResource(const eResourceType type,
                                   const int count) {
    mResourceType = type;
    mResourceCount = count;
}
