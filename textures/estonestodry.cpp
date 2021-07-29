#include "estonestodry.h"

bool hiddenByNeighbour(eTile* const tile, const int id) {
    const auto terr = tile->terrain();

    if(const auto t = tile->top()) {
        const auto did = t->drawnId();
        if(t->terrain() == terr && did & id) {
            return true;
        }
    }

    if(const auto t = tile->topLeft()) {
        const auto did = t->drawnId();
        if(t->terrain() == terr && did & id) {
            return true;
        }
    }

    if(const auto t = tile->topRight()) {
        const auto did = t->drawnId();
        if(t->terrain() == terr && did & id) {
            return true;
        }
    }

    return false;
}

inline eStonesToDryId operator|(const eStonesToDryId a, const eStonesToDryId b) {
    return static_cast<eStonesToDryId>(static_cast<int>(a) | static_cast<int>(b));
}

bool hidden(eTile* const tile) {
    const int hid = static_cast<int>(eStonesToDryId::huge);
    const int lid = static_cast<int>(eStonesToDryId::large);

    const bool r = hiddenByNeighbour(tile, hid | lid);
    if(r) return r;

    const auto terr = tile->terrain();

    if(const auto t = tile->left()) {
        const auto did = t->drawnId();
        if(t->terrain() == terr && did == hid) {
            return true;
        }
    }
    return false;
}

eStonesToDryId eStonesToDry::get(eTile* const tile) {
    const auto terr = tile->terrain();

    if(hidden(tile)) return eStonesToDryId::none;

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



    {
        const auto t = tile->top();
        if(!t || t->terrain() != terr) return eStonesToDryId::large;
    }

    {
        const auto t = tile->topLeft();
        if(!t || t->terrain() != terr) return eStonesToDryId::large;
    }

    {
        const auto t = tile->topRight();
        if(!t || t->terrain() != terr) return eStonesToDryId::large;
    }

    {
        const auto t = tile->left();
        if(!t || t->terrain() != terr) return eStonesToDryId::large;
    }

    {
        const auto t = tile->right();
        if(!t || t->terrain() != terr) return eStonesToDryId::large;
    }

    return eStonesToDryId::huge;
}
