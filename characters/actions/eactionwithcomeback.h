#ifndef EACTIONWITHCOMEBACK_H
#define EACTIONWITHCOMEBACK_H

#include "ecomplexaction.h"
#include "emovepathaction.h"
#include "engine/emovedirection.h"

#include <SDL2/SDL_rect.h>

class eBuilding;

class eActionWithComeback : public eComplexAction {
public:
    eActionWithComeback(eCharacter* const c,
                        const eAction& failAction,
                        const eAction& finishAction);
    eActionWithComeback(eCharacter* const c,
                        eTile* const startTile,
                        const eAction& failAction,
                        const eAction& finishAction);

    bool decide();

    void setFinishOnComeback(const bool b)
    { mFinishOnComeback = b; }
protected:
    using eWalkable = std::function<bool(eTileBase*)>;
    void goBack(const eWalkable& walkable);
    void goBack(eBuilding* const b,
                const eWalkable& walkable);
    void goBack(const SDL_Rect& rect,
                const eWalkable& walkable);

    eTile* startTile() const { return mStartTile; }
private:
    void teleportDecision();

    eTile* const mStartTile;

    bool mFinishOnComeback = false;
    bool mDefaultTry = false;
    bool mGoBackFail = false;
};

#endif // EACTIONWITHCOMEBACK_H
