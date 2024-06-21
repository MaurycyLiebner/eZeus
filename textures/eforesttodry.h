#ifndef EFORESTTODRY_H
#define EFORESTTODRY_H

class eTile;
enum class eWorldDirection;

enum class eForestToDryId {
    somewhere,
    none
};

namespace eForestToDry {
    eForestToDryId get(eTile* const tile, const eWorldDirection dir);
};

#endif // EFORESTTODRY_H
