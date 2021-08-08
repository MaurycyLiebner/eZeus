#ifndef EMOVEDIRECTION_H
#define EMOVEDIRECTION_H

#include "eorientation.h"

#include <vector>

enum class eMoveDirection {
    topRight = 1 << 0,
    bottomRight = 1 << 1,
    bottomLeft = 1 << 2,
    topLeft = 1 << 3,

    allDirections = eMoveDirection::topRight |
                    eMoveDirection::bottomRight |
                    eMoveDirection::bottomLeft |
                    eMoveDirection::topLeft
};

inline eMoveDirection operator|(const eMoveDirection a, const eMoveDirection b) {
    return static_cast<eMoveDirection>(static_cast<int>(a) | static_cast<int>(b));
}

inline eMoveDirection operator&(const eMoveDirection a, const eMoveDirection b) {
    return static_cast<eMoveDirection>(static_cast<int>(a) & static_cast<int>(b));
}

inline std::vector<eMoveDirection> gExtractDirections(
        const eMoveDirection d) {
    std::vector<eMoveDirection> dirs;
    if(static_cast<bool>(d & eMoveDirection::topRight)) {
        dirs.push_back(eMoveDirection::topRight);
    }
    if(static_cast<bool>(d & eMoveDirection::bottomRight)) {
        dirs.push_back(eMoveDirection::bottomRight);
    }
    if(static_cast<bool>(d & eMoveDirection::bottomLeft)) {
        dirs.push_back(eMoveDirection::bottomLeft);
    }
    if(static_cast<bool>(d & eMoveDirection::topLeft)) {
        dirs.push_back(eMoveDirection::topLeft);
    }
    return dirs;
}

inline eMoveDirection gOrientationToDirection(const eOrientation dir) {
    switch(dir) {
    case eOrientation::topRight:
        return eMoveDirection::topRight;
    case eOrientation::bottomRight:
        return eMoveDirection::bottomRight;
    case eOrientation::bottomLeft:
        return eMoveDirection::bottomLeft;
    case eOrientation::topLeft:
        return eMoveDirection::topLeft;
    default:
        break;
    }
    return eMoveDirection::topRight;
}

inline eOrientation gDirectionToOrientation(const eMoveDirection dir) {
    switch(dir) {
    case eMoveDirection::topRight:
        return eOrientation::topRight;
    case eMoveDirection::bottomRight:
        return eOrientation::bottomRight;
    case eMoveDirection::bottomLeft:
        return eOrientation::bottomLeft;
    case eMoveDirection::topLeft:
        return eOrientation::topLeft;
    }
    return eOrientation::topRight;
}

#endif // EMOVEDIRECTION_H
