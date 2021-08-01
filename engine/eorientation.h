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

#endif // EORIENTATION_H
