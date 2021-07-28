#include "efunctask.h"

eFuncTask::eFuncTask(const eFunc& runFunc, const eFunc& finishFunc) :
    mRun(runFunc), mFinish(finishFunc) {}

void eFuncTask::run() {
    if(mRun) mRun();
}

void eFuncTask::finish() {
    if(mFinish) mFinish();
}
