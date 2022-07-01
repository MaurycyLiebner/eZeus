#ifndef ETHREADDATA_H
#define ETHREADDATA_H

#include <atomic>
#include <mutex>

#include "engine/thread/ethreadboard.h"

class eGameBoard;

class eThreadData {
public:
    eThreadData() {}
    eThreadData(const eThreadData& s);

    void initialize(const int w, const int h);

    eThreadBoard& board() { return mBoard; }

    void scheduleUpdate(eGameBoard& board);

    void updateBoard();

    void setRunning(const bool r);
private:
    std::atomic_bool mRunning{false};

    eThreadBoard mBoard;
    std::atomic_bool mTmpChanged{false};
    eThreadBoard mTmpBoard;

    std::mutex mMutex;
};

#endif // ETHREADDATA_H
