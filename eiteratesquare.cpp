#include "eiteratesquare.h"

void eIterateSquare::iterateSquare(const int k, const eTileFunc& prcs,
                                   const int inc) {
    if(k == 0) {
        prcs(0, 0);
        return;
    }
    int i = 0;
    int j = 0;
    const auto iiter = [&]() {
        for(i = -k; i <= k; i += inc) {
            const bool r = prcs(i, j);
            if(r) return true;
        }
        return false;
    };

    const auto jiter = [&]() {
        for(j = -k + inc; j <= k - inc; j += inc) {
            const bool r = prcs(i, j);
            if(r) return true;
        }
        return false;
    };

    j = -k;
    const bool r0 = iiter();
    if(r0) return;
    j = k;
    const bool r1 = iiter();
    if(r1) return;

    i = -k;
    const bool r2 = jiter();
    if(r2) return;
    i = k;
    const bool r3 = jiter();
    if(r3) return;
}
