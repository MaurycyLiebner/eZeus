#include "etextureloader.h"

eTextureLoader::eTextureLoader(SDL_Renderer* const renderer) :
    mRenderer(renderer) {}

eTextureLoader::~eTextureLoader() {
    {
        std::unique_lock<std::mutex> lock(mTasksMutex);

        mQuit = true;
        mCv.notify_all();
    }
    for(auto& thread : mThreads) {
        thread.join();
    }
}

void eTextureLoader::initialize() {
    const int hc = std::thread::hardware_concurrency();
    const int threads = hc > 1 ? hc : 1;
    for(int i = 0; i < threads; i++) {
        mThreads.emplace_back(std::bind(&eTextureLoader::threadEntry, this));
    }
}

void eTextureLoader::threadEntry() {
    eTextureLoadTask task;
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
        {
            task.fSurface = IMG_Load(task.fPath.c_str());
            if(!task.fSurface) {
                printf("Unable to load image %s! SDL_image Error: %s\n",
                       task.fPath.c_str(), IMG_GetError());
                continue;
            }
            {
                std::lock_guard lock(mFinishedTasksMutex);
                mFinishedTasks.push_back(task);
            }
        }
    }
}

void eTextureLoader::queueTask(const eTextureLoadTask& task) {
    std::unique_lock<std::mutex> lock(mTasksMutex);
    mTasks.emplace(task);
    mCv.notify_one();
}

void eTextureLoader::handleFinished() {
    std::vector<eTextureLoadTask> tasks;
    {
        std::lock_guard lock(mFinishedTasksMutex);
        std::swap(tasks, mFinishedTasks);
    }
    for(auto &t : tasks) {
        t.fTex->load(mRenderer, t.fSurface);
    }
}

bool eTextureLoader::finished() {
    {
        std::unique_lock<std::mutex> lock(mTasksMutex);
        if(!mTasks.empty()) return false;
    }
    return true;
}

void eTextureLoader::waitUntilFinished() {
    while(!finished()) {
        std::chrono::milliseconds timespan(1);
        std::this_thread::sleep_for(timespan);
    }
}
