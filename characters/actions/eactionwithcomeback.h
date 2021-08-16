#ifndef EACTIONWITHCOMEBACK_H
#define EACTIONWITHCOMEBACK_H

#include "emovepathaction.h"
#include "engine/emovedirection.h"

class eActionWithComeback : public eCharacterAction {
public:
    eActionWithComeback(eCharacter* const c,
                        const eAction& failAction,
                        const eAction& finishAction);
    ~eActionWithComeback();

    void increment(const int by);
protected:
    eCharacterAction* currentAction() const { return mCurrentAction; }
    void setCurrentAction(eCharacterAction* const a);
    using eWalkable = std::function<bool(eTileBase*)>;
    virtual bool goBack(const eWalkable& walkable);
private:
    eCharacterAction* mCurrentAction = nullptr;

    int mStartX{0};
    int mStartY{0};
};

#endif // EACTIONWITHCOMEBACK_H
