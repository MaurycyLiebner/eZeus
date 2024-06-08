#include "ecarttransporter.h"

#include "textures/egametextures.h"

#include "characters/actions/efollowaction.h"
#include "engine/egameboard.h"
#include "etrailer.h"
#include "eox.h"
#include "eporter.h"
#include "ehorse.h"
#include "echariot.h"

eCartTransporter::eCartTransporter(eGameBoard& board) :
    eBasicPatroler(board, &eCharacterTextures::fTransporter,
                   eCharacterType::cartTransporter) {
    eGameTextures::loadTransporter();
    eGameTextures::loadCart();
    setHasSecondaryTexture(true);
}

eCartTransporter::~eCartTransporter() {
    if(mOx) mOx->kill();
    if(mTrailer) mTrailer->kill();
    for(const auto& f : mFollowers) {
        if(f) f->kill();
    }
}

eOverlay eCartTransporter::getSecondaryTexture(const eTileSize size) const {
    if(mType != eCartTransporterType::basic) {
        return eBasicPatroler::getSecondaryTexture(size);
    }
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
        default:
            tex = texs.fEmptyCart.getTexture(oi);
            break;
        }
    }
    return {xx, yy, tex};
}

void eCartTransporter::setType(const eCartTransporterType t) {
    if(mType == t) return;
    mType = t;
    updateTextures();
    if(mOx) mOx->kill();
    if(mTrailer) mTrailer->kill();
    if(mType == eCartTransporterType::ox) {
        const auto t = tile();
        auto& board = getBoard();

        eCharacter* follow = this;

        if(!board.poseidonMode()) {
            mOx = e::make_shared<eOx>(board);
            const auto aox = e::make_shared<eFollowAction>(follow, mOx.get());
            mOx->setAction(aox);
            mOx->changeTile(t);
            follow = mOx.get();
        }

        mTrailer = e::make_shared<eTrailer>(board);
        mTrailer->setFollow(this);
        mTrailer->setBig(mBigTrailer);
        const auto atr = e::make_shared<eFollowAction>(follow, mTrailer.get());
        mTrailer->setAction(atr);
        mTrailer->changeTile(t);
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

    if(mType == eCartTransporterType::ox ||
       mType == eCartTransporterType::basic) {
        switch(mResourceType) {
        case eResourceType::marble:
        case eResourceType::wood:
        case eResourceType::sculpture:
            setType(eCartTransporterType::ox);
            break;
        default:
            setType(eCartTransporterType::basic);
        }
    }
    switch(mType) {
    case eCartTransporterType::food:
    case eCartTransporterType::fleece:
    case eCartTransporterType::oil:
    case eCartTransporterType::wine:
    case eCartTransporterType::arms:
    case eCartTransporterType::horse:
    case eCartTransporterType::chariot: {
        const auto chr = eCartTransporterType::chariot;
        const int nFollPerRes = mType == chr ? 2 : 1;
        {
            const int iMax = mFollowers.size();
            for(int i = count*nFollPerRes; i < iMax; i++) {
                const auto f = mFollowers.back();
                mFollowers.pop_back();
                f->kill();
            }
        }
        const int iMax = count - mFollowers.size()/nFollPerRes;
        for(int i = 0; i < iMax; i++) {
            eCharacter* follow;
            if(mFollowers.empty()) {
                follow = this;
            } else {
                follow = mFollowers.back().get();
            }

            const auto t = tile();
            auto& board = getBoard();

            stdsptr<eCharacter> follower;
            if(mType == eCartTransporterType::horse) {
                follower = e::make_shared<eHorse>(board);
            } else if(mType == eCartTransporterType::chariot) {
                follower = e::make_shared<eHorse>(board);
                const auto aox = e::make_shared<eFollowAction>(
                                   follow, follower.get());
                follower->setAction(aox);
                follower->changeTile(t);
                mFollowers.push_back(follower);
                follow = follower.get();

                follower = e::make_shared<eChariot>(board);
            } else {
                follower = e::make_shared<ePorter>(board);
            }
            const auto aox = e::make_shared<eFollowAction>(
                               follow, follower.get());
            follower->setAction(aox);
            follower->changeTile(t);
            mFollowers.push_back(follower);
        }
    } break;
    default: break;
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

void eCartTransporter::read(eReadStream& src) {
    eBasicPatroler::read(src);
    src >> mResourceCount;
    src >> mType;
    src >> mResourceType;
    src >> mSupports;
    src >> mSupport;
    src >> mWaiting;
    src >> mIsOx;
    src >> mBigTrailer;
    src.readCharacter(&getBoard(), [this](eCharacter* const c) {
        mOx = static_cast<eOx*>(c);
    });
    src.readCharacter(&getBoard(), [this](eCharacter* const c) {
        mTrailer = static_cast<eTrailer*>(c);
    });
    int nf;
    src >> nf;
    for(int i = 0; i < nf; i++) {
        src.readCharacter(&getBoard(), [this](eCharacter* const c) {
            if(!c) return;
            mFollowers.push_back(c);
        });
    }
    updateTextures();
}

void eCartTransporter::write(eWriteStream& dst) const {
    eBasicPatroler::write(dst);
    dst << mResourceCount;
    dst << mType;
    dst << mResourceType;
    dst << mSupports;
    dst << mSupport;
    dst << mWaiting;
    dst << mIsOx;
    dst << mBigTrailer;
    dst.writeCharacter(mOx);
    dst.writeCharacter(mTrailer);

    dst << mFollowers.size();
    for(const auto& f : mFollowers) {
        dst.writeCharacter(f);
    }
}

void eCartTransporter::updateTextures() {
    switch(mType) {
    case eCartTransporterType::basic: {
        eGameTextures::loadTransporter();
        eGameTextures::loadCart();
        setCharTextures(&eCharacterTextures::fTransporter);
    } break;
    case eCartTransporterType::ox: {
        auto& board = getBoard();
        if(board.poseidonMode()) {
            eGameTextures::loadElephant();
            setCharTextures(&eCharacterTextures::fElephant);
        } else {
            eGameTextures::loadOxHandler();
            setCharTextures(&eCharacterTextures::fOxHandler);
        }
    } break;
    case eCartTransporterType::food: {
        eGameTextures::loadFoodVendor();
        setCharTextures(&eCharacterTextures::fFoodVendor);
    } break;
    case eCartTransporterType::fleece: {
        eGameTextures::loadFleeceVendor();
        setCharTextures(&eCharacterTextures::fFleeceVendor);
    } break;
    case eCartTransporterType::oil: {
        eGameTextures::loadOilVendor();
        setCharTextures(&eCharacterTextures::fOilVendor);
    } break;
    case eCartTransporterType::wine: {
        eGameTextures::loadWineVendor();
        setCharTextures(&eCharacterTextures::fWineVendor);
    } break;
    case eCartTransporterType::arms: {
        eGameTextures::loadArmsVendor();
        setCharTextures(&eCharacterTextures::fArmsVendor);
    } break;
    case eCartTransporterType::horse: {
        eGameTextures::loadHorseVendor();
        setCharTextures(&eCharacterTextures::fHorseVendor);
    } break;
    case eCartTransporterType::chariot: {
        eGameTextures::loadChariotVendorCharacter();
        setCharTextures(&eCharacterTextures::fChariotVendor);
    } break;
    }
}
