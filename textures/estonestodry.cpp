#include "estonestodry.h"

bool hiddenByNeighbour(eTile* const tile, const int id) {
    const auto terr = tile->terrain();

    if(const auto t = tile->top()) {
        const auto tdid = t->drawnId();
        if(t->terrain() == terr && tdid & id) {
            return true;
        }
    }

    if(const auto tl = tile->topLeft()) {
        const auto tldid = tl->drawnId();
        if(tl->terrain() == terr && tldid & id) {
            return true;
        }
    }

    if(const auto tr = tile->topRight()) {
        const auto trdid = tr->drawnId();
        if(tr->terrain() == terr && trdid & id) {
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

//    const auto terr = tile->terrain();

//    if(const auto t = tile->top()) {
//        if(const auto tt = t->top()) {
//            const auto did = tt->drawnId();
//            if(tt->terrain() == terr && did == hid) {
//                return true;
//            }
//        }
//        if(const auto tt = t->topLeft()) {
//            const auto did = tt->drawnId();
//            if(tt->terrain() == terr && did == hid) {
//                return true;
//            }
//        }
//        if(const auto tt = t->topRight()) {
//            const auto did = tt->drawnId();
//            if(tt->terrain() == terr && did == hid) {
//                return true;
//            }
//        }
//        if(const auto tt = t->right()) {
//            const auto did = tt->drawnId();
//            if(tt->terrain() == terr && did == hid) {
//                return true;
//            }
//        }
//        if(const auto tt = t->left()) {
//            const auto did = tt->drawnId();
//            if(tt->terrain() == terr && did == hid) {
//                return true;
//            }
//        }
//    }

    return false;
}

eStonesToDryId eStonesToDry::get(eTile* const tile) {
    const auto terr = tile->terrain();

    if(hidden(tile)) return eStonesToDryId::none;

    const auto bt = tile->bottom();
    if(!bt || bt->terrain() != terr) return eStonesToDryId::small;

    const auto blt = tile->bottomLeft();
    if(!blt || blt->terrain() != terr) return eStonesToDryId::small;

    const auto brt = tile->bottomRight();
    if(!brt || brt->terrain() != terr) return eStonesToDryId::small;


//    const auto bbt = bt->bottom();
//    if(!bbt || bbt->terrain() != terr) return eStonesToDryId::large;

//    const auto bblt = bt->bottomLeft();
//    if(!bblt || bblt->terrain() != terr) return eStonesToDryId::large;

//    const auto bbrt = bt->bottomRight();
//    if(!bbrt || bbrt->terrain() != terr) return eStonesToDryId::large;

//    const auto bbblt = bt->left();
//    if(!bbblt || bbblt->terrain() != terr) return eStonesToDryId::large;

//    const auto bbbrt = bt->right();
//    if(!bbbrt || bbbrt->terrain() != terr) return eStonesToDryId::large;

    return eStonesToDryId::large;
}
