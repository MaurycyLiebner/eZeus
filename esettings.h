#ifndef ESETTINGS_H
#define ESETTINGS_H

#include "widgets/eresolution.h"

struct eSettings {
    bool fSmallTextures;
    bool fLargeTextures;
    bool fFullscreen;
    eResolution fRes;
};

#endif // ESETTINGS_H
