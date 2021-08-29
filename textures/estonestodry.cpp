#include "estonestodry.h"

bool hiddenByNeighbour(eTile* const tile) {
    if(const auto t = tile->top<eTile>()) {
        const int d = t->futureDim();
        if(d > 1) return true;
    }

    if(const auto t = tile->topLeft<eTile>()) {
        const int d = t->futureDim();
        if(d > 1) return true;
    }


    for(int x = 0; x > -3; x--) {
        for(int y = 0; y > -3; y--) {
            if(x == 0 && y == 0) continue;
            if(x == 0 && y == -2) continue;
            const auto t = tile->tileRel<eTile>(x, y);
            if(!t) continue;
            const int d = t->futureDim();
            if(d > 2) return true;
        }
    }


    return false;
}

void eStonesToDry::get(eTile* const tile,
                       int& futureDim,
                       int& drawDim) {
    const auto terr = tile->terrain();

    const bool hidden = hiddenByNeighbour(tile);
    if(hidden) {
        futureDim = 0;
        drawDim = 0;
        return;
    }

    {
        const auto tr = tile->topRight<eTile>();
        if(tr) {
            if(tr->futureDim() == 2) {
                futureDim = 1;
                drawDim = 2;
                return;
            }
            const auto trtr = tr->topRight<eTile>();
            if(trtr && trtr->futureDim() == 3) {
                futureDim = 1;
                drawDim = 3;
                return;
            }
        }
    }

    futureDim = 1;
    drawDim = 1;

    {
        const auto t = tile->bottom();
        if(!t || t->terrain() != terr) return;
    }

    {
        const auto t = tile->bottomLeft();
        if(!t || t->terrain() != terr) return;
    }

    {
        const auto t = tile->bottomRight();
        if(!t || t->terrain() != terr) return;
    }
    {
        const auto t = tile->left<eTile>();
        if(t) {
            if(t->terrain() == terr && t->futureDim() > 1) {
                return;
            }
            const auto t1 = t->left<eTile>();
            if(t1 && t1->terrain() == terr && t1->futureDim() > 2) {
                return;
            }
            const auto t2 = t->topLeft<eTile>();
            if(t2 && t2->terrain() == terr && t2->futureDim() > 2) {
                return;
            }
            const auto t3 = t->bottomLeft<eTile>();
            if(t3 && t3->terrain() == terr && t3->futureDim() > 2) {
                return;
            }
        }
    }

    futureDim = 2;
    drawDim = 0;

    {
        const auto t0 = tile->bottom<eTile>();
        if(!t0 || t0->terrain() != terr) return;
        const auto t1 = t0->bottom<eTile>();
        if(!t1 || t1->terrain() != terr) return;

        const auto t2 = t1->topRight<eTile>();
        if(!t2 || t2->terrain() != terr) return;
        const auto t3 = t2->topRight<eTile>();
        if(!t3 || t3->terrain() != terr) return;

        const auto t4 = t1->topLeft<eTile>();
        if(!t4 || t4->terrain() != terr) return;
        const auto t5 = t4->topLeft<eTile>();
        if(!t5 || t5->terrain() != terr) return;

        const auto t = tile->left<eTile>();
        if(t) {
            const auto t3 = t->bottomLeft<eTile>();
            if(t3 && t3->terrain() == terr && t3->futureDim() > 1) {
                return;
            }
        }
    }

    futureDim = 3;
    drawDim = 0;
}
