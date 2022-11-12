#ifndef EPATROLBUILDINGBASE_H
#define EPATROLBUILDINGBASE_H

#include "eemployingbuilding.h"

#include "characters/actions/epatrolaction.h"

class ePatrolBuildingBase : public eEmployingBuilding {
public:
    using eCharGenerator =  std::function<stdsptr<eCharacter>()>;
    using eActGenerator =  std::function<stdsptr<eCharacterAction>(
                                eCharacter* const c,
                                ePatrolBuildingBase* const b,
                                const std::vector<ePatrolGuide>& guides,
                                const eAction& failAction,
                                const eAction& finishAction,
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
            const eAction& failAction,
            const eAction& finishAction,
            const stdsptr<eDirectionTimes>& dirTimes);

    void timeChanged(const int by) override;

    using ePatrolGuides = std::vector<ePatrolGuide>;
    ePatrolGuides* patrolGuides() { return &mPatrolGuides; };
    void setPatrolGuides(const ePatrolGuides& g);

    bool spawn();

    void setSpawnPatrolers(const bool s);
    bool spawnPatrolers() const { return mSpawnPatrolers; }

    void setMaxDistance(const int m) { mMaxDistance = m; }
    int maxDistance() const { return mMaxDistance; }

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
private:
    const eCharGenerator mCharGenerator;
    const eActGenerator mActGenerator;

    int mSpawnRoadId = 0;
    stdsptr<eDirectionTimes> mDirTimes =
            std::make_shared<eDirectionTimes>();

    bool mSpawnPatrolers = true;

    int mMaxDistance = 40;

    const int mWaitTime = 5000;
    int mSpawnTime = mWaitTime;
    stdptr<eCharacter> mChar;

    ePatrolGuides mPatrolGuides;
};

#endif // EPATROLBUILDINGBASE_H
