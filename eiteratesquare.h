#ifndef EITERATESQUARE_H
#define EITERATESQUARE_H

#include <functional>

namespace eIterateSquare {
    using eTileFunc = std::function<void(int, int)>;
    void iterateSquare(const int k, const eTileFunc& prcs,
                       const int inc = 1);
};

#endif // EITERATESQUARE_H
