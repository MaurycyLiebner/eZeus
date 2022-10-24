#include "egodaction.h"

#include "engine/egameboard.h"
#include "esounds.h"

#include "ewaitaction.h"
#include "emovearoundaction.h"
#include "epatrolmoveaction.h"

#include "eiteratesquare.h"

#include "missiles/egodmissile.h"

eGodAction::eGodAction(eCharacter* const c,
                       const eAction& failAction,
                       const eAction& finishAction) :
    eComplexAction(c, failAction, finishAction),
    mType(eGod::sCharacterToGodType(c->type())) {

}

void eGodAction::appear(const eFunc& finish) {
    if(type() == eGodType::hermes) {
        hermesRun(true);
    } else {
        const auto c = character();
        c->setActionType(eCharacterActionType::appear);
        const auto a = e::make_shared<eWaitAction>(c, finish, finish);
        a->setTime(500);
        setCurrentAction(a);
        playAppearSound();
    }
}

void eGodAction::disappear(const bool die,
                           const eFunc& finish) {
    if(type() == eGodType::hermes) {
        hermesRun(false);
    } else {
        const auto c = character();
        c->setActionType(die ? eCharacterActionType::die :
                               eCharacterActionType::disappear);
        const auto a = e::make_shared<eWaitAction>(c, finish, finish);
        a->setTime(500);
        setCurrentAction(a);
        playDisappearSound();
    }
}

void eGodAction::teleport(eTile* const tile) {
    const stdptr<eGodAction> tptr(this);
    disappear(false, [tptr, this, tile]() {
        if(!tptr) return;
        const auto c = character();
        c->changeTile(tile);
        appear();
    });
}

void eGodAction::moveAround(const eAction& finishAct,
                            const int time) {
    const auto c = character();
    c->setActionType(eCharacterActionType::walk);
    const auto t = c->tile();
    const int tx = t->x();
    const int ty = t->y();
    const auto a = e::make_shared<eMoveAroundAction>(
                       c, finishAct, finishAct, tx, ty,
                       eMoveAroundAction::sDefaultWalkable);
    a->setTime(time);
    setCurrentAction(a);
}

void eGodAction::patrol(const eAction& finishAct,
                        const int dist) {
    const auto c = character();
    c->setActionType(eCharacterActionType::walk);
    const auto a = e::make_shared<ePatrolMoveAction>(
                       c, finishAct, finishAct);
    a->setMaxDistance(dist);
    setCurrentAction(a);
}

void eGodAction::playAppearSound() {
    const auto c = character();
    auto& board = c->getBoard();
    board.ifVisible(c->tile(), [this]() {
        eSounds::playGodSound(type(), eGodSound::appear);
    });
}

void eGodAction::playDisappearSound() {
    const auto c = character();
    auto& board = c->getBoard();
    board.ifVisible(c->tile(), [this]() {
        eSounds::playGodSound(type(), eGodSound::disappear);
    });
}

void eGodAction::hermesRun(const bool appear) {
    const auto c = character();
    c->setActionType(eCharacterActionType::appear);
    c->setSpeed(2.0);
    const auto tile = c->tile();
    const stdptr<eGodAction> tptr(this);
    const auto finish = [tptr, c, appear]() {
        if(!tptr) return;
        c->setSpeed(1.);
        if(!appear) tptr->playDisappearSound();
    };
    if(tile->hasRoad()) {
        patrol(finish, 20);
    } else {
        moveAround(finish, 1000);
    }
    if(appear) playAppearSound();
}

void eGodAction::randomPlaceOnBoard() {
    const auto c = character();
    auto& board = c->getBoard();
    const int w = board.width();
    const int h = board.height();
    const int rdx = rand() % w;
    const int rdy = rand() % h;
    const auto tile = closestRoad(rdx, rdy);
    if(!tile) return;
    c->changeTile(tile);
}

