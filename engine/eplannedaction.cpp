#include "eplannedaction.h"

#include "fileIO/ereadstream.h"
#include "fileIO/ewritestream.h"

#include "eregrowforestaction.h"
#include "ecolonymonumentaction.h"

ePlannedAction::ePlannedAction(const bool recurring,
                               const int actionTime,
                               const ePlannedActionType type) :
    mType(type), mRecurring(recurring),
    mActionTime(actionTime) {}

ePlannedAction::ePlannedAction(const ePlannedActionType type) :
    mType(type) {}

ePlannedAction::~ePlannedAction() {}

void ePlannedAction::read(eReadStream& src, eGameBoard& board) {
    (void)board;
    src >> mRecurring;
    src >> mActionTime;
    src >> mFinished;
    src >> mTime;
}

void ePlannedAction::write(eWriteStream& dst) const {
    dst << mRecurring;
    dst << mActionTime;
    dst << mFinished;
    dst << mTime;
}

ePlannedAction* ePlannedAction::sCreate(const ePlannedActionType type) {
    switch(type) {
    case ePlannedActionType::regrowForest:
        return new eRegrowForestAction();
    case ePlannedActionType::colonyMonument:
        return new eColonyMonumentAction();
    }
}

void ePlannedAction::incTime(const int by, eGameBoard& board) {
    if(mFinished) return;
    mTime += by;
    while(mTime > mActionTime) {
        mTime -= mActionTime;
        trigger(board);
        if(!mRecurring) {
            mFinished = true;
            return;
        }
    }
}
