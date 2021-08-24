#include "ecarttransporter.h"

#include "textures/egametextures.h"

eCartTransporter::eCartTransporter(eGameBoard& board) :
    eBasicPatroler(board, &eCharacterTextures::fTransporter,
                   eCharacterType::cartTransporter) {
    setHasSecondaryTexture(true);
}

eOverlay eCartTransporter::getSecondaryTexture(const eTileSize size) const {
    const auto a = actionType();
    if(a == eCharacterActionType::none) {
        return eOverlay{0, 0, eTexture()};
    }
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

    double xx;
    double yy;
    switch(orientation()) {
    case eOrientation::topRight:
        xx = 0.25;
        yy = -0.60;
        break;
    case eOrientation::right:
        xx = 0.75;
        yy = -0.25;
        break;
    case eOrientation::bottomRight:
        xx = 0.85;
        yy = 0.15;
        break;
    case eOrientation::bottom:
        xx = 0.75;
        yy = 0.75;
        break;
    case eOrientation::bottomLeft:
        xx = 0.15;
        yy = 0.85;
        break;
    case eOrientation::left:
        xx = -0.25;
        yy = 0.75;
        break;
    case eOrientation::topLeft:
        xx = -0.75;
        yy = 0.1;
        break;
    case eOrientation::top:
        xx = -0.25;
        yy = -0.25;
        break;
    }

    eTexture tex;
    if(mResourceCount <= 0) {
        tex = texs.fEmptyCart.getTexture(oi);
    } else {
        switch(mResourceType) {
        case eResourceType::urchin:
            tex = texs.fUrchinCart[oi].getTexture(ci);
            break;
        case eResourceType::fish:
            tex = texs.fFishCart[oi].getTexture(ci);
            break;
        case eResourceType::meat:
            tex = texs.fMeatCart[oi].getTexture(ci);
            break;
        case eResourceType::cheese:
            tex = texs.fCheeseCart[oi].getTexture(ci);
            break;
        case eResourceType::carrots:
            tex = texs.fCarrotsCart[oi].getTexture(ci);
            break;
        case eResourceType::onions:
            tex = texs.fOnionsCart[oi].getTexture(ci);
            break;
        case eResourceType::wheat:
            tex = texs.fWheatCart[oi].getTexture(ci);
            break;
        case eResourceType::grapes:
            tex = texs.fGrapesCart[oi].getTexture(ci);
            break;
        case eResourceType::olives:
            tex = texs.fOlivesCart[oi].getTexture(ci);
            break;
        case eResourceType::wine:
            tex = texs.fWineCart[oi].getTexture(ci);
            break;
        case eResourceType::oliveOil:
            tex = texs.fOliveOilCart[oi].getTexture(ci);
            break;
        case eResourceType::fleece:
            tex = texs.fFleeceCart[oi].getTexture(ci);
            break;
        case eResourceType::bronze:
            tex = texs.fBronzeCart[oi].getTexture(ci);
            break;
        case eResourceType::armor:
            tex = texs.fArmorCart[oi].getTexture(ci);
            break;
        default:
            tex = texs.fEmptyCart.getTexture(oi);
            break;
        }
    }
    return {xx, yy, tex};
}

void eCartTransporter::setResource(const eResourceType type,
                                   const int count) {
    mResourceType = type;
    mResourceCount = count;
}
