#ifndef EHEROACTION_H
#define EHEROACTION_H

#include "eactionwithcomeback.h"

class eMonster;

enum class eHeroActionStage {
    none, patrol, hunt, fight, goBack
};

class eHeroAction : public eActionWithComeback {
public:
    using eActionWithComeback::eActionWithComeback;

    bool decide();
    void increment(const int by);
private:
    void lookForMonster();
    void lookForMonsterFight();
    bool fightMonster(eMonster* const m);
    void huntMonster(eMonster* const m);

    eHeroActionStage mStage = eHeroActionStage::none;
    int mLookForMonster = 0;
};

#endif // EHEROACTION_H
