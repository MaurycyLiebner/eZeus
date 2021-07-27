#ifndef EFORESTTODRY_H
#define EFORESTTODRY_H

class eTile;

enum class eForestToDryId {
    somewhere,
    none
};

namespace eForestToDry {
    eForestToDryId get(eTile* const tile);
};

#endif // EFORESTTODRY_H
