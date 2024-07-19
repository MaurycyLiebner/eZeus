#include "etriremewharf.h"

#include "characters/etrireme.h"
#include "characters/actions/ecarttransporteraction.h"
#include "textures/egametextures.h"
#include "engine/egameboard.h"

eTriremeWharf::eTriremeWharf(eGameBoard& board, const eOrientation o) :
    eEmployingBuilding(board, eBuildingType::triremeWharf,
                       3, 3, 100),
    mO(o) {
    eGameTextures::loadTriremeWharf();
}

eTriremeWharf::~eTriremeWharf() {
    if(mTakeCart) mTakeCart->kill();
    if(mTrireme) mTrireme->kill();
}

std::shared_ptr<eTexture> eTriremeWharf::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings();
    const auto& coll = blds[sizeId].fTriremeWharf;
    auto& board = getBoard();
    const auto dir = board.direction();
    const auto o = sRotated(mO, dir);
    int id = 3;
    switch(o) {
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

std::vector<eOverlay> eTriremeWharf::getOverlays(const eTileSize size) const {
    (void)size;
    return {};
}

void eTriremeWharf::timeChanged(const int by) {
    if(enabled()) {
        if(!mTakeCart) {
            mTakeCart = spawnCart(eCartActionTypeSupport::take);
            mTakeCart->setMaxDistance(60);
        }
    }
    eEmployingBuilding::timeChanged(by);
}

int eTriremeWharf::add(const eResourceType type,
                       const int count) {
    if(type == eResourceType::wood) {
        const int r = std::clamp(mWoodCount + count, 0, mMaxWood);
        const int result = r - mWoodCount;
        mWoodCount = r;
        return result;
    } else if(type == eResourceType::armor) {
        const int r = std::clamp(mArmorCount + count, 0, mMaxArmor);
        const int result = r - mArmorCount;
        mArmorCount = r;
        return result;
    }
    return 0;
}

int eTriremeWharf::count(const eResourceType type) const {
    if(type == eResourceType::wood) {
        return mWoodCount;
    } else if(type == eResourceType::armor) {
        return mArmorCount;
    }
    return 0;
}

int eTriremeWharf::spaceLeft(const eResourceType type) const {
    if(type == eResourceType::wood) {
        return mMaxWood - mWoodCount;
    } else if(type == eResourceType::armor) {
        return mMaxArmor - mArmorCount;
    }
    return 0;
}

std::vector<eCartTask> eTriremeWharf::cartTasks() const {
    std::vector<eCartTask> tasks;

    if(mMaxWood > mWoodCount) {
        eCartTask task;
        task.fType = eCartActionType::take;
        task.fResource = eResourceType::wood;
        task.fMaxCount = mMaxWood - mWoodCount;
        tasks.push_back(task);
    }

    if(mMaxArmor > mArmorCount) {
        eCartTask task;
        task.fType = eCartActionType::take;
        task.fResource = eResourceType::armor;
        task.fMaxCount = mMaxArmor - mArmorCount;
        tasks.push_back(task);
    }

    return tasks;
}

void eTriremeWharf::read(eReadStream& src) {
    eEmployingBuilding::read(src);

    src.readCharacter(&getBoard(), [this](eCharacter* const c) {
        mTakeCart = static_cast<eCartTransporter*>(c);
    });
    src.readCharacter(&getBoard(), [this](eCharacter* const c) {
        mTrireme = static_cast<eTrireme*>(c);
    });
    src >> mWoodCount;
    src >> mArmorCount;
}

void eTriremeWharf::write(eWriteStream& dst) const {
    eEmployingBuilding::write(dst);

    dst.writeCharacter(mTakeCart);
    dst.writeCharacter(mTrireme);
    dst << mWoodCount;
    dst << mArmorCount;
}
