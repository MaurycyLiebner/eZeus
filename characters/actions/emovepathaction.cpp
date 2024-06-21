#include "emovepathaction.h"

#include "characters/echaracter.h"

eMovePathAction::eMovePathAction(eCharacter* const c,
                                 const std::vector<eOrientation>& path,
                                 const stdsptr<eWalkableObject>& tileWalkable) :
    eMoveAction(c, tileWalkable, eCharActionType::movePathAction),
    mTurns(path) {
}

eMovePathAction::eMovePathAction(eCharacter* const c) :
    eMovePathAction(c, {}, nullptr) {}

eCharacterActionState eMovePathAction::nextTurn(eOrientation& turn) {
    if(mTurns.empty()) return eCharacterActionState::finished;
    if(mWalkedDistance++ > mMaxDistance) {
        return eCharacterActionState::finished;
    }
    turn = mTurns.back();
    mTurns.pop_back();
    const auto c = character();
    const auto t = c->tile();
    if(!t) return eCharacterActionState::failed;
    const auto tt = t->neighbour(turn);
    if(!tt) return eCharacterActionState::failed;
    return eCharacterActionState::running;
}

void eMovePathAction::read(eReadStream& src) {
    eMoveAction::read(src);
    int n;
    src >> n;
    for(int i = 0; i < n; i++) {
        auto& o = mTurns.emplace_back();
        src >> o;
    }
    src >> mMaxDistance;
    src >> mWalkedDistance;
}

void eMovePathAction::write(eWriteStream& dst) const {
    eMoveAction::write(dst);
    dst << mTurns.size();
    for(const auto t : mTurns) {
        dst << t;
    }
    dst << mMaxDistance;
    dst << mWalkedDistance;
}
