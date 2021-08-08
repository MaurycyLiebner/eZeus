#ifndef ETILETOTEXTURE_H
#define ETILETOTEXTURE_H

#include "etexture.h"

class eTile;
class eTerrainTextures;

enum class eTileSize : int;

namespace eTileToTexture {
    eTexture get(eTile* const tile,
                 const eTerrainTextures& textures,
                 int& wSpan, int& hSpan,
                 const eTileSize tileSize,
                 const bool drawElev);
};

#endif // ETILETOTEXTURE_H
