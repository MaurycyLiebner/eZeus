#include "eeventloop.h"

eEventLoop* eEventLoop::sInstance = nullptr;

eEventLoop::eEventLoop(const eSlot& loopFunc) :
    mLoopFunc(loopFunc) {
    sInstance = this;
}

eEventLoop::~eEventLoop() {
    sInstance = nullptr;
}

void eEventLoop::setFps(const double fps) {
    mFps = fps;
}

void eEventLoop::exec() {
    using namespace std::chrono;
    using namespace std::chrono_literals;
    while(!mQuit) {
        const auto start = high_resolution_clock::now();

        const auto slots = takeSlots();
        for(const auto& slot : slots) {
            slot();
        }

        if(mLoopFunc) mLoopFunc();

        const auto end = high_resolution_clock::now();
        const duration<double> elapsed = end - start;
        const duration<double> frameTime(1/mFps);
        const auto sleepTime = frameTime - elapsed;
        if(sleepTime.count() > 0) {
            std::this_thread::sleep_for(sleepTime);
        }
    }
}

void eEventLoop::quit() {
    mQuit = true;
}

eEventLoop* eEventLoop::instance() {
    return sInstance;
}

void eEventLoop::queueSlot(const eSlot& slot) {
    sInstance->queueSlotImpl(slot);
}

void eEventLoop::queueSlotImpl(const eSlot& slot) {
    std::lock_guard<std::mutex> lock(mSlotsMtx);
    mSlots.push_back(slot);
}

std::vector<eSlot> eEventLoop::takeSlots() {
    std::lock_guard<std::mutex> lock(mSlotsMtx);
    std::vector<eSlot> slots;
    std::swap(slots, mSlots);
    return slots;
}
