#ifndef EWATERTOBEACH_H
#define EWATERTOBEACH_H

class eTile;
enum class eWorldDirection;

namespace eWaterToBeach {
    int get(eTile* const tile, const eWorldDirection dir);
};

#endif // EWATERTOBEACH_H
