#include "ehorseranch.h"

#include "textures/egametextures.h"

#include "ehorseranchenclosure.h"

eHorseRanch::eHorseRanch(eGameBoard& board) :
    eEmployingBuilding(board, eBuildingType::horseRanch, 3, 3, 15) {}

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
    const int horse = 10000;
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
    eEmployingBuilding::timeChanged(by);
}


int eHorseRanch::count(const eResourceType type) const {
    if(type == eResourceType::wheat) return mWheat/100;
    return eEmployingBuilding::count(type);
}

int eHorseRanch::add(const eResourceType type, const int count) {
    if(type == eResourceType::wheat) {
        mWheat += count*100;
        return count;
    }
    return eEmployingBuilding::add(type, count);
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
