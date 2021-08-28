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

//    if(const auto t = tile->left()) {
//        const int w = t->drawSpanW();
//        const int h = t->drawSpanH();
//        if(w > 2 && h > 2) return true;
//    }

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
        if(tr && tr->futureDim() == 2) {
            futureDim = 1;
            drawDim = 2;
            return;
        }
    }

    {
        const auto t = tile->bottom();
        if(!t || t->terrain() != terr) {
            futureDim = 1;
            drawDim = 1;
            return;
        }
    }

    {
        const auto t = tile->bottomLeft();
        if(!t || t->terrain() != terr) {
            futureDim = 1;
            drawDim = 1;
            return;
        }
    }

    {
        const auto t = tile->bottomRight();
        if(!t || t->terrain() != terr) {
            futureDim = 1;
            drawDim = 1;
            return;
        }
    }
    {
        const auto t = tile->left<eTile>();
        if(t && t->terrain() == terr && t->futureDim() > 1) {
            futureDim = 1;
            drawDim = 1;
            return;
        }
    }

    futureDim = 2;
    drawDim = 0;

//    {
//        const auto t = tile->top();
//        if(!t || t->terrain() != terr) return eStonesToDryId::large;
//    }

//    {
//        const auto t = tile->topLeft();
//        if(!t || t->terrain() != terr) return eStonesToDryId::large;
//    }

//    {
//        const auto t = tile->topRight();
//        if(!t || t->terrain() != terr) return eStonesToDryId::large;
//    }

//    {
//        const auto t = tile->left();
//        if(!t || t->terrain() != terr) return eStonesToDryId::large;
//    }

//    {
//        const auto t = tile->right();
//        if(!t || t->terrain() != terr) return eStonesToDryId::large;
//    }

//    return eStonesToDryId::huge;
}
