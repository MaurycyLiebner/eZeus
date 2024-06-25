#include "eurchinquay.h"

#include "characters/eurchingatherer.h"
#include "characters/actions/ecollectresourceaction.h"
#include "textures/egametextures.h"
#include "engine/egameboard.h"

eUrchinQuay::eUrchinQuay(eGameBoard& board, const eOrientation o) :
    eResourceCollectBuildingBase(board, eBuildingType::urchinQuay,
                                 2, 2, 10, eResourceType::urchin),
    mO(o) {
    eGameTextures::loadUrchinQuay();
}

eUrchinQuay::~eUrchinQuay() {
    if(mGatherer) mGatherer->kill();
}

const int gUnpackTime = 5000;

void eUrchinQuay::timeChanged(const int by) {
    if(enabled()) {
        mStateCount += by;
        if(!mGatherer) {
            spawnGatherer();
            mState = eUrchinQuayState::waiting;
        }
        switch(mState) {
        case eUrchinQuayState::unpacking: {
            if(mStateCount > gUnpackTime) {
                mStateCount -= gUnpackTime;
                mState = eUrchinQuayState::waiting;
                eResourceBuildingBase::add(eResourceType::urchin, 3);
                updateDisabled();
            }
        } break;
        default: break;
        }
    }
    eResourceBuildingBase::timeChanged(by);
}

std::shared_ptr<eTexture> eUrchinQuay::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings();
    const auto& coll = blds[sizeId].fUrchinQuay;
    auto& board = getBoard();
    const auto dir = board.direction();
    const auto oo = sRotated(mO, dir);
    int id = 3;
    switch(oo) {
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

std::vector<eOverlay> eUrchinQuay::getOverlays(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings()[sizeId];
    auto& board = getBoard();
    const auto dir = board.direction();
    const auto oo = sRotated(mO, dir);
    switch(mState) {
    case eUrchinQuayState::waiting: {
        eOverlay o;
        const eTextureCollection* coll;
        switch(oo) {
        case eOrientation::topRight:
            coll = &blds.fFisheryOverlay[0];
            o.fX = -0.25;
            o.fY = -2.5;
            break;
        case eOrientation::bottomLeft:
            coll = &blds.fFisheryOverlay[4];
            o.fX = 0.25;
            o.fY = -1.38;
            break;
        default:
        case eOrientation::topLeft:
            coll = &blds.fFisheryOverlay[6];
            o.fX = -0.75;
            o.fY = -2.2;
            break;
        case eOrientation::bottomRight:
            coll = &blds.fFisheryOverlay[2];
            o.fX = 0.5;
            o.fY = -2.25;
            break;
        }

        const int texId = textureTime() % coll->size();
        o.fTex = coll->getTexture(texId);
        return {o};
    } break;
    case eUrchinQuayState::unpacking: {
        eOverlay o;
        const eTextureCollection* coll;
        switch(oo) {
        case eOrientation::topRight:
            coll = &blds.fUrchinQuayUnpackingOverlayTR;
            o.fX = 0.19;
            o.fY = -1.84;
            break;
        case eOrientation::bottomLeft:
            coll = &blds.fUrchinQuayUnpackingOverlayBL;
            o.fX = 0.05;
            o.fY = -1.40;
            break;
        default:
        case eOrientation::topLeft:
            coll = &blds.fUrchinQuayUnpackingOverlayTL;
            o.fX = 0.05;
            o.fY = -2.1;
            break;
        case eOrientation::bottomRight:
            coll = &blds.fUrchinQuayUnpackingOverlayBR;
            o.fX = 0.60;
            o.fY = -1.45;
            break;
        }

        const int texId = textureTime() % coll->size();
        o.fTex = coll->getTexture(texId);
        return {o};
    } break;
    }
    return {};
}

void eUrchinQuay::addRaw() {
    mState = eUrchinQuayState::unpacking;
    mStateCount = 0;
    if(mGatherer) {
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
        mGatherer->setOrientation(o);
    }
}

int eUrchinQuay::take(const eResourceType type, const int count) {
    const int r = eResourceCollectBuildingBase::take(type, count);
    updateDisabled();
    return r;
}

void eUrchinQuay::spawnGatherer() {
    if(mGatherer) return;
    const auto b = e::make_shared<eUrchinGatherer>(getBoard());
    mGatherer = b.get();
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
                            eHasResourceObjectType::urchin);
    const auto a = e::make_shared<eCollectResourceAction>(
                       this, b.get(), hasRes);
    const auto w = eWalkableObject::sCreateWater();
    a->setWalkable(w);
    a->setWaitTime(gUnpackTime);
    a->setFinishOnce(false);
    b->setAction(a);
}

void eUrchinQuay::updateDisabled() {
    const int s = eResourceBuildingBase::spaceLeft(eResourceType::urchin);
    const bool d = s <= 0;
    if(mDisabled == d) return;
    mDisabled = d;
}

void eUrchinQuay::read(eReadStream& src) {
    eResourceCollectBuildingBase::read(src);

    src >> mDisabled;
    src >> mStateCount;
    src >> mState;
    src.readCharacter(&getBoard(), [this](eCharacter* const c) {
        mGatherer = static_cast<eUrchinGatherer*>(c);
    });
}

void eUrchinQuay::write(eWriteStream& dst) const {
    eResourceCollectBuildingBase::write(dst);

    dst << mDisabled;
    dst << mStateCount;
    dst << mState;
    dst.writeCharacter(mGatherer);
}
