#include "etask.h"

#include "eeventloop.h"

eTask::eTask() {}

eTask::~eTask() {}

void eTask::exec() {
    run();
    eEventLoop::queueSlot([this]() {
        finish();
        delete this;
    });
}
