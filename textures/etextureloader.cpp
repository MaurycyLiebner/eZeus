#include "etextureloader.h"

eTextureLoader::eTextureLoader(SDL_Renderer* const renderer) :
    mRenderer(renderer) {}

eTextureLoader::~eTextureLoader() {
    if(mUseBMPs) {
        if(mRFile) SDL_RWclose(mRFile);
        if(mWFile) SDL_RWclose(mWFile);
    }
    {
        std::unique_lock<std::mutex> lock(mTasksMutex);

        mQuit = true;
        mCv.notify_all();
    }
    for(auto& thread : mThreads) {
        thread.join();
    }
}

void eTextureLoader::initialize(const std::string& path) {
    if(mUseBMPs) {
        if(path.empty()) return;
        mRFile = SDL_RWFromFile(path.c_str(), "r+b");
        if(!mRFile) {
            mWFile = SDL_RWFromFile(path.c_str(), "w+b");
            if(!mWFile) {
                printf("Unable to open %s! SDL_error Error: %s\n",
                       path.c_str(), SDL_GetError());
            }
        }
    } else {
        const int hc = std::thread::hardware_concurrency();
        const int threads = hc > 1 ? hc : 1;
        for(int i = 0; i < threads; i++) {
            mThreads.emplace_back(std::bind(&eTextureLoader::threadEntry, this));
        }
    }
}

void eTextureLoader::threadEntry() {
    std::vector<eTextureLoadTask> tasks;
    while(!mQuit) {
        {
            std::unique_lock<std::mutex> lock(mTasksMutex);

            while(!mQuit && mTasks.empty()) {
                mCv.wait(lock);
            }

            if(mTasks.empty()) return;

            const int iMax = mTasks.size();
            for(int i = 0; i < iMax && i < 500; i++) {
                const auto& task = mTasks.front();
                tasks.push_back(task);
                mTasks.pop();
            }
        }
        {
            for(auto& task : tasks) {
                task.fSurface = IMG_Load(task.fPath.c_str());
                if(!task.fSurface) {
                    printf("Unable to load image %s! SDL_image Error: %s\n",
                           task.fPath.c_str(), IMG_GetError());
                }
            }
            {
                std::lock_guard lock(mFinishedTasksMutex);
                for(auto& task : tasks) {
                    mFinishedTasks.push_back(task);
                }
            }
            tasks.clear();
        }
    }
}

void eTextureLoader::queueTask(const eTextureLoadTask& task) {
    if(mUseBMPs) {
        SDL_Surface* surf = nullptr;
        if(mRFile) {
            surf = SDL_LoadBMP_RW(mRFile, 0);
        } else {
            surf = IMG_Load(task.fPath.c_str());
            if(mWFile) SDL_SaveBMP_RW(surf, mWFile, 0);
        }
        if(!surf) {
            printf("Unable to load image %s! SDL_image Error: %s\n",
                   task.fPath.c_str(), IMG_GetError());
        }
        task.fTex->load(mRenderer, surf);
    } else {
        mQuedTasks++;
        std::unique_lock<std::mutex> lock(mTasksMutex);
        mTasks.emplace(task);
        mCv.notify_one();
    }
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
    mFinished += tasks.size();
}

bool eTextureLoader::finished() {
    std::lock_guard lock(mFinishedTasksMutex);
    const int iSize = mFinishedTasks.size();
    return mQuedTasks == iSize + mFinished;
}

void eTextureLoader::waitUntilFinished() {
    while(!finished()) {
        const std::chrono::milliseconds timespan(10);
        std::this_thread::sleep_for(timespan);
        handleFinished();
    }
    handleFinished();
}
