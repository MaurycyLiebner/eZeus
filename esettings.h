#ifndef ESETTINGS_H
#define ESETTINGS_H

#include "widgets/eresolution.h"
#include "engine/etile.h"

struct eSettings {
    bool fTinyTextures;
    bool fSmallTextures;
    bool fMediumTextures;
    bool fLargeTextures;
    bool fFullscreen;
    eResolution fRes;

    std::vector<eTileSize> availableSizes() const {
        std::vector<eTileSize> sizes;
        if(fTinyTextures) {
            sizes.push_back(eTileSize::s15);
        }
        if(fSmallTextures) {
            sizes.push_back(eTileSize::s30);
        }
        if(fMediumTextures) {
            sizes.push_back(eTileSize::s45);
        }
        if(fLargeTextures) {
            sizes.push_back(eTileSize::s60);
        }
        return sizes;
    }
};

#endif // ESETTINGS_H
