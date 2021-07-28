#ifndef ETHREADPOOL_H
#define ETHREADPOOL_H

#include "etask.h"

#include <queue>
#include <thread>
#include <mutex>
#include <functional>
#include <condition_variable>

class eThreadPool {
public:
    eThreadPool();
    ~eThreadPool();

    static void queueTask(eTask* const task);
    static void handleFinished();
private:
    void threadEntry();

    void queueTaskImpl(eTask* const task);
    void handleFinishedImpl();

    static eThreadPool* sInstance;

    bool mQuit = false;

    std::mutex mTasksMutex;
    std::condition_variable mCv;
    std::queue<eTask*> mTasks;

    std::mutex mFinishedTasksMutex;
    std::vector<eTask*> mFinishedTasks;

    std::vector<std::thread> mThreads;
};

#endif // ETHREADPOOL_H
