#include "ebuildingwithresource.h"

#include "characters/ecarttransporter.h"
#include "characters/actions/ecarttransporteraction.h"

int eBuildingWithResource::stash(const eResourceType type, const int count) {
    const bool a = static_cast<bool>(type & mStashable);
    if(!a) return 0;
    for(auto& s : mStash) {
        if(s.fType == type) {
            s.fCount += count;
            return count;
        }
    }
    mStash.push_back(eStash{type, count});
    return count;
}

int eBuildingWithResource::stashCount(const eResourceType type) const {
    for(const auto& s : mStash) {
        if(s.fType == type) {
            return s.fCount;
        }
    }
    return 0;
}

void eBuildingWithResource::setStashable(const eResourceType s) {
    mStashable = s;
}

void eBuildingWithResource::addFromStash() {
    for(int i = 0; i < (int)mStash.size(); i++) {
        auto& s = mStash[i];
        const int a = add(s.fType, s.fCount);
        if(a >= s.fCount) {
            mStash.erase(mStash.begin() + i);
            i--;
        } else {
            s.fCount -= a;
        }
    }
}

stdptr<eCartTransporter> eBuildingWithResource::spawnCart(
        const eCartActionTypeSupport s) {
    const auto t = centerTile();
    auto& board = getBoard();

    const auto c = e::make_shared<eCartTransporter>(board);
    c->changeTile(t);

    const auto a = e::make_shared<eCartTransporterAction>(
                       c.get(), this);
    c->setAction(a);
    c->setSupport(s);
    return c.get();
}

void eBuildingWithResource::read(eReadStream& src) {
    eBuilding::read(src);
    src >> mStashable;
    int ns;
    src >> ns;
    for(int i = 0; i < ns; i++) {
        auto& s = mStash.emplace_back();
        src >> s.fType;
        src >> s.fCount;
    }
}

void eBuildingWithResource::write(eWriteStream& dst) const {
    eBuilding::write(dst);
    dst << mStashable;
    dst << mStash.size();
    for(const auto& s : mStash) {
        dst << s.fType;
        dst << s.fCount;
    }
}
