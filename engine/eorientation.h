#ifndef EORIENTATION_H
#define EORIENTATION_H

#include "eworlddirection.h"

#include <cmath>

enum class eOrientation {
    topRight,
    right,
    bottomRight,
    bottom,
    bottomLeft,
    left,
    topLeft,
    top
};

inline eOrientation operator!(const eOrientation o) {
    switch(o) {
    case eOrientation::topRight: return eOrientation::bottomLeft;
    case eOrientation::right: return eOrientation::left;
    case eOrientation::bottomRight: return eOrientation::topLeft;
    case eOrientation::bottom: return eOrientation::top;
    case eOrientation::bottomLeft: return eOrientation::topRight;
    case eOrientation::left: return eOrientation::right;
    case eOrientation::topLeft: return eOrientation::bottomRight;
    case eOrientation::top: return eOrientation::bottom;
    }
    return eOrientation::topRight;
}

inline eOrientation sAngleOrientation(const double degAngle) {
    const double h45 = 0.5*45.;
    eOrientation o;
    if(degAngle > h45 && degAngle < h45 + 45) {
        o = eOrientation::bottom;
    } else if(degAngle > h45 + 45 && degAngle < h45 + 90) {
        o = eOrientation::bottomLeft;
    } else if(degAngle > h45 + 90 && degAngle < h45 + 135) {
        o = eOrientation::left;
    } else if(degAngle > h45 + 135 && degAngle < h45 + 180) {
        o = eOrientation::topLeft;
    } else if(degAngle > h45 + 180 && degAngle < h45 + 225) {
        o = eOrientation::top;
    } else if(degAngle > h45 + 225 && degAngle < h45 + 270) {
        o = eOrientation::topRight;
    } else if(degAngle > h45 + 270 && degAngle < h45 + 315) {
        o = eOrientation::right;
    } else {
        o = eOrientation::bottomRight;
    }
    return o;
}

inline eOrientation sRotated(const eOrientation o,
                             const eWorldDirection dir) {
    if(dir == eWorldDirection::N) {
        return o;
    } else if(dir == eWorldDirection::E) {
        switch(o) {
        case eOrientation::topRight:
            return eOrientation::topLeft;
        case eOrientation::right:
            return eOrientation::top;
        case eOrientation::bottomRight:
            return eOrientation::topRight;
        case eOrientation::bottom:
            return eOrientation::right;
        case eOrientation::bottomLeft:
            return eOrientation::bottomRight;
        case eOrientation::left:
            return eOrientation::bottom;
        case eOrientation::topLeft:
            return eOrientation::bottomLeft;
        case eOrientation::top:
            return eOrientation::left;
        }
    } else if(dir == eWorldDirection::S) {
        switch(o) {
        case eOrientation::topRight:
            return eOrientation::bottomLeft;
        case eOrientation::right:
            return eOrientation::left;
        case eOrientation::bottomRight:
            return eOrientation::topLeft;
        case eOrientation::bottom:
            return eOrientation::top;
        case eOrientation::bottomLeft:
            return eOrientation::topRight;
        case eOrientation::left:
            return eOrientation::right;
        case eOrientation::topLeft:
            return eOrientation::bottomRight;
        case eOrientation::top:
            return eOrientation::bottom;
        }
    } else { // if(dir == eWorldDirection::W) {
        switch(o) {
        case eOrientation::topRight:
            return eOrientation::bottomRight;
        case eOrientation::right:
            return eOrientation::bottom;
        case eOrientation::bottomRight:
            return eOrientation::bottomLeft;
        case eOrientation::bottom:
            return eOrientation::left;
        case eOrientation::bottomLeft:
            return eOrientation::topLeft;
        case eOrientation::left:
            return eOrientation::top;
        case eOrientation::topLeft:
            return eOrientation::topRight;
        case eOrientation::top:
            return eOrientation::right;
        }
    }
}

#endif // EORIENTATION_H
