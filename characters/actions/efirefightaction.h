#ifndef EFIREFIGHTACTION_H
#define EFIREFIGHTACTION_H

#include "eactionwithcomeback.h"
#include "engine/emovedirection.h"
#include "epatrolmoveaction.h"

class eFireFightAction : public eActionWithComeback {
public:
    eFireFightAction(eCharacter* const c,
                     const std::vector<ePatrolGuide>& guides,
                     const eAction& failAction,
                     const eAction& finishAction);

    void increment(const int by);
private:
    bool goBack2();

    const std::vector<ePatrolGuide> mGuides;

    int mStartX = 0;
    int mStartY = 0;
};

#endif // EFIREFIGHTACTION_H
