#include "ethreadpool.h"

eThreadPool::eThreadPool() {}

eThreadPool::~eThreadPool() {
    {
        std::unique_lock<std::mutex> lock(mTasksMutex);

        mQuit = true;
        mCv.notify_all();
    }
    for(auto& thread : mThreads) {
        thread.join();
    }
}

void eThreadPool::initialize(const int w, const int h) {
    const int hc = std::thread::hardware_concurrency();
    const int threads = hc > 1 ? hc - 1 : 1;
    for(int i = 0; i < threads; i++) {
        auto& b = mThreadData.emplace_back();
        b.initialize(w, h);
        mThreads.emplace_back(std::bind(&eThreadPool::threadEntry, this, b));
    }
}

void eThreadPool::threadEntry(eThreadData& data) {
    eTask* task = nullptr;
    while(!mQuit) {
        {
            std::unique_lock<std::mutex> lock(mTasksMutex);

            while(!mQuit && mTasks.empty()) {
                mCv.wait(lock);
            }

            if(mTasks.empty()) return;

            task = mTasks.front();
            mTasks.pop();
        }
        if(task) {
            {
                data.updateBoard();
                data.setRunning(true);
                auto& b = data.board();
                task->run(b);
                data.setRunning(false);
            }
            std::lock_guard lock(mFinishedTasksMutex);
            mFinishedTasks.push_back(task);
        }
    }
}

void eThreadPool::queueTask(eTask* const task) {
    std::unique_lock<std::mutex> lock(mTasksMutex);
    mTasks.emplace(task);
    mCv.notify_one();
}

void eThreadPool::handleFinished() {
    std::vector<eTask*> tasks;
    {
        std::lock_guard lock(mFinishedTasksMutex);
        std::swap(tasks, mFinishedTasks);
    }
    for(const auto t : tasks) {
        t->finish();
        delete t;
    }
}

void eThreadPool::scheduleUpdate(eGameBoard& board,
                                 const int x, const int y,
                                 const int w, const int h) {
    for(auto& d : mThreadData) {
        d.scheduleUpdate(board, x, y, w, h);
    }
}
