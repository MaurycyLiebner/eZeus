#include "eiteratesquare.h"

void eIterateSquare::iterateSquare(const int k, const eTileFunc& prcs,
                                   const int inc) {
    if(k == 0) {
        return prcs(0, 0);
    }
    int i = 0;
    int j = 0;
    const auto iiter = [&]() {
        for(i = -k; i <= k; i += inc) {
            prcs(i, j);
        }
    };

    const auto jiter = [&]() {
        for(j = -k + inc; j <= k - inc; j += inc) {
            prcs(i, j);
        }
    };

    j = -k;
    iiter();
    j = k;
    iiter();

    i = -k;
    jiter();
    i = k;
    jiter();
}
