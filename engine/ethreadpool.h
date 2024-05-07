#ifndef ETHREADPOOL_H
#define ETHREADPOOL_H

#include "etask.h"

#include "thread/ethreaddata.h"

#include <queue>
#include <thread>
#include <mutex>
#include <functional>
#include <condition_variable>

class eThreadPool {
public:
    eThreadPool(eGameBoard& board);
    ~eThreadPool();

    void initialize(const int w, const int h);

    void queueTask(eTask* const task);
    void handleFinished();

    void scheduleDataUpdate();

    bool finished();
    void waitFinished();
private:
    void threadEntry(eThreadData* data);
    void updateData();

    eGameBoard& mBoard;
    bool mDataUpdateScheduled = false;

    bool mQuit = false;

    int mBusy = 0;

    std::mutex mTasksMutex;
    std::condition_variable mCv;
    std::condition_variable mCvFinished;
    std::queue<eTask*> mTasks;

    std::mutex mFinishedTasksMutex;
    std::vector<eTask*> mFinishedTasks;

    std::vector<std::thread> mThreads;
    std::vector<eThreadData*> mThreadData;
};

#endif // ETHREADPOOL_H
