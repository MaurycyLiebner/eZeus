#include "echariotfactory.h"

#include "textures/egametextures.h"
#include "enumbers.h"

eChariotFactory::eChariotFactory(eGameBoard& board) :
    eEmployingBuilding(board, eBuildingType::chariotFactory, 4, 4, 30) {
    eGameTextures::loadChariotFactory();
}

eChariotFactory::~eChariotFactory() {
    if(mWheatCart) mWheatCart->kill();
    if(mHorseCart) mHorseCart->kill();
}

std::shared_ptr<eTexture>
eChariotFactory::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings();
    return blds[sizeId].fChariotFactory;
}

std::vector<eOverlay>
eChariotFactory::getOverlays(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings();
    const auto& texs = blds[sizeId];

    std::vector<eOverlay> os;

    const auto& hcoll = texs.fChariotFactoryHorses;
    if(mHorses > 0) {
        eOverlay& o = os.emplace_back();
        const int collId = std::min(3, mHorses - 1);
        const auto& coll = hcoll[collId];
        const int texId = textureTime() % coll.size();
        o.fTex = coll.getTexture(texId);
        o.fX = -1.68;
        o.fY = -3.28;
    }

    const auto& ccoll = texs.fChariotFactoryChariots;
    if(mChariots == 0) {
        eOverlay& o = os.emplace_back();
        const auto& coll = texs.fChariotFactoryOverlay;
        const int texId = textureTime() % coll.size();
        o.fTex = coll.getTexture(texId);
        o.fX = -0.63;
        o.fY = -3.92;
    } else if(mChariots > 0) {
        eOverlay& o = os.emplace_back();
        const int texId = std::min(3, mChariots - 1);
        o.fTex = ccoll.getTexture(texId);
        o.fX = -0.7;
        o.fY = -2.95;
    }

    if(mWood > 0) {
        {
            const auto& coll = texs.fChariotFactoryOverlay1;
            const int texId = textureTime() % coll.size();
            eOverlay& o = os.emplace_back();
            o.fTex = coll.getTexture(texId);
            o.fX = -0.2;
            o.fY = -3.75;
        }

        {
            const auto& coll = texs.fWaitingWood;
            const int resMax = coll.size() - 1;
            const int res = std::clamp(mWood - 1, 0, resMax);
            eOverlay& o = os.emplace_back();
            o.fTex = coll.getTexture(res);
            o.fX = -1.5;
            o.fY = -2.85;
        }
    }

    return os;
}

void eChariotFactory::timeChanged(const int by) {
    if(enabled()) {
        if(!mWheatCart) {
            mWheatCart = spawnCart(eCartActionTypeSupport::take);
            mWheatCart->setSupportResource(eResourceType::wheat);
        }
        if(!mHorseCart) {
            mHorseCart = spawnCart(eCartActionTypeSupport::take);
            mHorseCart->setSupportResource(eResourceType::horse);
            mHorseCart->setType(eCartTransporterType::horse);
        }
        if(mWood > 2 && mChariots < 4) {
            const int chariotBuildingType = eNumbers::sChariotBuildingTime;
            mChariotBuildingTime += by;
            if(mChariotBuildingTime > chariotBuildingType) {
                mChariotBuildingTime = 0;
                mChariots++;
                mWood -= 2;
            }

        }
    }
    eEmployingBuilding::timeChanged(by);
}

int eChariotFactory::count(const eResourceType type) const {
    if(type == eResourceType::wood) return mWood;
    if(type == eResourceType::horse) return mHorses;
    if(type == eResourceType::chariot) return chariotCount();
    return eEmployingBuilding::count(type);
}

int eChariotFactory::add(const eResourceType type, const int count) {
    if(type == eResourceType::wood) {
        mWood += count;
        return count;
    } else if(type == eResourceType::horse) {
        mHorses += count;
        return count;
    }
    return eEmployingBuilding::add(type, count);
}

int eChariotFactory::take(const eResourceType type, const int count) {
    if(type == eResourceType::chariot) {
        const int t = std::min(mHorses, std::min(mChariots, count));
        mChariots -= t;
        mHorses -= t;
        return t;
    }
    return eEmployingBuilding::take(type, count);
}

int eChariotFactory::spaceLeft(const eResourceType type) const {
    if(type == eResourceType::wheat) return std::max(0, 8 - mWood);
    if(type == eResourceType::horse) return std::max(0, 4 - mHorses);
    return eEmployingBuilding::spaceLeft(type);
}

std::vector<eCartTask> eChariotFactory::cartTasks() const {
    auto tasks = eEmployingBuilding::cartTasks();

    if(mWood < 8) {
        eCartTask task;
        task.fType = eCartActionType::take;
        task.fResource = eResourceType::wood;
        task.fMaxCount = std::max(0, 8 - mWood);
        tasks.push_back(task);
    }
    if(mHorses < 4) {
        eCartTask task;
        task.fType = eCartActionType::take;
        task.fResource = eResourceType::horse;
        task.fMaxCount = std::max(0, 4 - mHorses);
        tasks.push_back(task);
    }

    return tasks;
}

void eChariotFactory::read(eReadStream& src) {
    eEmployingBuilding::read(src);

    src >> mWood;
    src >> mHorses;
    src >> mChariots;
    auto& board = getBoard();
    src.readCharacter(&board, [this](eCharacter* const c) {
        mWheatCart = static_cast<eCartTransporter*>(c);
    });
    src.readCharacter(&board, [this](eCharacter* const c) {
        mHorseCart = static_cast<eCartTransporter*>(c);
    });
}

void eChariotFactory::write(eWriteStream& dst) const {
    eEmployingBuilding::write(dst);

    dst << mWood;
    dst << mHorses;
    dst << mChariots;
    dst.writeCharacter(mWheatCart);
    dst.writeCharacter(mHorseCart);
}
