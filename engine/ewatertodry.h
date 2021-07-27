#ifndef EWATERTODRY_H
#define EWATERTODRY_H

class eTile;

enum class eWaterToDryId {
    bottomLeft,
    topLeft,
    topRight,
    bottomRight,
    bottomLeft_topLeft,
    topLeft_topRight,
    topRight_bottomRight,
    bottomLeft_bottomRight,
    bottomLeft_topRight,
    topLeft_bottomRight,
    topLeft_bottomLeft_bottomRight,
    bottomLeft_topLeft_topRight,
    topLeft_topRight_bottomRight,
    topRight_bottomRight_bottomLeft,
    left_right,
    top_bottom,
    left,
    top,
    right,
    bottom,
    top_left,
    top_right,
    right_bottom,
    left_bottom,
    left_top_right,
    top_right_bottom,
    right_bottom_left,
    bottom_left_top,
    top_right_bottom_left,
    top_bottomLeft,
    right_bottomLeft,
    top_right_bottomLeft,
    right_topLeft,
    bottom_topLeft,
    bottom_right_topLeft,
    bottom_topRight,
    left_topRight,
    bottom_left_topRight,
    left_bottomRight,
    top_bottomRight,
    left_top_bottomRight,
    right_bottomLeft_topLeft,
    bottom_topLeft_topRight,
    left_topRight_bottomRight,
    top_bottomLeft_bottomRight,
    all,
    none
};

namespace eWaterToDry {
    eWaterToDryId get(eTile* const tile);
};

#endif // EWATERTODRY_H
