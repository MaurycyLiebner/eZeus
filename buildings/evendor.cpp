#include "evendor.h"

#include "characters/echaracter.h"
#include "characters/ecarttransporter.h"
#include "textures/egametextures.h"
#include "buildings/eagorabase.h"

#include <algorithm>

eVendor::eVendor(eGameBoard& board,
                 const eResourceType resType,
                 const eProvide provType,
                 const eBaseTex& baseTex,
                 const double overlayX,
                 const double overlayY,
                 const eBaseTex& overlayTex,
                 const double overlayX2,
                 const double overlayY2,
                 const eOverlays& overlayTex2,
                 const eBuildingType type,
                 const int sw, const int sh,
                 const int maxEmployees) :
    eEmployingBuilding(board, type, sw, sh, maxEmployees),
    mResType(resType),
    mProvType(provType),
    mBaseTex(baseTex),
    mOverlayX(overlayX),
    mOverlayY(overlayY),
    mOverlayTex(overlayTex),
    mOverlayX2(overlayX2),
    mOverlayY2(overlayY2),
    mOverlayTex2(overlayTex2) {}

eVendor::~eVendor() {
    if(mCart) mCart->kill();
}

std::shared_ptr<eTexture> eVendor::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings();
    return blds[sizeId].*mBaseTex;
}

std::vector<eOverlay> eVendor::getOverlays(const eTileSize size) const {
    if(mResource <= 0) return {};

    auto os = eEmployingBuilding::getOverlays(size);
    const int sizeId = static_cast<int>(size);
    const auto& texs = eGameTextures::buildings();

    if(mOverlayTex) {
        eOverlay o;
        o.fTex = texs[sizeId].*mOverlayTex;
        o.fX = mOverlayX;
        o.fY = mOverlayY;
        os.push_back(o);
    }

    if(mOverlayTex2) {
        eOverlay o2;
        const auto& coll = texs[sizeId].*mOverlayTex2;
        o2.fTex = coll.getTexture(textureTime() % coll.size());
        o2.fX = mOverlayX2;
        o2.fY = mOverlayY2;
        os.push_back(o2);
    }

    return os;
}

void eVendor::erase() {
    deleteLater();
    const auto a = agora();
    a->setBuilding(this, nullptr);
    a->fillSpaces();
}

int eVendor::add(const eResourceType type, const int count) {
    if(!static_cast<bool>(type & mResType)) return 0;

    const int r = std::clamp(count, 0, spaceLeft(type));
    mResource += r*mResMult;
    return r;
}

int eVendor::take(const eResourceType type, const int count) {
    (void)type;
    (void)count;
    return 0;
}

int eVendor::count(const eResourceType type) const {
    (void)type;
    return 0;
}

int eVendor::spaceLeft(const eResourceType type) const {
    if(type != mResType) return 0;
    return (mMaxResource - mResource)/mResMult;
}

void eVendor::timeChanged(const int by) {
    if(enabled()) {
        if(!mCart) {
            mCart = spawnCart(eCartActionTypeSupport::take);
            switch(mResType) {
            case eResourceType::food:
                mCart->setType(eCartTransporterType::food);
                break;
            case eResourceType::fleece:
                mCart->setType(eCartTransporterType::fleece);
                break;
            case eResourceType::oliveOil:
                mCart->setType(eCartTransporterType::oil);
                break;
            case eResourceType::wine:
                mCart->setType(eCartTransporterType::wine);
                break;
            case eResourceType::armor:
                mCart->setType(eCartTransporterType::arms);
                break;
            case eResourceType::horse:
                mCart->setType(eCartTransporterType::horse);
                break;
            case eResourceType::chariot:
                mCart->setType(eCartTransporterType::chariot);
                break;
            default:
                break;
            }
        }
    }
    eEmployingBuilding::timeChanged(by);
}

std::vector<eCartTask> eVendor::cartTasks() const {
    const int space = spaceLeft(mResType);

    if(space > 0) {
        eCartTask task;
        task.fType = eCartActionType::take;
        task.fResource = mResType;
        task.fMaxCount = space;
        return {task};
    }

    return {};
}

void eVendor::setAgora(const stdsptr<eAgoraBase>& agora) {
    mAgora = agora;
}

int eVendor::agoraSpaceId() const {
    if(!mAgora) return -1;
    return mAgora->buildingId(this);
}

int eVendor::peddlerResource() const {
    return mResource;
}

int eVendor::takeForPeddler(const int t) {
    const int tt = std::clamp(t, 0, mResource);
    mResource -= tt;
    return tt;
}

void eVendor::read(eReadStream& src) {
    eEmployingBuilding::read(src);
    src >> mResource;
    src >> mVendorEnabled;
    src.readCharacter(&getBoard(), [this](eCharacter* const c) {
        mCart = static_cast<eCartTransporter*>(c);
    });
}

void eVendor::write(eWriteStream& dst) const {
    eEmployingBuilding::write(dst);
    dst << mResource;
    dst << mVendorEnabled;
    dst.writeCharacter(mCart);
}
