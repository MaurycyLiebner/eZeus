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
private:
    void threadEntry();

    void queueTaskImpl(eTask* const task);

    static eThreadPool* sInstance;

    std::mutex mMutex;
    std::condition_variable mCv;
    bool mQuit = false;
    std::queue<eTask*> mTasks;
    std::vector<std::thread> mThreads;
};

#endif // ETHREADPOOL_H
