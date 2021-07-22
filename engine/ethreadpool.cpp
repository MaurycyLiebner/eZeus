#include "ethreadpool.h"

eThreadPool* eThreadPool::sInstance = nullptr;

eThreadPool::eThreadPool() {
    sInstance = this;

    const int hc = std::thread::hardware_concurrency();
    const int threads = hc > 1 ? hc - 1 : 1;
    for(int i = 0; i < threads; i++) {
        mThreads.emplace_back(std::bind(&eThreadPool::threadEntry, this));
    }
}

eThreadPool::~eThreadPool() {
    sInstance = nullptr;

    {
        std::unique_lock<std::mutex> lock(mMutex);

        mQuit = true;
        mCv.notify_all();
    }
    for(auto& thread : mThreads) {
        thread.join();
    }
}

void eThreadPool::queueTask(eTask* const task) {
    sInstance->queueTaskImpl(task);
}

void eThreadPool::threadEntry() {
    eTask* task = nullptr;
    while(!mQuit) {
        {
            std::unique_lock<std::mutex> lock(mMutex);

            while(!mQuit && mTasks.empty()) {
                mCv.wait(lock);
            }

            if(mTasks.empty()) return;

            task = mTasks.front();
            mTasks.pop();
        }
        if(task) task->exec();
    }
}

void eThreadPool::queueTaskImpl(eTask* const task) {
    std::unique_lock<std::mutex> lock(mMutex);
    mTasks.emplace(task);
    mCv.notify_one();
}
