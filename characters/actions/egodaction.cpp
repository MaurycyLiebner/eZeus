#include "egodaction.h"

#include "engine/egameboard.h"
#include "esounds.h"

#include "ewaitaction.h"
#include "emovearoundaction.h"
#include "epatrolmoveaction.h"

#include "eiteratesquare.h"

#include "missiles/egodmissile.h"

#include "emovetoaction.h"

eGodAction::eGodAction(eCharacter* const c,
                       const eAction& failAction,
                       const eAction& finishAction) :
    eGodMonsterAction(c, failAction, finishAction),
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

bool eGodAction::lookForBlessCurse(const int dtime,
                                   int& time, const int freq,
                                   const int range,
                                   const double bless) {
    const auto bTarget = std::make_shared<stdptr<eBuilding>>();
    const auto act = [bTarget](eTile* const t) {
        const auto null = static_cast<eTile*>(nullptr);
        const auto b = t->underBuilding();
        if(!b) return null;
        if(!eBuilding::sBlessable(b->type())) return null;
        if(std::abs(b->blessed()) > 0.01) return null;
        *bTarget = b;
        return b->centerTile();
    };

    const auto finishA = [bless, bTarget]() {
        if(!bTarget) return;
        (*bTarget)->setBlessed(bless);
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

bool eGodAction::lookForSoldierAttack(const int dtime, int& time,
                                      const int freq, const int range) {
    const auto c = character();
    const auto charTarget = std::make_shared<stdptr<eCharacter>>();
    const auto act = [c, charTarget](eTile* const t) {
        const auto null = static_cast<eTile*>(nullptr);
        const auto& chars = t->characters();
        if(chars.empty()) return null;
        for(const auto& cc : chars) {
            if(c == cc.get()) continue;
            bool isGod = false;
            eGod::sCharacterToGodType(cc->type(), &isGod);
            if(isGod) continue;
            const bool is = cc->isSoldier();
            if(!is) continue;
            const int pid = cc->playerId();
            if(pid == 1) continue;
            *charTarget = cc;
            return t;
        }
        return null;
    };

    const auto cptr = stdptr<eCharacter>(c);
    const auto finishA = [cptr, charTarget]() {
        if(!cptr) return;
        if(*charTarget) {
            (*charTarget)->killWithCorpse();
        }
    };
    const auto at = eCharacterActionType::fight;
    const auto s = eGodSound::attack;
    const auto tex = eGod::sGodMissile(type());

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
                                    const eFunc& finishMissileA) {
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

            const stdptr<eGodAction> tptr(this);
            const auto finishAttackA = [tptr, this]() {
                if(!tptr) return;
                resumeAction();
            };

            pauseAction();
            spawnGodMissile(at, missileTex, tt,
                            missileSound, finishMissileA,
                            finishAttackA);
            return true;
        }
    }
    return false;
}

void eGodAction::spawnGodMissile(const eCharacterActionType at,
                                 const eTexPtr tex,
                                 eTile* const target,
                                 const eGodSound sound,
                                 const eFunc& finishMissileA,
                                 const eFunc& finishAttackA) {
    const stdptr<eGodAction> tptr(this);
    const auto finish = [tptr, this, tex, target, sound,
                        finishMissileA, finishAttackA, at]() {
        if(!tptr) return;
        const auto c = character();
        const auto g = static_cast<eGod*>(c);
        const auto gt = g->type();
        const auto ct = c->tile();
        const int tx = ct->x();
        const int ty = ct->y();
        const int ttx = target->x();
        const int tty = target->y();
        auto& brd = c->getBoard();
        double h;
        if(at == eCharacterActionType::fight) {
            switch(gt) {
            case eGodType::apollo:
                h = -0.5;
                break;
            default:
                h = 0;
                break;
            }
        } else {
            h = 0;
        }

        const auto m = eMissile::sCreate<eGodMissile>(
                           brd, tx, ty, h,
                           ttx, tty, h, 0);
        m->setTexture(tex);

        m->setFinishAction(finishMissileA);

        if(finishAttackA) finishAttackA();
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
    const int time = eGod::sGodAttackTime(type());
    a->setTime(time);
    setCurrentAction(a);

    auto& board = c->getBoard();
    board.ifVisible(c->tile(), [this, sound]() {
        eSounds::playGodSound(mType, sound);
    });
}

void eGodAction::spawnGodMultipleMissiles(const eCharacterActionType at,
                                          const eTexPtr tex,
                                          eTile* const target,
                                          const eGodSound sound,
                                          const eFunc& finishA,
                                          const int nMissiles) {
    if(nMissiles <= 0) {
        finishA();
        return;
    }
    eFunc finishAA;
    if(nMissiles == 1) {
        finishAA = finishA;
    } else {
        const stdptr<eGodAction> tptr(this);
        finishAA = [tptr, this, at, tex, target, sound, finishA, nMissiles]() {
            if(!tptr) return;
            spawnGodMultipleMissiles(at, tex, target, sound, finishA, nMissiles - 1);
        };
    }
    spawnGodMissile(at, tex, target, sound, nullptr, finishAA);
}

void eGodAction::spawnGodTimedMissiles(const eCharacterActionType at,
                                       const eTexPtr tex,
                                       eTile* const target,
                                       const eGodSound sound,
                                       const eFunc& finishA,
                                       const int time) {
    const int atime = eGod::sGodAttackTime(type());
    const int n = std::round(double(time)/atime);
    spawnGodMultipleMissiles(at, tex, target, sound, finishA, n);
}

void eGodAction::fightGod(eGod* const g, const eFunc& finishAttackA) {
    const auto at = eCharacterActionType::fight;
    const auto s = eGodSound::attack;
    const auto tex = eGod::sGodMissile(type());

    spawnGodTimedMissiles(at, tex, g->tile(),
                          s, finishAttackA, 6000);
}

void eGodAction::goToTarget() {
    const auto gt = type();
    const auto hg = eHeatGetters::godLeaning(gt);
    const stdptr<eGodAction> tptr(this);
    const auto tele = [tptr, this](eTile* const tile) {
        if(!tptr) return;
        teleport(tile);
    };
    eGodMonsterAction::goToTarget(hg, tele);
}
