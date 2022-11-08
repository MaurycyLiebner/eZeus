#ifndef EINVASIONHANDLER_H
#define EINVASIONHANDLER_H

#include "engine/egameboard.h"

class eInvasionEvent;

enum class eInvasionStage {
    spread, invade, comeback
};

class eInvasionHandler {
public:
    eInvasionHandler(eGameBoard& board, eWorldCity* const city);
    ~eInvasionHandler();

    void initialize(eTile* const tile,
                    const int infantry,
                    const int cavalry,
                    const int archers);

    void incTime(const int by);
private:
    eGameBoard& mBoard;
    eWorldCity* const mCity;
    eTile* mTile = nullptr;
    eInvasionStage mStage = eInvasionStage::spread;
    std::vector<stdsptr<eSoldierBanner>> mBanners;

    int mWait = 0;
};

#endif // EINVASIONHANDLER_H
