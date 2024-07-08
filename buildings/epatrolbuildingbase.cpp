#include "epatrolbuildingbase.h"

ePatrolBuildingBase::ePatrolBuildingBase(
        eGameBoard& board,
        const eCharGenerator& charGen,
        const eActGenerator& actGen,
        const eBuildingType type,
        const int sw, const int sh,
        const int maxEmployees) :
    eEmployingBuilding(board, type, sw, sh, maxEmployees),
    mCharGenerator(charGen),
    mActGenerator(actGen) {

}

stdsptr<eCharacterAction>
ePatrolBuildingBase::sDefaultActGenerator(
           eCharacter* const c,
           ePatrolBuildingBase* const b,
           const std::vector<ePatrolGuide>& guides,
           const stdsptr<eDirectionTimes>& dirTimes) {
    return e::make_shared<ePatrolAction>(c, b, guides, dirTimes);
}

ePatrolBuildingBase::ePatrolBuildingBase(
        eGameBoard& board,
        const eCharGenerator& charGen,
        const eBuildingType type,
        const int sw, const int sh,
        const int maxEmployees) :
    ePatrolBuildingBase(board, charGen, sDefaultActGenerator,
                        type, sw, sh, maxEmployees) {}

ePatrolBuildingBase::~ePatrolBuildingBase() {
    if(mChar) mChar->kill();
}

void ePatrolBuildingBase::timeChanged(const int by) {
    if(mSpawnPatrolers && enabled()) {
        if(!mChar) {
            mSpawnTime += by;
            const int wait = mWaitTime/effectiveness();
            if(mSpawnTime > wait) {
                mSpawnTime -= wait;
                spawn();
            }
        }
    }
    eEmployingBuilding::timeChanged(by);
}

using ePatrolGuides = std::vector<ePatrolGuide>;
ePatrolGuides ePatrolBuildingBase::reversePatrolGuides() const {
    auto guides = mPatrolGuides;
    std::reverse(guides.begin(), guides.end());
    return guides;
}

void ePatrolBuildingBase::setPatrolGuides(const ePatrolGuides &g) {
    mPatrolGuides = g;
}

void ePatrolBuildingBase::setBothDirections(const bool both) {
    mBothDirections = both;
}

bool ePatrolBuildingBase::spawn() {
    if(!mCharGenerator || !mActGenerator) return false;
    const auto chr = mCharGenerator();
    mChar = chr.get();
    if(!mChar) return false;
    if(mPatrolGuides.empty()) {
        eTile* t = nullptr;
        const auto bt = type();
        if(bt == eBuildingType::commonAgora ||
           bt == eBuildingType::grandAgora) {
            t = centerTile();
        } else {
            const auto ts = surroundingRoad(false, true);
            if(!ts.empty()) {
                const int tss = ts.size();
                if(++mSpawnRoadId >= tss) mSpawnRoadId = 0;
                t = ts[mSpawnRoadId];
            }
        }
        if(!t) return false;
        chr->changeTile(t);
    } else {
        chr->changeTile(centerTile());
    }
    auto guides = mPatrolGuides;
    if(mBothDirections) {
        mLastDirection = !mLastDirection;
        if(mLastDirection) {
            std::reverse(guides.begin(), guides.end());
        }
    }
    const auto a = mActGenerator(chr.get(), this,
                                 guides, mDirTimes);
    chr->setAction(a);
    return true;
}

void ePatrolBuildingBase::setSpawnPatrolers(const bool s) {
    mSpawnPatrolers = s;
}

bool ePatrolBuildingBase::spawnsPatrolers() const {
    return mCharGenerator && mActGenerator;
}

void ePatrolBuildingBase::read(eReadStream& src) {
    eEmployingBuilding::read(src);

    src >> mBothDirections;
    src >> mLastDirection;

    src >> mSpawnPatrolers;
    src >> mSpawnTime;
    src >> mSpawnRoadId;

    mDirTimes = src.readDirectionTimes(getBoard());

    src.readCharacter(&getBoard(), [this](eCharacter* const c) {
        mChar = c;
    });

    int n;
    src >> n;
    for(int i = 0; i < n; i++) {
        ePatrolGuide pg;
        src >> pg.fX;
        src >> pg.fY;
        mPatrolGuides.push_back(pg);
    }
}

void ePatrolBuildingBase::write(eWriteStream& dst) const {
    eEmployingBuilding::write(dst);

    dst << mBothDirections;
    dst << mLastDirection;

    dst << mSpawnPatrolers;
    dst << mSpawnTime;
    dst << mSpawnRoadId;

    dst.writeDirectionTimes(mDirTimes.get());

    dst.writeCharacter(mChar);

    dst << mPatrolGuides.size();
    for(const auto& pg : mPatrolGuides) {
        dst << pg.fX;
        dst << pg.fY;
    }
}
