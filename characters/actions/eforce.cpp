#include "eforce.h"

#include "engine/egameboard.h"

eForce eForceHelpers::avoidBuildingsForce(eCharacter* const c) {
    const auto ct = c->tile();
    const auto& brd = c->getBoard();
    const auto cx = c->x();
    const auto cy = c->y();
    eForce f{0., 0.};
    if(cx > 0.5) { // bottom-right
        const auto cxt = brd.tile(ct->x() + 1, ct->y());
        if(cxt) {
            const auto ub = cxt->underBuilding();
            const double s = 10*(cx - 0.5);
            if(ub) f += eForce{-s, 0.};
        }
        if(cy < 0.5) { // right
            const auto cxyt = brd.tile(ct->x() + 1, ct->y() - 1);
            if(cxyt) {
                const auto ub = cxyt->underBuilding();
                const double s = 10*(cx - 0.5)*(0.5 - cy);
                if(ub) f += eForce{-s, s};
            }
        } else { // bottom
            const auto cxyt = brd.tile(ct->x() + 1, ct->y() + 1);
            if(cxyt) {
                const auto ub = cxyt->underBuilding();
                const double s = 10*(cx - 0.5)*(cy - 0.5);
                if(ub) f += eForce{-s, -s};
            }
        }
    } else { // top-left
        const auto cxt = brd.tile(ct->x() - 1, ct->y());
        if(cxt) {
            const auto ub = cxt->underBuilding();
            const double s = 10*(0.5 - cx);
            if(ub) f += eForce{s, 0.};
        }
        if(cy < 0.5) { // top
            const auto cxyt = brd.tile(ct->x() - 1, ct->y() - 1);
            if(cxyt) {
                const auto ub = cxyt->underBuilding();
                const double s = 10*(0.5 - cx)*(0.5 - cy);
                if(ub) f += eForce{s, s};
            }
        } else { // left
            const auto cxyt = brd.tile(ct->x() - 1, ct->y() + 1);
            if(cxyt) {
                const auto ub = cxyt->underBuilding();
                const double s = 10*(0.5 - cx)*(cy - 0.5);
                if(ub) f += eForce{s, -s};
            }
        }
    }
    if(cy > 0.5) {
        const auto cxt = brd.tile(ct->x(), ct->y() + 1);
        if(cxt) {
            const auto ub = cxt->underBuilding();
            const double s = 10*(cy - 0.5);
            if(ub) f += eForce{0., -s};
        }
    } else {
        const auto cxt = brd.tile(ct->x(), ct->y() - 1);
        if(cxt) {
            const auto ub = cxt->underBuilding();
            const double s = 10*(0.5 - cy);
            if(ub) f += eForce{0., s};
        }
    }
    return f;
}
