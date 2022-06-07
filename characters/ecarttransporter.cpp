#include "ecarttransporter.h"

#include "textures/egametextures.h"

#include "characters/actions/efollowaction.h"
#include "etrailer.h"
#include "eox.h"

eCartTransporter::eCartTransporter(eGameBoard& board) :
    eBasicPatroler(board, &eCharacterTextures::fTransporter,
                   eCharacterType::cartTransporter) {
    setHasSecondaryTexture(true);
}

eOverlay eCartTransporter::getSecondaryTexture(const eTileSize size) const {
    if(mIsOx) return eBasicPatroler::getSecondaryTexture(size);
    const auto a = actionType();
    if(a == eCharacterActionType::none) {
        return eOverlay{0, 0, std::shared_ptr<eTexture>()};
    }
    const int id = static_cast<int>(size);
    const auto& texs = eGameTextures::characters()[id];
    const int oi = static_cast<int>(orientation());

    int ci = 0;

    const auto rType = resType();
    const int rCount = resCount();

    switch(rType) {
    case eResourceType::urchin:
    case eResourceType::fish:
    case eResourceType::meat:
    case eResourceType::cheese:
    case eResourceType::carrots:
    case eResourceType::onions:
    case eResourceType::wheat:
    case eResourceType::oranges:

    case eResourceType::grapes:
    case eResourceType::olives:
        ci = std::clamp(rCount/4, 0, 2);
        break;
    case eResourceType::wine:
    case eResourceType::oliveOil:
    case eResourceType::fleece:
    case eResourceType::bronze:
    case eResourceType::armor:
        ci = std::clamp(rCount/4, 0, 1);
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

    std::shared_ptr<eTexture> tex;
    if(rCount <= 0) {
        tex = texs.fEmptyCart.getTexture(oi);
    } else {
        switch(rType) {
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
        case eResourceType::oranges:
            tex = texs.fOrangesCart[oi].getTexture(ci);
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
        case eResourceType::food:
            tex = texs.fFoodCart[oi].getTexture(0);
            break;
        default:
            tex = texs.fEmptyCart.getTexture(oi);
            break;
        }
    }
    return {xx, yy, tex};
}

void eCartTransporter::setIsOx(const bool o) {
    if(mIsOx == o) return;
    mIsOx = o;
    if(mIsOx) {
        setCharTextures(&eCharacterTextures::fOxHandler);

        const auto t = tile();
        auto& board = getBoard();

        mOx = e::make_shared<eOx>(board);
        const auto aox = e::make_shared<eFollowAction>(
                           this, mOx.get(),
                           []() {}, []() {});
        mOx->setAction(aox);
        mOx->changeTile(t);
        mTrailer = e::make_shared<eTrailer>(this, board);
        mTrailer->setBig(mBigTrailer);
        const auto atr = e::make_shared<eFollowAction>(
                           mOx.get(), mTrailer.get(),
                           []() {}, []() {});
        mTrailer->setAction(atr);
        mTrailer->changeTile(t);
    } else {
        setCharTextures(&eCharacterTextures::fTransporter);

        mOx->kill();
        mOx.reset();

        mTrailer->kill();
        mTrailer.reset();
    }
}

void eCartTransporter::setBigTrailer(const bool b) {
    mBigTrailer = b;
    if(mTrailer) mTrailer->setBig(b);
}

void eCartTransporter::setResource(const eResourceType type,
                                   const int count) {
    mResourceType = type;
    mResourceCount = count;

    switch(mResourceType) {
    case eResourceType::marble:
    case eResourceType::wood:
    case eResourceType::sculpture:
        setIsOx(true);
        break;
    default:
        setIsOx(false);
    }
}

int eCartTransporter::add(const eResourceType type, const int count) {
    if(count <= 0) return 0;
    const bool comp = mResourceType == type ||
                      mResourceCount <= 0;
    if(!comp) return 0;
    const int maxResource = eResourceTypeHelpers::transportSize(type);
    const int r = std::clamp(mResourceCount + count, 0, maxResource);
    const int result = r - mResourceCount;
    setResource(type, r);
    return result;
}

int eCartTransporter::take(const eResourceType type, const int count) {
    if(count <= 0) return 0;
    if(type != mResourceType) return 0;

    const int result = std::clamp(count, 0, mResourceCount);
    setResource(type, mResourceCount - result);
    return result;
}

void eCartTransporter::setActionType(const eCharacterActionType t) {
    eCharacterBase::setActionType(t);
    if(mOx) mOx->setActionType(t);
}
