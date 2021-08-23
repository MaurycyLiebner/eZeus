#ifndef EACTIONWITHCOMEBACK_H
#define EACTIONWITHCOMEBACK_H

#include "ecomplexaction.h"
#include "emovepathaction.h"
#include "engine/emovedirection.h"

class eActionWithComeback : public eComplexAction {
public:
    eActionWithComeback(eCharacter* const c,
                        const eAction& failAction,
                        const eAction& finishAction);
protected:
    using eWalkable = std::function<bool(eTileBase*)>;
    void goBack(const eWalkable& walkable);
private:
    int mStartX{0};
    int mStartY{0};
};

#endif // EACTIONWITHCOMEBACK_H
