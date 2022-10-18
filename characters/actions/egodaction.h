#ifndef EGODACTION_H
#define EGODACTION_H

#include "ecomplexaction.h"

#include "characters/gods/egod.h"

class eGodAction : public eComplexAction {
public:
    eGodAction(eCharacter* const c,
               const eAction& failAction,
               const eAction& finishAction);

    void appear();
    void disappear(const bool die = false);

    void hermesRun(const bool appear);
    void moveAround(const eAction& finishAct = [](){},
                    const int time = 5000);
    void patrol(const eAction& finishAct = [](){},
                const int dist = 100);

    eGodType type() const { return mType; }
private:
    void playAppearSound();
    void playDisappearSound();

    const eGodType mType;
};

#endif // EGODACTION_H
