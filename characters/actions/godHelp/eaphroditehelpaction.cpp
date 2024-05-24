#include "eaphroditehelpaction.h"

#include "etilehelper.h"
#include "engine/eplague.h"
#include "buildings/ehousebase.h"
#include "eiteratesquare.h"

eAphroditeHelpAction::eAphroditeHelpAction(eCharacter* const c) :
    eGodAction(c, eCharActionType::aphroditeHelpAction) {}

bool eAphroditeHelpAction::decide() {
    switch(mStage) {
    case eAphroditeHelpStage::none:
        mStage = eAphroditeHelpStage::appear;
        appear();
        break;
    case eAphroditeHelpStage::appear:
        goToTarget();
        break;
    case eAphroditeHelpStage::goTo:
        mStage = eAphroditeHelpStage::populate;
        populate();
        break;
    case eAphroditeHelpStage::populate:
        goToTarget();
        break;
    case eAphroditeHelpStage::disappear:
        const auto c = character();
        c->kill();
        break;
    }
    return true;
}

void eAphroditeHelpAction::read(eReadStream& src) {
    eGodAction::read(src);
    src >> mStage;
}

void eAphroditeHelpAction::write(eWriteStream& dst) const {
    eGodAction::write(dst);
    dst << mStage;
}

bool eAphroditeHelpAction::sHelpNeeded(const eGameBoard& board) {
    const auto bs = board.buildings([](eBuilding* const b) {
        const auto type = b->type();
        return type == eBuildingType::commonHouse ||
               type == eBuildingType::eliteHousing;
    });
    int v = 0;
    for(const auto b : bs) {
        const auto hb = static_cast<eHouseBase*>(b);
        v += hb->vacancies();
    }
    return v > 50;
}

eHouseBase* eAphroditeHelpAction::nearestHouseWithVacancies() {
    const auto c = character();
    const auto cTile = c->tile();
    if(!cTile) return nullptr;
    const int cx = cTile->x();
    const int cy = cTile->y();
    auto& board = this->board();
    const auto bs = board.buildings([](eBuilding* const b) {
        const auto type = b->type();
        return type == eBuildingType::commonHouse ||
               type == eBuildingType::eliteHousing;
    });
    eHouseBase* nearest = nullptr;
    int minDist = __INT_MAX__;
    for(const auto b : bs) {
        const auto hb = static_cast<eHouseBase*>(b);
        const int v = hb->vacancies();
        if(v <= 0) continue;
        const auto centerTile = b->centerTile();
        const int bx = centerTile->x();
        const int by = centerTile->y();
        const int dx = cx - bx;
        const int dy = cy - by;
        const int dist = dx*dx + dy*dy;
        if(minDist > dist) {
            minDist = dist;
            nearest = hb;
        }
    }
    return nearest;
}

void eAphroditeHelpAction::goToTarget() {
    auto& board = this->board();
    const auto nearest = nearestHouseWithVacancies();
    if(!nearest) {
        mStage = eAphroditeHelpStage::disappear;
        disappear();
    } else {
        mStage = eAphroditeHelpStage::goTo;
        const auto ct = nearest->centerTile();
        const int tx = ct->x();
        const int ty = ct->y();
        const auto tile = eTileHelper::closestRoad(tx, ty, board);
        using eGTTT = eGoToTargetTeleport;
        const auto tele = std::make_shared<eGTTT>(board, this);
        goToTile(tile, tele);
    }
}

void eAphroditeHelpAction::populate() {
    const auto c = character();
    const auto house = nearestHouseWithVacancies();
    if(!house) return;
    const auto targetTile = house->centerTile();
    using eGA_LFRAF = eGA_lookForRangeActionFinish;
    const auto finishAttackA = std::make_shared<eGA_LFRAF>(
                                   board(), this);
    const auto act = std::make_shared<eAphroditeHelpAct>(board(), house);
    pauseAction();
    spawnGodMissile(eCharacterActionType::bless,
                    c->type(), targetTile,
                    eGodSound::santcify, act,
                    finishAttackA);
}
