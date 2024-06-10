#ifndef ETILETOTEXTURE_H
#define ETILETOTEXTURE_H

#include "etexture.h"

class eTile;
class eTerrainTextures;
class eBuildingTextures;
class eTextureCollection;

enum class eTileSize : int;

namespace eTileToTexture {
    std::shared_ptr<eTexture> get(eTile* const tile,
                 const eTerrainTextures& textures,
                 const eBuildingTextures& blds,
                 const eTileSize tileSize,
                 const bool drawElev,
                 int& futureDim,
                 int& drawDim,
                 const eTextureCollection** coll,
                 const bool poseidonMode);
};

#endif // ETILETOTEXTURE_H
