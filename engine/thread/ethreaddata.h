#ifndef ETHREADDATA_H
#define ETHREADDATA_H

#include <queue>
#include <atomic>
#include <mutex>
#include <condition_variable>

#include "engine/thread/ethreadboard.h"

class eGameBoard;
class eTask;

class eThreadData {
public:
    eThreadData() {}
    eThreadData(const eThreadData& s);

    void initialize(const int w, const int h);

    eThreadBoard& board() { return mBoard; }

    void scheduleUpdate(eGameBoard& board);

    void updateBoard();

    void setRunning(const bool r);

    bool fDataUpdateScheduled = false;
    std::atomic_bool fBusy{false};
    std::mutex fTasksMutex;
    std::condition_variable fCv;
    std::condition_variable fCvFinished;
    std::queue<eTask*> fTasks;
private:
    std::atomic_bool mRunning{false};

    eThreadBoard mBoard;
    std::atomic_bool mTmpChanged{false};
    eThreadBoard mTmpBoard;

    std::mutex mTmpBoardMutex;
};

#endif // ETHREADDATA_H
