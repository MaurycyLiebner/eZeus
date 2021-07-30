#include "estonestodry.h"

bool hiddenByNeighbour(eTile* const tile) {
    if(const auto t = tile->top()) {
        const int w = t->drawSpanW();
        const int h = t->drawSpanH();
        if(w > 1 && h > 1) return true;
    }

    if(const auto t = tile->topLeft()) {
        const int w = t->drawSpanW();
        if(w > 1) return true;
    }

    if(const auto t = tile->topRight()) {
        const int h = t->drawSpanH();
        if(h > 1) return true;
    }

//    if(const auto t = tile->left()) {
//        const int w = t->drawSpanW();
//        const int h = t->drawSpanH();
//        if(w > 2 && h > 2) return true;
//    }

    return false;
}

eStonesToDryId eStonesToDry::get(eTile* const tile) {
    const auto terr = tile->terrain();

    if(hiddenByNeighbour(tile)) return eStonesToDryId::none;

    {
        const auto t = tile->bottom();
        if(!t || t->terrain() != terr) return eStonesToDryId::small;
    }

    {
        const auto t = tile->bottomLeft();
        if(!t || t->terrain() != terr) return eStonesToDryId::small;
    }

    {
        const auto t = tile->bottomRight();
        if(!t || t->terrain() != terr) return eStonesToDryId::small;
    }

    return eStonesToDryId::large;

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
