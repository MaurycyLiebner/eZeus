#include "egodaction.h"

#include "engine/egameboard.h"
#include "esounds.h"

#include "ewaitaction.h"
#include "emovearoundaction.h"
#include "epatrolmoveaction.h"

#include "eiteratesquare.h"

#include "missiles/egodmissile.h"

#include "engine/boardData/eheatmaptask.h"
#include "engine/boardData/eheatmapdivisor.h"
#include "buildings/eheatgetters.h"

#include "emovetoaction.h"

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
    a->setMaxWalkDistance(dist);
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

bool eGodAction::lookForBlessCurse(const int dtime,
                                   int& time, const int freq,
                                   const int range,
                                   const double bless) {
    const auto act = [](eTile* const t) {
        const auto null = static_cast<eTile*>(nullptr);
        const auto b = t->underBuilding();
        if(!b) return null;
        if(!eBuilding::sBlessable(b->type())) return null;
        if(std::abs(b->blessed()) > 0.01) return null;
        return b->centerTile();
    };

    const auto finishA = [bless](eTile* const target) {
        const auto b = target->underBuilding();
        if(!b) return;
        b->setBlessed(bless);
    };
    eCharacterActionType at;
    eGodSound s;
    eTexPtr tex;
    if(bless > 0) {
        at = eCharacterActionType::bless;
        s = eGodSound::santcify;
        tex = &eDestructionTextures::fBless;
    } else {
        at = eCharacterActionType::bless;
        s = eGodSound::curse;
        tex = &eDestructionTextures::fCurse;
    }
    return lookForRangeAction(dtime, time, freq, range,
                              at, act, tex, s, finishA);
}

bool eGodAction::lookForRangeAction(const int dtime,
                                    int& time, const int freq,
                                    const int range,
                                    const eCharacterActionType at,
                                    const eGodAct& act,
                                    const eTexPtr missileTex,
                                    const eGodSound missileSound,
                                    const eFinishFunc& finishA) {
    const auto c = character();
    const auto cat = c->actionType();
    const bool walking = cat == eCharacterActionType::walk;
    if(!walking) return false;
    auto& brd = c->getBoard();
    const auto ct = c->tile();
    if(!ct) return false;
    const int tx = ct->x();
    const int ty = ct->y();

    time += dtime;
    if(time > freq) {
        time -= freq;
        std::vector<eTile*> tiles;
        const int rr = 2*range + 1;
        tiles.reserve(rr*rr);
        for(int i = -range; i <= range; i++) {
            for(int j = -range; j <= range; j++) {
                const int ttx = tx + i;
                const int tty = ty + j;
                const auto t = brd.tile(ttx, tty);
                if(!t) continue;
                tiles.push_back(t);
            }
        }
        std::random_shuffle(tiles.begin(), tiles.end());
        for(const auto t : tiles) {
            const auto tt = act(t);
            if(!tt) continue;

            const auto finishAA = [finishA, tt]() {
                finishA(tt);
            };

            spawnGodMissile(at, missileTex, tt,
                            missileSound, finishAA);
            return true;
        }
    }
    return false;
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

        auto& board = c->getBoard();
        board.ifVisible(c->tile(), [this, sound]() {
            eSounds::playGodSound(mType, sound);
        });

        resumeAction();
    };
    const auto c = character();
    c->setActionType(at);
    {
        const auto ct = c->tile();
        const int tx = ct->x();
        const int ty = ct->y();
        const int ttx = target->x();
        const int tty = target->y();
        const double dx = ttx - tx;
        const double dy = tty - ty;

        const vec2d angleLine{dx, dy};
        const double a = angleLine.angle();
        const double inc = 360./8.;
        const double aa = a + 90;
        const double aaa = aa > 360. ? aa - 360. : aa;
        const int oi = int(std::floor(aaa/inc)) % 8;
        const auto o = static_cast<eOrientation>(oi);
        c->setOrientation(o);
    }
    const auto a = e::make_shared<eWaitAction>(c, finish, finish);
    int time;
    switch(type()) {
    case eGodType::apollo:
    case eGodType::hades:
        time = 300;
        break;
    default:
        time = 500;
        break;
    }

    a->setTime(time);
    setCurrentAction(a);
}

void eGodAction::goToTarget() {
    const auto c = character();
    const stdptr<eGodAction> tptr(this);
    const stdptr<eCharacter> cptr(c);
    const auto hmFinish = [tptr, this, cptr, c](eHeatMap& map) {
        if(!tptr || !cptr) return;
        eHeatMapDivisor divisor(map);
        divisor.divide(10);
        int tx;
        int ty;
        const bool r = divisor.randomHeatTile(tx, ty);
        if(r) {
            const auto tile = closestRoad(tx, ty);
            if(!tile) return setCurrentAction(nullptr);
            const auto tele = [tptr, this, tile]() {
                if(!tptr) return;
                teleport(tile);
            };
            const auto a = e::make_shared<eMoveToAction>(
                               c, tele, [](){});
            a->setFindFailAction(tele);
            a->start(tile);
            setCurrentAction(a);
            c->setActionType(eCharacterActionType::walk);
        } else {
            setCurrentAction(nullptr);
        }
    };
    const auto gt = type();
    const auto hg = eHeatGetters::godLeaning(gt);
    const auto task = new eHeatMapTask(hg, hmFinish);
    auto& board = c->getBoard();
    auto& tp = board.threadPool();
    tp.queueTask(task);
    wait();
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
