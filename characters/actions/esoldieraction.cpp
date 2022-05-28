#include "esoldieraction.h"

#include "characters/echaracter.h"
#include "engine/egameboard.h"

#include <math.h>

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

void eSoldierAction::increment(const int by) {
    if(!mForceGetters.empty()) {
        vec2d force{0, 0};
        const auto c = character();
        for(const auto& frc : mForceGetters) {
            force += frc.second(c);
        }
        const double len = force.length();
        if(abs(len) > 0.001) {
            const double d = c->speed()*0.005 * by;
            force *= d/len;
            moveBy(force.x, force.y);
            const double radAngle = std::atan2(force.y, force.x);
            const double radAngle2 = radAngle < 0 ? 2*M_PI + radAngle : radAngle;
            const double degAngle = radAngle2 * 180 / M_PI;
            mAngle = mAngle*0.99 + 0.01*degAngle;
            const auto o = angleOrientation(mAngle);
            c->setOrientation(o);
        }
    }
}

int eSoldierAction::addForce(const eForceGetter& force) {
    mForceGetters[mForceId] = force;
    return mForceId++;
}

void eSoldierAction::removeForce(const int id) {
    mForceGetters.erase(id);
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
