#ifndef EMARBLETILE_H
#define EMARBLETILE_H

#include "etexture.h"
#include "engine/etile.h"
#include "eterraintextures.h"

namespace eMarbleTile {
    bool isEdge(eTile* const tile, const eWorldDirection dir);
    std::shared_ptr<eTexture> get(eTile* const tile,
            const eTerrainTextures& textures,
            const eWorldDirection dir);
};

#endif // EMARBLETILE_H
