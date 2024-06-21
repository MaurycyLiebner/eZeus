#include "efollowaction.h"

#include "../echaracter.h"

#include "emovepathaction.h"
#include "walkable/ewalkableobject.h"

eFollowAction::eFollowAction(eCharacter* const f,
                             eCharacter* const c,
                             const eCharActionType type) :
    eComplexAction(c, type),
    mFollow(f) {
    if(f) c->setSpeed(f->speed());
    c->setActionType(eCharacterActionType::stand);
}

eFollowAction::eFollowAction(eCharacter* const f,
                             eCharacter* const c) :
    eFollowAction(f, c, eCharActionType::followAction) {}

eFollowAction::eFollowAction(eCharacter* const c) :
    eFollowAction(nullptr, c) {}

void eFollowAction::setDistance(const int d) {
    mDistance = d;
}

void eFollowAction::read(eReadStream& src) {
    eComplexAction::read(src);
    src.readCharacter(&board(), [this](eCharacter* const c) {
        mFollow = c;
        const auto cc = character();
        cc->setSpeed(c->speed());
    });
    src >> mDistance;
    int s;
    src >> s;
    for(int i = 0; i < s; i++) {
        ePathNode n;
        n.fTile = src.readTile(board());
        src >> n.fO;
        mTiles.push_back(n);
    }
}

void eFollowAction::write(eWriteStream& dst) const {
    eComplexAction::write(dst);
    dst.writeCharacter(mFollow);
    dst << mDistance;
    dst << mTiles.size();
    for(const auto& t : mTiles) {
        dst.writeTile(t.fTile);
        dst << t.fO;
    }
}

eOrientation sOrientation(eTile* const from,
                          eTile* const to) {
    const int dx = to->x() - from->x();
    const int dy = to->y() - from->y();
    if(dx < 0 && dy < 0) return eOrientation::top;
    else if(dx > 0 && dy > 0) return eOrientation::bottom;
    else if(dx > 0 && dy < 0) return eOrientation::right;
    else if(dx < 0 && dy > 0) return eOrientation::left;
    else if(dy < 0) return eOrientation::topRight;
    else if(dx > 0) return eOrientation::bottomRight;
    else if(dy > 0) return eOrientation::bottomLeft;
    else if(dx < 0) return eOrientation::topLeft;
    return eOrientation::topLeft;
}

void eFollowAction::increment(const int by) {
    const auto ft = mFollow ? mFollow->tile() : nullptr;
    const bool dead = mFollow ? mFollow->dead() : false;
    const auto c = character();
    if(!ft || dead) {
        const auto ca = currentAction();
        if(ca) return eComplexAction::increment(by);
        if(mTiles.empty()) {
            return setState(eCharacterActionState::finished);
        } else {
            const auto walkable = eWalkableObject::sCreateAll();
            std::vector<eOrientation> path;
            path.reserve(mTiles.size());
            for(int i = 0; i < mDistance && !mTiles.empty(); i++) {
                const auto& f = mTiles.front();
                path.push_back(f.fO);
                mTiles.pop_front();
            }
            mTiles = {};
            const auto a = e::make_shared<eMovePathAction>(c, path, walkable);
            setCurrentAction(a);
        }
        return eComplexAction::increment(by);
    }
    if(!mTiles.empty()) {
        auto& b = mTiles.back();
        if(ft == b.fTile) {
            const auto at = mFollow->actionType();
            if(at == eCharacterActionType::walk ||
               at == eCharacterActionType::carry) {
                b.fO = mFollow->orientation();
            }
            eComplexAction::increment(by);
            return;
        }
        b.fO = sOrientation(b.fTile, ft);
    }
    mTiles.push_back({ft, mFollow->orientation()});
    const int nt = mTiles.size();
    if(nt < mDistance + 2) return;
    if(nt > mDistance + 2) mTiles.pop_front();
    const auto pn = mTiles.front();
    c->setActionType(eCharacterActionType::walk);
    c->changeTile(pn.fTile);
    c->setOrientation(pn.fO);
    const auto walkable = eWalkableObject::sCreateAll();
    const std::vector<eOrientation> path = {pn.fO};
    const auto a = e::make_shared<eMovePathAction>(c, path, walkable);
    setCurrentAction(a);
    eComplexAction::increment(by);
}
