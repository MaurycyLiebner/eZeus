#include "eareshelpaction.h"

#include "characters/actions/emovetoaction.h"
#include "characters/actions/ekillcharacterfinishfail.h"

eAresHelpAction::eAresHelpAction(eCharacter* const c) :
    eGodAction(c, eCharActionType::aresHelpAction) {}


bool eAresHelpAction::decide() {
    switch(mStage) {
    case eAresHelpStage::none:
        mStage = eAresHelpStage::appear;
        appear();
        break;
    case eAresHelpStage::appear:
        mStage = eAresHelpStage::go;
        goToTarget();
        break;
    case eAresHelpStage::go:
        const auto c = character();
        c->kill();
        break;
    }
    return true;
}

bool eAresHelpAction::sHelpNeeded(const eGameBoard& board) {
    const auto& cs = board.conquests();
    return !cs.empty();
}

void eAresHelpAction::read(eReadStream& src) {
    eGodAction::read(src);
    src >> mStage;
}

void eAresHelpAction::write(eWriteStream& dst) const {
    eGodAction::write(dst);
    dst << mStage;
}

void eAresHelpAction::goToTarget() {
    const auto c = character();
    auto& board = eGodAction::board();
    const auto hero = static_cast<eHero*>(c);
    const stdptr<eHero> cptr(hero);
    const auto fail = std::make_shared<eKillCharacterFinishFail>(
                          board, hero);
    const auto finish = std::make_shared<eKillCharacterFinishFail>(
                            board, hero);

    const auto a = e::make_shared<eMoveToAction>(c);
    a->setFailAction(fail);
    a->setFinishAction(finish);
    a->setFindFailAction([cptr]() {
        if(cptr) cptr->kill();
    });
    setCurrentAction(a);
    c->setActionType(eCharacterActionType::walk);

    const auto exitPoint = board.exitPoint();
    if(exitPoint) {
        a->start(exitPoint);
    } else {
        const int bw = board.width();
        const int bh = board.height();
        const auto edgeTile = [bw, bh](eTileBase* const tile) {
            const int tx = tile->dx();
            if(tx == 0 || tx >= bw) return true;
            const int ty = tile->dy();
            if(ty == 0 || ty >= bh) return true;
            return false;
        };
        a->start(edgeTile);
    }
}
