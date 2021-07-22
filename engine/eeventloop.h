#ifndef EEVENTLOOP_H
#define EEVENTLOOP_H

#include <queue>
#include <functional>
#include <mutex>
#include <thread>

using eSlot = std::function<void()>;

class eEventLoop {
public:
    eEventLoop(const eSlot& loopFunc);
    ~eEventLoop();

    void setFps(const double fps);
    void exec();
    void quit();

    static eEventLoop* instance();
    static void queueSlot(const eSlot& slot);
private:
    static eEventLoop* sInstance;

    void queueSlotImpl(const eSlot& slot);
    std::vector<eSlot> takeSlots();

    const eSlot mLoopFunc;

    std::mutex mSlotsMtx;
    std::vector<eSlot> mSlots;

    double mFps;

    bool mQuit = false;
};

#endif // EEVENTLOOP_H
