#ifndef EWATERCORNER_H
#define EWATERCORNER_H

class eTile;
enum class eWorldDirection;

namespace eWaterCorner {
    int get(eTile* const tile, const eWorldDirection dir);
};

#endif // EWATERCORNER_H
