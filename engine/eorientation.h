#ifndef EORIENTATION_H
#define EORIENTATION_H

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

#endif // EORIENTATION_H
