#include "ebeachtodry.h"

#include "engine/etile.h"
#include "esurroundingterrain.h"

int eBeachToDry::get(eTile* const tile,
                     const eWorldDirection dir) {
    const auto dry = eTerrain::dryBased;
    const auto beach = eTerrain::beach;

    if(tile->terrain() != beach) return -1;

    const auto bow = beach | eTerrain::water;

    eSurroundingTerrain tt(tile, dir);

    int id = -1;
    if(tt(bow, bow, bow, bow, dry | bow, dry, dry | bow, bow)) {
        id = 0;
    } else if(tt(bow, bow, bow, bow, bow, bow, dry, bow)) {
        id = 1;
    } else if(tt(dry | bow, bow, bow, bow, bow, bow, dry | bow, dry)) {
        id = 2;
    } else if(tt(dry, bow, bow, bow, bow, bow, bow, bow)) {
        id = 3;
    } else if(tt(dry | bow, dry, dry | bow, bow, bow, bow, bow, bow)) {
        id = 4;
    } else if(tt(bow, bow, dry, bow, bow, bow, bow, bow)) {
        id = 5;
    } else if(tt(bow, bow, dry | bow, dry, dry | bow, bow, bow, bow)) {
        id = 6;
    } else if(tt(bow, bow, bow, bow, dry, bow, bow, bow)) {
        id = 7;
    } else if(tt(dry | bow, bow, bow, bow, dry | bow, dry, dry | bow, dry)) {
        id = 8;
    } else if(tt(dry | bow, dry, dry | bow, bow, bow, bow, dry | bow, dry)) {
        id = 9;
    } else if(tt(dry | bow, dry, dry | bow, dry, dry | bow, bow, bow, bow)) {
        id = 10;
    } else if(tt(bow, bow, dry | bow, dry, dry | bow, dry, dry | bow, bow)) {
        id = 11;
    }
    return id;
}
