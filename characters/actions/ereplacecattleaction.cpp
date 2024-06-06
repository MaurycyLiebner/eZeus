#include "ereplacecattleaction.h"

#include "emovetoaction.h"

eReplaceCattleAction::eReplaceCattleAction(
        eCharacter* const c, eCharacter* const cc) :
    eActionWithComeback(c, eCharActionType::replaceCattleAction),
    mCattle(cc) {
    setFinishOnComeback(true);
}

bool eReplaceCattleAction::decide() {
    goCattle();
    return true;
}

void eReplaceCattleAction::read(eReadStream& src) {
    eActionWithComeback::read(src);
    auto& board = this->board();
    src.readCharacter(&board, [this](eCharacter* const c) {
        mCattle = c;
    });
}

void eReplaceCattleAction::write(eWriteStream& dst) const {
    eActionWithComeback::write(dst);
    dst.writeCharacter(mCattle);
}

void eReplaceCattleAction::goCattle() {
    const auto c = character();

    const auto hha = [](eThreadTile* const tile) {
        const auto ub = tile->underBuilding();
        const auto ubt = ub.type();
        if(ubt != eBuildingType::cattle) return false;
        return !ub.hasAnimal();
    };

    const auto a = e::make_shared<eMoveToAction>(c);
    const stdptr<eCharacter> cptr(c);
    a->setFoundAction([cptr, c]() {
        if(cptr) c->setActionType(eCharacterActionType::walk);
    });
    const stdptr<eReplaceCattleAction> tptr(this);
    const auto findFailFunc = [tptr, this]() {
        if(tptr) goBack(eWalkableObject::sCreateDefault());
    };
    a->setFindFailAction(findFailFunc);
    const auto finish = std::make_shared<eRC_finishAction>(
                            board(), this, c, mCattle);
    a->setFinishAction(finish);
    a->start(hha);
    setCurrentAction(a);
}

void eRC_finishAction::call() {
    if(mButcherA) {
        const auto walkable = eWalkableObject::sCreateDefault();
        mButcherA->goBack(walkable);
    }
    if(!mCattle) return;
    const auto c = mCattle.get();

    const auto hha = [](eThreadTile* const tile) {
        const auto ub = tile->underBuilding();
        const auto ubt = ub.type();
        if(ubt != eBuildingType::cattle) return false;
        return !ub.hasAnimal();
    };

    const auto a = e::make_shared<eMoveToAction>(c);

    const auto finish = std::make_shared<eRC_finishWalkingAction>(
                            board(), c);
    a->setFinishAction(finish);
    a->start(hha);
    c->setAction(a);
}

void eRC_finishWalkingAction::call() {
    const auto t = mCattle->tile();
    if(!t) return;
    const auto ub = t->underBuilding();
    if(!ub) return;
    const auto ubt = ub->type();
    if(ubt != eBuildingType::cattle) return;
    const auto ab = static_cast<eAnimalBuilding*>(ub);
    ab->setAnimal(mCattle);
    const int tx = t->x();
    const int ty = t->y();
    const auto walkable = eWalkableObject::sCreateFertile();
    const auto a = e::make_shared<eAnimalAction>(
                       mCattle, tx, ty, walkable);
    mCattle->setAction(a);
}
