#ifndef EFERTILETODRY_H
#define EFERTILETODRY_H

class eTile;

enum class eFertileToDryId {
    somewhere,
    none
};

namespace eFertileToDry {
    eFertileToDryId get(eTile* const tile);
};

#endif // EFERTILETODRY_H
