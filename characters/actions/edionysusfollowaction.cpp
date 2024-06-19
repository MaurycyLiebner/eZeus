#include "edionysusfollowaction.h"

#include "characters/echaracter.h"

void eDionysusFollowAction::setFollower(eCharacter* const f) {
    mFollower = f;
}

bool eDionysusFollowAction::sShouldFollow(const eCharacterType c) {
    switch(c) {
    case eCharacterType::settler:
    case eCharacterType::homeless:
    case eCharacterType::shepherd:
    case eCharacterType::goatherd:
    case eCharacterType::grower:
    case eCharacterType::peddler:
    case eCharacterType::lumberjack:
    case eCharacterType::bronzeMiner:
    case eCharacterType::silverMiner:
    case eCharacterType::artisan:
    case eCharacterType::hunter:
    case eCharacterType::gymnast:
    case eCharacterType::philosopher:
    case eCharacterType::actor:
    case eCharacterType::competitor:
    case eCharacterType::scholar:
    case eCharacterType::astronomer:
    case eCharacterType::inventor:
    case eCharacterType::curator:
    case eCharacterType::taxCollector:
    case eCharacterType::watchman:
    case eCharacterType::waterDistributor:
    case eCharacterType::fireFighter:
    case eCharacterType::healer:
    case eCharacterType::cartTransporter:
        return true;
    default:
        return false;
    }
    return false;
}

void eDionysusFollowAction::increment(const int by) {
    eFollowAction::increment(by);
    if(mFollower) return;
    auto& board = this->board();
    const auto c = character();
    const auto tile = c->tile();
    const auto& chars = tile->characters();
    for(const auto& cc : chars) {
        const auto cType = cc->type();
        const bool r = sShouldFollow(cType);
        if(!r) continue;
        const auto fa = e::make_shared<eDionysusFollowAction>(c, cc.get());
        cc->setAction(fa);
        const auto killA = std::make_shared<eChar_killWithCorpseFinish>(
                               board, cc.get(), true);
        fa->setFinishAction(killA);
        fa->setFailAction(killA);
        mFollower = cc.get();
        break;
    }
}
