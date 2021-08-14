#include "efunctask.h"

eFuncTask::eFuncTask(const eRunFunc& runFunc, const eFunc& finishFunc) :
    mRun(runFunc), mFinish(finishFunc) {}

void eFuncTask::run(eThreadData& data) {
    if(mRun) mRun(data);
}

void eFuncTask::finish() {
    if(mFinish) mFinish();
}
