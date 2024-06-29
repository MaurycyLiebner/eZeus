#ifndef ESETTINGS_H
#define ESETTINGS_H

#include "widgets/eresolution.h"
#include "engine/etile.h"

struct eSettings {
    bool fTinyTextures = false;
    bool fSmallTextures = true;
    bool fMediumTextures = false;
    bool fLargeTextures = false;
    bool fFullscreen = false;
    eResolution fRes = eResolution(1280, 720);

    std::vector<eTileSize> availableSizes() const;

    void write() const;
    void read();
};

#endif // ESETTINGS_H
