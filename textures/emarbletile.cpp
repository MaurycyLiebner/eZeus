#include "emarbletile.h"

std::shared_ptr<eTexture> eMarbleTile::get(
        eTile* const tile,
        const eTerrainTextures& textures) {
    const int seed = tile->seed();

    const auto terr = tile->terrain();

    bool tl;
    bool tr;
    bool br;
    bool bl;
    bool t;
    bool r;
    bool b;
    bool l;
    tile->neighboursWithTerrain(terr, tl, tr, br, bl, t, r, b, l);

    //if()
    const auto& fm = textures.fFlatMarble;
    const int id = seed % fm.size();
    return fm.getTexture(id);
}
