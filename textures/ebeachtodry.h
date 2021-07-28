#ifndef EBEACHTODRY_H
#define EBEACHTODRY_H

class eTile;

enum class eBeachToDryId {
    bottomLeft,
    left,
    topLeft,
    top,
    topRight,
    right,
    bottomRight,
    bottom,
    topLeftAndBottomLeft,
    topLeftAndTopRight,
    topRightAndBottomRight,
    bottomLeftAndBottomRight,
    none
};

namespace eBeachToDry {
    eBeachToDryId get(eTile* const tile);
};

#endif // EBEACHTODRY_H
