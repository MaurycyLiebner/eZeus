#ifndef EPATROLBUILDINGBASE_H
#define EPATROLBUILDINGBASE_H

#include "eemployingbuilding.h"

#include "characters/actions/epatrolaction.h"
#include "enumbers.h"

class ePatrolBuildingBase : public eEmployingBuilding {
public:
    using eCharGenerator =  std::function<stdsptr<eCharacter>()>;
    using eActGenerator =  std::function<stdsptr<eCharacterAction>(
                                eCharacter* const c,
                                ePatrolBuildingBase* const b,
                                const std::vector<ePatrolGuide>& guides,
                                const stdsptr<eDirectionTimes>& dirTimes)>;
    ePatrolBuildingBase(eGameBoard& board,
                        const eCharGenerator& charGen,
                        const eActGenerator& actGen,
                        const eBuildingType type,
                        const int sw, const int sh,
                        const int maxEmployees);
    ePatrolBuildingBase(eGameBoard& board,
                        const eCharGenerator& charGen,
                        const eBuildingType type,
                        const int sw, const int sh,
                        const int maxEmployees);
    ~ePatrolBuildingBase();

    static stdsptr<eCharacterAction> sDefaultActGenerator(
            eCharacter* const c,
            ePatrolBuildingBase* const b,
            const std::vector<ePatrolGuide>& guides,
            const stdsptr<eDirectionTimes>& dirTimes);

    void timeChanged(const int by) override;

    using ePatrolGuides = std::vector<ePatrolGuide>;
    ePatrolGuides& patrolGuides() { return mPatrolGuides; };
    ePatrolGuides reversePatrolGuides() const;
    void setPatrolGuides(const ePatrolGuides& g);
    bool bothDirections() const { return mBothDirections; }
    void setBothDirections(const bool both);

    bool spawn();

    void setSpawnPatrolers(const bool s);
    bool spawnPatrolers() const { return mSpawnPatrolers; }

    int maxDistance() const { return mMaxDistance; }

    bool spawnsPatrolers() const;

    const stdsptr<eDirectionTimes>& dirTimes() const
    { return mDirTimes; }

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
private:
    const eCharGenerator mCharGenerator;
    const eActGenerator mActGenerator;

    bool mBothDirections = false;
    bool mLastDirection = false;
    int mSpawnRoadId = 0;
    stdsptr<eDirectionTimes> mDirTimes =
            std::make_shared<eDirectionTimes>();

    bool mSpawnPatrolers = true;

    const int mMaxDistance = eNumbers::sPatrolerMaxDistance;

    const int mWaitTime = eNumbers::sPatrolerWaitTime;
    int mSpawnTime = 1000000;
    stdptr<eCharacter> mChar;

    ePatrolGuides mPatrolGuides;
};

#endif // EPATROLBUILDINGBASE_H
