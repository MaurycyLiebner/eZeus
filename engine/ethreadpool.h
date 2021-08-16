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
    eThreadPool();
    ~eThreadPool();

    void initialize(const int w, const int h);

    void queueTask(eTask* const task);
    void handleFinished();

    void scheduleUpdate(eGameBoard& board,
                        const int x, const int y,
                        const int w, const int h);
private:
    void threadEntry(eThreadData& data);


    bool mQuit = false;

    std::mutex mTasksMutex;
    std::condition_variable mCv;
    std::queue<eTask*> mTasks;

    std::mutex mFinishedTasksMutex;
    std::vector<eTask*> mFinishedTasks;

    std::vector<std::thread> mThreads;
    std::vector<eThreadData> mThreadData;
};

#endif // ETHREADPOOL_H
