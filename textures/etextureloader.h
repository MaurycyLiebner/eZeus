#ifndef ETEXTURELOADER_H
#define ETEXTURELOADER_H

#include <queue>
#include <thread>
#include <mutex>
#include <functional>
#include <condition_variable>

#include "etexture.h"

struct eTextureLoadTask {
    std::shared_ptr<eTexture> fTex;
    std::string fPath;

    SDL_Surface* fSurface = nullptr;
};

class eTextureLoader {
public:
    eTextureLoader(SDL_Renderer* const renderer);
    ~eTextureLoader();

    void initialize(const std::string& path);

    void queueTask(const eTextureLoadTask& task);
    void waitUntilFinished();

    SDL_Renderer* renderer() const { return mRenderer; }
private:
    void threadEntry();

    void handleFinished();
    bool finished();

    const bool mUseBMPs = false;

    SDL_RWops* mWFile = nullptr;
    SDL_RWops* mRFile = nullptr;

    int mFinished = 0;
    int mQuedTasks = 0;

    bool mQuit = false;

    SDL_Renderer* const mRenderer;

    std::mutex mTasksMutex;
    std::condition_variable mCv;
    std::queue<eTextureLoadTask> mTasks;

    std::mutex mFinishedTasksMutex;
    std::vector<eTextureLoadTask> mFinishedTasks;

    std::vector<std::thread> mThreads;
};

#endif // ETEXTURELOADER_H
