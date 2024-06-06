#include "etakecattleaction.h"

#include "buildings/ecorral.h"

#include "characters/echaracter.h"
#include "characters/ecattle.h"
#include "efollowaction.h"
#include "emovetoaction.h"

eTakeCattleAction::eTakeCattleAction(
        eCharacter* const c, eCorral* const cc) :
    eActionWithComeback(c, eCharActionType::takeCattleAction),
    mCorral(cc) {}

bool eTakeCattleAction::decide() {
    switch(mStage) {
    case eTakeCattleActionStage::none:
    case eTakeCattleActionStage::get: {
        mStage = eTakeCattleActionStage::get;
        goGetCattle();
    } break;
    case eTakeCattleActionStage::goBack: {
        if(mCorral && !mNoCattle) mCorral->addCattle();
        setState(eCharacterActionState::finished);
    } break;
    }
    return true;
}

void eTakeCattleAction::increment(const int by) {
    if(mStage == eTakeCattleActionStage::get) {
        const auto c = character();
        const auto tile = c->tile();
        const auto& chars = tile->characters();
        for(const auto& cc : chars) {
            const auto cct = cc->type();
            if(cct != eCharacterType::cattle3) continue;
            const auto fa = e::make_shared<eFollowAction>(c, cc.get());
            cc->setAction(fa);

            mStage = eTakeCattleActionStage::goBack;
            goBack(eWalkableObject::sCreateDefault());
        }
    }
    eActionWithComeback::increment(by);
}

void eTakeCattleAction::read(eReadStream& src) {
    eActionWithComeback::read(src);
    src >> mStage;
    auto& board = this->board();
    src.readBuilding(&board, [this](eBuilding* const b) {
        mCorral = static_cast<eCorral*>(b);
    });
    src >> mNoCattle;
}

void eTakeCattleAction::write(eWriteStream& dst) const {
    eActionWithComeback::write(dst);
    dst << mStage;
    dst.writeBuilding(mCorral);
    dst << mNoCattle;
}

bool hasCattle(eTileBase* const tile) {
    return tile->hasCharacter([](const eCharacterBase& c) {
        return c.type() == eCharacterType::cattle3;
    });
}

void eTakeCattleAction::goGetCattle() {
    const auto c = character();

    auto aType = std::make_shared<eCharacterType>();

    const auto hha = [aType](eTileBase* const tile) {
        return hasCattle(tile);
    };

    const auto a = e::make_shared<eMoveToAction>(c);
    const stdptr<eCharacter> cptr(c);
    a->setFoundAction([cptr, c]() {
        if(cptr) c->setActionType(eCharacterActionType::walk);
    });
    const stdptr<eTakeCattleAction> tptr(this);
    const auto findFailFunc = [tptr, this]() {
        if(tptr) {
            mNoCattle = true;
            goBack(eWalkableObject::sCreateDefault());
        }
    };
    a->setFindFailAction(findFailFunc);
    a->start(hha);
    setCurrentAction(a);
}
