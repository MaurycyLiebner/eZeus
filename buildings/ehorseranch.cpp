#include "ehorseranch.h"

#include "textures/egametextures.h"

#include "ehorseranchenclosure.h"

#include <algorithm>

eHorseRanch::eHorseRanch(eGameBoard& board) :
    eEmployingBuilding(board, eBuildingType::horseRanch, 3, 3, 15) {
    eGameTextures::loadHorseRanch();
}

eHorseRanch::~eHorseRanch() {
    if(mTakeCart) mTakeCart->kill();
}

void eHorseRanch::erase() {
    mEnclosure->eBuilding::erase();
    eBuilding::erase();
}

std::shared_ptr<eTexture> eHorseRanch::getTexture(
        const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings();
    return blds[sizeId].fHorseRanch;
}

std::vector<eOverlay> eHorseRanch::getOverlays(
        const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings();
    const auto& texs = blds[sizeId];
    const auto& coll = texs.fHorseRanchOverlay;
    const int texId = textureTime() % coll.size();

    std::vector<eOverlay> os;
    eOverlay& o = os.emplace_back();
    o.fTex = coll.getTexture(texId);
    o.fX = -2.1;
    o.fY = -2.85;

    if(mWheat > 0) {
        const int nw = std::clamp((mWheat - 50)/100, 0, 7);
        eOverlay& wo = os.emplace_back();
        wo.fTex = texs.fWaitingWheat.getTexture(nw);
        wo.fX = -0.4;
        wo.fY = -2.7;
    }

    return os;
}

void eHorseRanch::timeChanged(const int by) {
    const int wheat = 1000;
    const int horse = 40000;
    if(enabled()) {
        if(!mTakeCart) {
            mTakeCart = spawnCart(eCartActionTypeSupport::take);
        }
        if(mWheat > 0) {
            mWheatTime += by;
            if(mWheatTime > wheat) {
                mWheat -= 10;
                mWheatTime -= wheat;
            }
            mHorseTime += by;
            if(mHorseTime > horse) {
                mHorseTime -= horse;
                mEnclosure->spawnHorse();
            }
        }
    }
    eEmployingBuilding::timeChanged(by);
}

int eHorseRanch::count(const eResourceType type) const {
    if(type == eResourceType::wheat) return mWheat/100;
    if(type == eResourceType::horse) return horseCount();
    return eEmployingBuilding::count(type);
}

int eHorseRanch::add(const eResourceType type, const int count) {
    if(type == eResourceType::wheat) {
        mWheat += count*100;
        return count;
    }
    return eEmployingBuilding::add(type, count);
}

int eHorseRanch::take(const eResourceType type, const int count) {
    if(type == eResourceType::horse) {
        return mEnclosure->take(type, count);
    }
    return eEmployingBuilding::take(type, count);
}

int eHorseRanch::spaceLeft(const eResourceType type) const {
    if(type == eResourceType::wheat) return 8 - mWheat/100;
    return eEmployingBuilding::spaceLeft(type);
}

std::vector<eCartTask> eHorseRanch::cartTasks() const {
    auto tasks = eEmployingBuilding::cartTasks();

    if(800 > mWheat) {
        eCartTask task;
        task.fType = eCartActionType::take;
        task.fResource = eResourceType::wheat;
        task.fMaxCount = 8 - mWheat/100;
        tasks.push_back(task);
    }

    return tasks;
}

void eHorseRanch::setEnclosure(eHorseRanchEnclosure* const e) {
    mEnclosure = e;
}

int eHorseRanch::horseCount() const {
    return mEnclosure->horseCount();
}

bool eHorseRanch::takeHorse() {
    return mEnclosure->takeHorse();
}

void eHorseRanch::read(eReadStream& src) {
    eEmployingBuilding::read(src);

    src >> mWheat;
    src >> mWheatTime;
    src >> mHorseTime;
    auto& board = getBoard();
    src.readCharacter(&board, [this](eCharacter* const c) {
        mTakeCart = static_cast<eCartTransporter*>(c);
    });
}

void eHorseRanch::write(eWriteStream& dst) const {
    eEmployingBuilding::write(dst);

    dst << mWheat;
    dst << mWheatTime;
    dst << mHorseTime;
    dst.writeCharacter(mTakeCart);
}
