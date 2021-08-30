#ifndef EOVERLAY_H
#define EOVERLAY_H

#include "etexture.h"

struct eOverlay {
    double fX;
    double fY;
    std::shared_ptr<eTexture> fTex;
    bool fAlignTop = false;
};

#endif // EOVERLAY_H