eTile* eGodAction::closestRoad(const int rdx, const int rdy) const {
    const auto c = character();
    auto& board = c->getBoard();
    eTile* roadTile = nullptr;
    eTile* plainTile = nullptr;
    const auto prcsTile = [&](const int i, const int j) {
        const int tx = rdx + i;
        const int ty = rdy + j;
        const auto tt = board.dtile(tx, ty);
        if(!tt) return false;
        if(tt->hasRoad()) {
            roadTile = tt;
            return true;
        } else if(!plainTile && tt->walkable()) {
            plainTile = tt;
        }
        return false;
    };

    for(int k = 0; k < 1000; k++) {
        eIterateSquare::iterateSquare(k, prcsTile, 1);
        if(roadTile) break;
    }

    const auto tile = roadTile ? roadTile : plainTile;
    return tile;
}

void eGodAction::lookForBlessCurse(const int dtime,
                                   int& time, const int freq,
                                   const int range, const double bless) {
    const auto c = character();
    const auto at = c->actionType();
    const bool walking = at == eCharacterActionType::walk;
    auto& brd = c->getBoard();
    const auto ct = c->tile();
    if(ct && walking) {
        const int tx = ct->x();
        const int ty = ct->y();

        time += dtime;
        if(time > freq) {
            time -= freq;
            bool found = false;
            for(int i = -range; i <= range && !found; i++) {
                for(int j = -range; j <= range && !found; j++) {
                    const int ttx = tx + i;
                    const int tty = ty + j;
                    const auto t = brd.tile(ttx, tty);
                    if(!t) continue;
                    const auto b = t->underBuilding();
                    if(!b) continue;
                    if(!eBuilding::sBlessable(b->type())) continue;
                    if((bless > 0) == (b->blessed() > 0)) continue;
                    blessCurse(b, bless);
                    found = true;
                }
            }
        }
    }
}

void eGodAction::blessCurse(eBuilding* const b, const double bb) {
    eTexPtr texPtr;
    eGodSound sound;
    if(bb > 0) {
        texPtr = &eDestructionTextures::fBless;
        sound = eGodSound::santcify;
    } else {
        texPtr = &eDestructionTextures::fCurse;
        sound = eGodSound::curse;
    }

    const stdptr<eBuilding> bptr(b);
    const auto finishA = [bptr, bb]() {
        if(!bptr) return;
        bptr->setBlessed(bb);
    };

    spawnGodMissile(eCharacterActionType::bless,
                    texPtr, b->centerTile(),
                    sound, finishA);
}

void eGodAction::spawnGodMissile(const eCharacterActionType at,
                                 const eTexPtr tex,
                                 eTile* const target,
                                 const eGodSound sound,
                                 const eFunc& finishA) {
    pauseAction();
    const stdptr<eGodAction> tptr(this);
    const auto finish = [tptr, tex, target, sound, finishA, this]() {
        if(!tptr) return;
        const auto c = character();
        const auto ct = c->tile();
        const int tx = ct->x();
        const int ty = ct->y();
        const int ttx = target->x();
        const int tty = target->y();
        auto& brd = c->getBoard();
        const auto m = eMissile::sCreate<eGodMissile>(
                           brd, tx, ty, 0.5,
                           ttx, tty, 0.5, 0);
        m->setTexture(tex);

        m->setFinishAction(finishA);

        {
            m->incTime(1);
            const double a = m->angle();
            const double inc = 360./8.;
            const double aa = a + 90;
            const double aaa = aa > 360. ? aa - 360. : aa;
            const int oi = int(std::floor(aaa/inc)) % 8;
            const auto o = static_cast<eOrientation>(oi);
            c->setOrientation(o);
        }

        auto& board = c->getBoard();
        board.ifVisible(c->tile(), [this, sound]() {
            eSounds::playGodSound(mType, sound);
        });

        resumeAction();
    };
    const auto c = character();
    c->setActionType(at);
    const auto a = e::make_shared<eWaitAction>(c, finish, finish);
    a->setTime(500);
    setCurrentAction(a);
}

void eGodAction::pauseAction() {
    mPausedAction = currentAction()->ref<eCharacterAction>();
    const auto c = character();
    mOrientation = c->orientation();

    pause();
}

void eGodAction::resumeAction() {
    setCurrentAction(mPausedAction);
    mPausedAction = nullptr;
    const auto c = character();
    c->setOrientation(mOrientation);

    resume();
}
