#ifndef EWATERCORNER_H
#define EWATERCORNER_H

class eTile;

namespace eWaterCorner {
    bool detect(eTile* const tile);
    int get(eTile* const tile);
};

#endif // EWATERCORNER_H
