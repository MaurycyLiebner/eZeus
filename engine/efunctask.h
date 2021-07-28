#ifndef EFUNCTASK_H
#define EFUNCTASK_H

#include "etask.h"

#include <functional>

class eFuncTask : public eTask {
public:
    using eFunc = std::function<void()>;
    eFuncTask(const eFunc& runFunc, const eFunc& finishFunc);
protected:
    void run();
    void finish();
private:
    const eFunc mRun;
    const eFunc mFinish;
};

#endif // EFUNCTASK_H
