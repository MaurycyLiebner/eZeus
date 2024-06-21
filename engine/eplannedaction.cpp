#include "eplannedaction.h"

ePlannedAction::ePlannedAction(const bool recurring,
                               const int actionTime,
                               const eAction& action) :
    mRecurring(recurring), mActionTime(actionTime), mAction(action) {

}

void ePlannedAction::incTime(const int by) {
    if(mFinished) return;
    mTime += by;
    while(mTime > mActionTime) {
        mTime -= mActionTime;
        mAction();
        if(!mRecurring) {
            mFinished = true;
            return;
        }
    }
}
