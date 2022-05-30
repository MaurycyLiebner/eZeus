#include "esoldieraction.h"

#include "characters/esoldier.h"
#include "engine/egameboard.h"

#include <math.h>

#include "edieaction.h"

double angle(const vec2d& force) {
    const double radAngle = std::atan2(force.y, force.x);
    const double radAngle2 = radAngle < 0 ? 2*M_PI + radAngle : radAngle;
    const double degAngle = radAngle2 * 180 / M_PI;
    return degAngle;
}

eOrientation angleOrientation(const double degAngle) {
    const double h45 = 0.5*45.;
    eOrientation o;
    if(degAngle > h45 && degAngle < h45 + 45) {
        o = eOrientation::bottom;
    } else if(degAngle > h45 + 45 && degAngle < h45 + 90) {
        o = eOrientation::bottomLeft;
    } else if(degAngle > h45 + 90 && degAngle < h45 + 135) {
        o = eOrientation::left;
    } else if(degAngle > h45 + 135 && degAngle < h45 + 180) {
        o = eOrientation::topLeft;
    } else if(degAngle > h45 + 180 && degAngle < h45 + 225) {
        o = eOrientation::top;
    } else if(degAngle > h45 + 225 && degAngle < h45 + 270) {
        o = eOrientation::topRight;
    } else if(degAngle > h45 + 270 && degAngle < h45 + 315) {
        o = eOrientation::right;
    } else {
        o = eOrientation::bottomRight;
    }
    return o;
}

eOrientation orientation(const vec2d& force) {
    const double deg = angle(force);
    return angleOrientation(deg);
}

void eSoldierAction::increment(const int by) {
    const auto c = character();
    const auto& brd = c->getBoard();
    if(mAttack) {
        mAttackTime += by;
        bool finishAttack = !mAttackTarget || mAttackTime > 1000;
        if(mAttackTarget && !mAttackTarget->dead()) {
            const int att = by*c->attack();
            const bool d = mAttackTarget->defend(att);
            if(d) {
                const auto a = e::make_shared<eDieAction>(mAttackTarget, []() {});
                mAttackTarget->setAction(a);
                finishAttack = true;
            }
        }
        if(finishAttack) {
            mAttack = false;
            mAttackTarget = nullptr;
            mAttackTime = 0;
        } else {
            return;
        }
    }
    const auto ct = c->tile();
    const int tx = ct->x();
    const int ty = ct->y();
    const int pid = c->playerId();
    vec2d cpos{c->absX(), c->absY()};
    for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
            const auto t = brd.tile(tx + i, ty + j);
            if(!t) continue;
            const auto& chars = t->characters();
            for(const auto& cc : chars) {
                if(!cc->isSoldier()) continue;
                if(cc->playerId() == pid) continue;
                if(cc->dead()) continue;
                vec2d ccpos{cc->absX(), cc->absY()};
                vec2d posdif = ccpos - cpos;
                const double dist = posdif.length();
                if(dist > 0.5) continue;
                mAttackTarget = cc;
                mAttack = true;
                mAttackTime = 0;
                c->setActionType(eCharacterActionType::fight);
                const auto o = orientation(posdif);
                c->setOrientation(o);
                return;
            }
        }
    }
    if(!mForceGetters.empty()) {
        vec2d force{0, 0};
        const auto frcs = mForceGetters;
        for(const auto& frc : frcs) {
            force += frc.second(c);
        }
        const double len = force.length();
        if(abs(len) > 0.001) {
            const double d = c->speed()*0.005 * by;
            force *= d/len;
            moveBy(force.x, force.y);
            const auto degAngle = angle(force);
            mAngle = mAngle*0.9 + 0.1*degAngle;
            const auto o = angleOrientation(mAngle);
            c->setOrientation(o);
        } else {
            c->setActionType(eCharacterActionType::walk);
        }
    } else {
    }
}

int eSoldierAction::addForce(const eForceGetter& force,
                             const eForceType type) {
    switch(type) {
    case eForceType::regular:
        mForceGetters[mForceId] = force;
        return mForceId++;
    case eForceType::reserved1:
        mForceGetters[-1] = force;
        return -1;
    }
}

void eSoldierAction::removeForce(const int id) {
    mForceGetters.erase(id);
}

void eSoldierAction::removeForce(const eForceType type) {
    switch(type) {
    case eForceType::regular:
        break;
    case eForceType::reserved1:
        mForceGetters.erase(-1);
        break;
    }
}

void eSoldierAction::moveBy(const double dx, const double dy) {
    const auto c = character();
    const auto ct = c->tile();
    if(!ct) return;
    const int tx = ct->x();
    const int ty = ct->y();
    const double newX = tx + c->x() + dx;
    const double newY = ty + c->y() + dy;
    const int newIX = floor(newX);
    const int newIY = floor(newY);
    const auto& brd = c->getBoard();
    const auto newT = brd.tile(newIX, newIY);
    if(!newT) return;
    c->changeTile(newT);
    const double newFX = newX - newIX;
    const double newFY = newY - newIY;
    c->setX(newFX);
    c->setY(newFY);
}
