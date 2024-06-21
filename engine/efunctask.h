#ifndef EFUNCTASK_H
#define EFUNCTASK_H

#include "etask.h"

#include <functional>

class eFuncTask : public eTask {
public:
    using eRunFunc = std::function<void(eThreadBoard&)>;
    using eFunc = std::function<void()>;
    eFuncTask(const eRunFunc& runFunc, const eFunc& finishFunc);
protected:
    void run(eThreadBoard& data);
    void finish();
private:
    const eRunFunc mRun;
    const eFunc mFinish;
};

#endif // EFUNCTASK_H
