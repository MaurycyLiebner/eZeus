#ifndef EPLANNEDACTION_H
#define EPLANNEDACTION_H

#include <functional>

using eAction = std::function<void()>;

class ePlannedAction {
public:
    ePlannedAction(const bool recurring,
                   const int actionTime,
                   const eAction& action);

    void incTime(const int by);
    bool finished() const { return mFinished; }
private:
    const bool mRecurring;
    const int mActionTime;
    const eAction mAction;
    bool mFinished = false;
    int mTime;
};

#endif // EPLANNEDACTION_H
