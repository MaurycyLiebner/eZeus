#ifndef EGROWERACTION_H
#define EGROWERACTION_H

#include "eactionwithcomeback.h"

#include "characters/egrower.h"
#include "buildings/egrowerslodge.h"
#include "buildings/eresourcebuilding.h"

class eGrowerAction : public eActionWithComeback {
    friend class eGRA_workOnDecisionFinish;
public:
    eGrowerAction(const eGrowerType type,
                  eGrowersLodge* const lodge,
                  eCharacter* const c);
    eGrowerAction(eCharacter* const c);

    bool decide() override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
private:
    bool findResourceDecision();
    void workOnDecision(eTile* const tile);
    void goBackDecision();
    void waitDecision();

    eGrowerType mType;
    eGrower* mGrower = nullptr;
    eGrowersLodge* mLodge = nullptr;

    bool mFinishOnce = true;

    int mGroomed = 0;
    bool mNoResource = false;
};

class eGRA_workOnDecisionFinish : public eCharActFunc {
public:
    eGRA_workOnDecisionFinish(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::GRA_workOnDecisionFinish) {}
    eGRA_workOnDecisionFinish(eGameBoard& board, eGrowerAction* const ca,
                              eTile* const tile, const eBuildingType type) :
        eCharActFunc(board, eCharActFuncType::GRA_workOnDecisionFinish),
        mTptr(ca), mTile(tile), mType(type) {}

    void call() {
        mTile->setBusy(false);
        if(!mTptr) return;
        const auto t = mTptr.get();
        if(const auto b = mTile->underBuilding()) {
            if(const auto bb = dynamic_cast<eResourceBuilding*>(b)) {
                bb->workOn();
                const int took = bb->takeResource(1);
                if(took > 0) {
                    if(mType == eBuildingType::vine) {
                        t->mGrower->incGrapes();
                    } else if(mType == eBuildingType::oliveTree) {
                        t->mGrower->incOlives();
                    } else if(mType == eBuildingType::orangeTree) {
                        t->mGrower->incOranges();
                    }
                    t->mGroomed += 5;
                }
            }
        }
        t->mGroomed++;
    }

    void read(eReadStream& src) {
        src.readCharacterAction(&board(), [this](eCharacterAction* const ca) {
            mTptr = static_cast<eGrowerAction*>(ca);
        });
        mTile = src.readTile(board());
        src >> mType;
    }

    void write(eWriteStream& dst) const {
        dst.writeCharacterAction(mTptr);
        dst.writeTile(mTile);
        dst << mType;
    }
private:
    stdptr<eGrowerAction> mTptr;
    eTile* mTile = nullptr;
    eBuildingType mType;
};

class eGRA_workOnDecisionDeleteFail : public eCharActFunc {
public:
    eGRA_workOnDecisionDeleteFail(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::GRA_workOnDecisionDeleteFail) {}
    eGRA_workOnDecisionDeleteFail(eGameBoard& board, eTile* const tile) :
        eCharActFunc(board, eCharActFuncType::GRA_workOnDecisionDeleteFail),
        mTile(tile) {}

    void call() {
        mTile->setBusy(false);
    }

    void read(eReadStream& src) {
        mTile = src.readTile(board());
    }

    void write(eWriteStream& dst) const {
        dst.writeTile(mTile);
    }
private:
    eTile* mTile = nullptr;
};

#endif // EGROWERACTION_H
