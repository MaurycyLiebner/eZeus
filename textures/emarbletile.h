#ifndef EMARBLETILE_H
#define EMARBLETILE_H

#include "etexture.h"
#include "engine/etile.h"
#include "eterraintextures.h"

namespace eMarbleTile {
    std::shared_ptr<eTexture> get(
            eTile* const tile,
            const eTerrainTextures& textures);
};

#endif // EMARBLETILE_H
