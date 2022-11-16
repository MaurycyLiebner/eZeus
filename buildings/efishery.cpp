#include "efishery.h"

#include "characters/efishingboat.h"
#include "characters/actions/ecollectresourceaction.h"
#include "textures/egametextures.h"

eFishery::eFishery(eGameBoard& board, const eOrientation o) :
    eResourceCollectBuildingBase(board, eBuildingType::fishery,
                                 2, 2, 10, eResourceType::fish),
    mO(o) {}

eFishery::~eFishery() {
    if(mBoat) mBoat->kill();
}

const int gUnpackTime = 5000;

void eFishery::timeChanged(const int by) {
    if(enabled()) {
        mStateCount += by;
        switch(mState) {
        case eFisheryState::buildingBoat: {
            const int buildTime = 5000;
            if(mStateCount > buildTime) {
                mStateCount -= buildTime;
                mState = eFisheryState::waiting;
                spawnBoat();
            }
        } break;
        case eFisheryState::unpacking: {
            if(mStateCount > gUnpackTime) {
                mStateCount -= gUnpackTime;
                mState = eFisheryState::waiting;
                eResourceBuildingBase::add(eResourceType::fish, 3);
                updateDisabled();
            }
        } break;
        default: break;
        }
    }
    eResourceBuildingBase::timeChanged(by);
}

std::shared_ptr<eTexture> eFishery::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings();
    const auto& coll = blds[sizeId].fFishery;
    int id = 3;
    switch(mO) {
    case eOrientation::topRight:
        id = 0;
        break;
    case eOrientation::bottomRight:
        id = 1;
        break;
    case eOrientation::bottomLeft:
        id = 2;
        break;
    case eOrientation::topLeft:
        id = 3;
        break;
    default:
        id = 0;
        break;
    }

    return coll.getTexture(id);
}

std::vector<eOverlay> eFishery::getOverlays(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings()[sizeId];
    switch(mState) {
    case eFisheryState::buildingBoat: {
        eOverlay o;
        const eTextureCollection* coll;
        switch(mO) {
        case eOrientation::topRight:
            coll = &blds.fFisheryBoatBuildingH;
            o.fX = 0.2;
            o.fY = -2.25;
            break;
        case eOrientation::bottomLeft:
            coll = &blds.fFisheryBoatBuildingH;
            o.fX = -0.3;
            o.fY = -2.38;
            break;
        default:
        case eOrientation::topLeft:
            coll = &blds.fFisheryBoatBuildingW;
            o.fX = 0.0;
            o.fY = -2.0;
            break;
        case eOrientation::bottomRight:
            coll = &blds.fFisheryBoatBuildingW;
            o.fX = -0.25;
            o.fY = -1.9;
            break;
        }

        const int texId = textureTime() % coll->size();
        o.fTex = coll->getTexture(texId);
        return {o};
    } break;
    case eFisheryState::waiting: {
        eOverlay o;
        const eTextureCollection* coll;
        switch(mO) {
        case eOrientation::topRight:
            coll = &blds.fFisheryOverlay[0];
            o.fX = 0.2;
            o.fY = -2.0;
            break;
        case eOrientation::bottomLeft:
            coll = &blds.fFisheryOverlay[4];
            o.fX = -0.3;
            o.fY = -2.38;
            break;
        default:
        case eOrientation::topLeft:
            coll = &blds.fFisheryOverlay[6];
            o.fX = 0.25;
            o.fY = -2.2;
            break;
        case eOrientation::bottomRight:
            coll = &blds.fFisheryOverlay[2];
            o.fX = -0.25;
            o.fY = -1.9;
            break;
        }

        const int texId = textureTime() % coll->size();
        o.fTex = coll->getTexture(texId);
        return {o};
    } break;
    case eFisheryState::unpacking: {
        eOverlay o;
        const eTextureCollection* coll;
        switch(mO) {
        case eOrientation::topRight:
            coll = &blds.fFisheryUnpackingOverlayTR;
            o.fX = -0.3;
            o.fY = -2.95;
            break;
        case eOrientation::bottomLeft:
            coll = &blds.fFisheryUnpackingOverlayBL;
            o.fX = -0.35;
            o.fY = -1.75;
            break;
        default:
        case eOrientation::topLeft:
            coll = &blds.fFisheryUnpackingOverlayTL;
            o.fX = -0.75;
            o.fY = -2.3;
            break;
        case eOrientation::bottomRight:
            coll = &blds.fFisheryUnpackingOverlayBR;
            o.fX = 0.20;
            o.fY = -2.3;
            break;
        }

        const int texId = textureTime() % coll->size();
        o.fTex = coll->getTexture(texId);
        return {o};
    } break;
    }
    return {};
}

void eFishery::addRaw() {
    mState = eFisheryState::unpacking;
    mStateCount = 0;
    if(mBoat) {
        eOrientation o;
        switch(mO) {
        case eOrientation::bottomLeft:
        case eOrientation::topRight:
            o = eOrientation::topLeft;
            break;
        default:
        case eOrientation::bottomRight:
        case eOrientation::topLeft:
            o = eOrientation::topRight;
            break;
        }
        mBoat->setOrientation(o);
    }
}

int eFishery::take(const eResourceType type, const int count) {
    const int r = eResourceCollectBuildingBase::take(type, count);
    updateDisabled();
    return r;
}

void eFishery::spawnBoat() {
    if(mBoat) return;
    const auto b = e::make_shared<eFishingBoat>(getBoard());
    mBoat = b.get();
    eTile* t;
    const auto ct = centerTile();
    switch(mO) {
    case eOrientation::topRight: {
        const auto tr = ct->topRight<eTile>();
        if(!tr) return;
        t = tr->topRight<eTile>();
    } break;
    case eOrientation::bottomLeft:
        t = ct->bottom<eTile>();
        break;
    case eOrientation::topLeft:
        t = ct->topLeft<eTile>();
        break;
    default:
    case eOrientation::bottomRight: {
        const auto r = ct->right<eTile>();
        if(!r) return;
        t = r->bottomRight<eTile>();
    } break;
    }
    if(!t) return;
    b->changeTile(t);

    const auto hasRes = eHasResourceObject::sCreate(
                            eHasResourceObjectType::fish);
    const auto a = e::make_shared<eCollectResourceAction>(
                       this, b.get(), hasRes);
    const auto w = eWalkableObject::sCreateWater();
    a->setWalkable(w);
    a->setWaitTime(gUnpackTime);
    a->setFinishOnce(false);
    b->setAction(a);
}

void eFishery::updateDisabled() {
    const int s = eResourceBuildingBase::spaceLeft(eResourceType::fish);
    const bool d = s <= 0;
    if(mDisabled == d) return;
    mDisabled = d;
}

void eFishery::read(eReadStream& src) {
    eResourceCollectBuildingBase::read(src);

    src >> mDisabled;
    src >> mStateCount;
    src >> mState;
}

void eFishery::write(eWriteStream& dst) const {
    eResourceCollectBuildingBase::write(dst);

    dst << mDisabled;
    dst << mStateCount;
    dst << mState;
}
