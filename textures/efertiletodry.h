#ifndef EFERTILETODRY_H
#define EFERTILETODRY_H

class eTile;
enum class eWorldDirection;

enum class eFertileToDryId {
    somewhere,
    none
};

namespace eFertileToDry {
    eFertileToDryId get(eTile* const tile, const eWorldDirection dir);
};

#endif // EFERTILETODRY_H
