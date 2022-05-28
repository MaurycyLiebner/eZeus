#include "eforce.h"

#include "engine/egameboard.h"

vec2d eForceHelpers::avoidUnwalkableForce(eCharacter* const c) {
    const auto ct = c->tile();
    const auto& brd = c->getBoard();
    const auto cx = c->x();
    const auto cy = c->y();
    vec2d f{0., 0.};
    const double mult = 10.;
    if(cx > 0.5) { // bottom-right
        const auto cxt = brd.tile(ct->x() + 1, ct->y());
        if(cxt) {
            const auto ub = cxt->walkable();
            const double s = mult*(cx - 0.5);
            if(ub) f += vec2d{-s, 0.};
        }
        if(cy < 0.5) { // right
            const auto cxyt = brd.tile(ct->x() + 1, ct->y() - 1);
            if(cxyt) {
                const auto ub = cxyt->walkable();
                const double s = mult*(cx - 0.5)*(0.5 - cy);
                if(ub) f += vec2d{-s, s};
            }
        } else { // bottom
            const auto cxyt = brd.tile(ct->x() + 1, ct->y() + 1);
            if(cxyt) {
                const auto ub = cxyt->walkable();
                const double s = mult*(cx - 0.5)*(cy - 0.5);
                if(ub) f += vec2d{-s, -s};
            }
        }
    } else { // top-left
        const auto cxt = brd.tile(ct->x() - 1, ct->y());
        if(cxt) {
            const auto ub = cxt->walkable();
            const double s = mult*(0.5 - cx);
            if(ub) f += vec2d{s, 0.};
        }
        if(cy < 0.5) { // top
            const auto cxyt = brd.tile(ct->x() - 1, ct->y() - 1);
            if(cxyt) {
                const auto ub = cxyt->walkable();
                const double s = mult*(0.5 - cx)*(0.5 - cy);
                if(ub) f += vec2d{s, s};
            }
        } else { // left
            const auto cxyt = brd.tile(ct->x() - 1, ct->y() + 1);
            if(cxyt) {
                const auto ub = cxyt->walkable();
                const double s = mult*(0.5 - cx)*(cy - 0.5);
                if(ub) f += vec2d{s, -s};
            }
        }
    }
    if(cy > 0.5) {
        const auto cxt = brd.tile(ct->x(), ct->y() + 1);
        if(cxt) {
            const auto ub = cxt->walkable();
            const double s = mult*(cy - 0.5);
            if(ub) f += vec2d{0., -s};
        }
    } else {
        const auto cxt = brd.tile(ct->x(), ct->y() - 1);
        if(cxt) {
            const auto ub = cxt->walkable();
            const double s = mult*(0.5 - cy);
            if(ub) f += vec2d{0., s};
        }
    }
    return f;
}

vec2d eForceHelpers::avoidSoldiersForce(eCharacter* const c) {
    const auto t = c->tile();
    if(!t) return vec2d{0., 0.};
    const double cax = c->absX();
    const double cay = c->absY();
    const double mult = 5.;
    vec2d result{0., 0.};
    for(int i = -1; i < 2; i++) {
        for(int j = -1; j < 2; j++) {
            const auto& chars = t->characters();
            for(const auto& cc : chars) {
                if(!cc->isSoldier()) continue;
                if(cc.get() == c) continue;
                const double ccax = cc->absX();
                const double ccay = cc->absY();

                const vec2d line{ccax - cax, ccay - cay};
                const double lineLen = line.length();
                if(lineLen > 1. || lineLen < 0.01) continue;
                vec2d force{-line.x, -line.y};
                force *= mult*(1. - lineLen)/lineLen;
                result += force;
            }
        }
    }
    return result;
}
