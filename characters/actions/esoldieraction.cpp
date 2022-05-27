#include "esoldieraction.h"

#include "characters/echaracter.h"
#include "engine/egameboard.h"

#include <math.h>

void eSoldierAction::increment(const int by) {
    if(!mForceGetters.empty()) {
        eForce force{0, 0};
        for(const auto& frc : mForceGetters) {
            force += frc.second();
        }
        const auto c = character();
        const double len = sqrt(force.fDx*force.fDx + force.fDy*force.fDy);
        if(abs(len) > 0.001) {
            const double d = c->speed()*0.005 * by;
            force.fDx *= d/len;
            force.fDy *= d/len;
            moveBy(force.fDx, force.fDy);
            const double radAngle = std::atan2(force.fDy, force.fDx);
            const double radAngle2 = radAngle < 0 ? 2*M_PI + radAngle : radAngle;
            const double degAngle = radAngle2 * 180 / M_PI;
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
