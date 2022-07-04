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
                                const eAction& finishAction)>;
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
            const eAction& finishAction);

    void timeChanged(const int by);

    using ePatrolGuides = std::vector<ePatrolGuide>;
    ePatrolGuides* patrolGuides() { return &mPatrolGuides; };
    void setPatrolGuides(const ePatrolGuides& g);

    bool spawn();

    void setSpawnPatrolers(const bool s);
    bool spawnPatrolers() const { return mSpawnPatrolers; }
private:
    const eCharGenerator mCharGenerator;
    const eActGenerator mActGenerator;

    bool mSpawnPatrolers = true;

    int mWaitTime = 5000;
    int mSpawnTime = mWaitTime;
    stdsptr<eCharacter> mChar;

    ePatrolGuides mPatrolGuides;
};

#endif // EPATROLBUILDINGBASE_H
