#include "eapollohelpaction.h"

#include "etilehelper.h"
#include "engine/eplague.h"
#include "buildings/esmallhouse.h"
#include "eiteratesquare.h"

eApolloHelpAction::eApolloHelpAction(eCharacter* const c) :
    eGodAction(c, eCharActionType::apolloHelpAction) {}

bool eApolloHelpAction::decide() {
    switch(mStage) {
    case eApolloHelpStage::none:
        mStage = eApolloHelpStage::appear;
        appear();
        break;
    case eApolloHelpStage::appear:
        goToTarget();
        break;
    case eApolloHelpStage::goTo:
        mStage = eApolloHelpStage::heal;
        heal();
        break;
    case eApolloHelpStage::heal:
        goToTarget();
        break;
    case eApolloHelpStage::disappear:
        const auto c = character();
        c->kill();
        break;
    }
    return true;
}

void eApolloHelpAction::read(eReadStream& src) {
    eGodAction::read(src);
    src >> mStage;
}

void eApolloHelpAction::write(eWriteStream& dst) const {
    eGodAction::write(dst);
    dst << mStage;
}

bool eApolloHelpAction::sHelpNeeded(const eGameBoard& board) {
    const auto& ps = board.plagues();
    return !ps.empty();
}

void eApolloHelpAction::goToTarget() {
    auto& board = this->board();
    const auto& plagues = board.plagues();
    if(plagues.empty()) {
        mStage = eApolloHelpStage::disappear;
        disappear();
    } else {
        const auto p = plagues[0];
        const auto& hs = p->houses();
        if(hs.empty()) {
            mStage = eApolloHelpStage::disappear;
            disappear();
        } else {
            mStage = eApolloHelpStage::goTo;
            const auto h = hs[0];
            const auto ct = h->centerTile();
            const int tx = ct->x();
            const int ty = ct->y();
            const auto tile = eTileHelper::closestRoad(tx, ty, board);
            using eGTTT = eGoToTargetTeleport;
            const auto tele = std::make_shared<eGTTT>(board, this);
            goToTile(tile, tele);
        }
    }
}

eSmallHouse* sClosestPlagueHouseTile(
        eTile* const to, eGameBoard& board) {
    if(!to) return nullptr;
    const int rdx = to->x();
    const int rdy = to->y();
    eSmallHouse* result = nullptr;
    const auto prcsTile = [&](const int i, const int j) {
        const int tx = rdx + i;
        const int ty = rdy + j;
        const auto tt = board.tile(tx, ty);
        if(!tt) return false;
        const auto ub = tt->underBuilding();
        if(const auto ch = dynamic_cast<eSmallHouse*>(ub)) {
            if(ch->plague()) {
                result = ch;
                return true;
            }
        }
        return false;
    };

    for(int k = 0; k < 1000; k++) {
        eIterateSquare::iterateSquare(k, prcsTile, 1);
        if(result) break;
    }
    return result;
}

void eApolloHelpAction::heal() {
    const auto c = character();
    const auto house = sClosestPlagueHouseTile(c->tile(), board());
    const auto targetTile = house->centerTile();
    using eGA_LFRAF = eGA_lookForRangeActionFinish;
    const auto finishAttackA = std::make_shared<eGA_LFRAF>(
                                   board(), this);
    const auto act = std::make_shared<eApolloHelpAct>(board(), house);
    pauseAction();
    spawnGodMissile(eCharacterActionType::bless,
                    c->type(), targetTile,
                    eGodSound::santcify, act,
                    finishAttackA);
}
