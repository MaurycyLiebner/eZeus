#ifndef ETILETOTEXTURE_H
#define ETILETOTEXTURE_H

#include "etexture.h"

class eTile;
class eTerrainTextures;

namespace eTileToTexture {
    eTexture get(eTile* const tile,
                 const eTerrainTextures& textures);
};

#endif // ETILETOTEXTURE_H
