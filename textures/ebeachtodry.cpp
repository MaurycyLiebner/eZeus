#include "ebeachtodry.h"

#include "engine/etile.h"
#include "esurroundingterrain.h"

int eBeachToDry::get(eTile* const tile) {
    const auto dry = eTerrain::dry;
    const auto beach = eTerrain::beach;

    if(tile->terrain() != beach) return -1;

    eSurroundingTerrain tt(tile);

    int id = -1;
    if(tt(beach, beach, beach, beach, dry, dry, dry, beach)) {
        id = 0;
    } else if(tt(beach, beach, beach, beach, beach, beach, dry, beach)) {
        id = 1;
    } else if(tt(dry, beach, beach, beach, beach, beach, dry, dry)) {
        id = 2;
    } else if(tt(dry, beach, beach, beach, beach, beach, beach, beach)) {
        id = 3;
    } else if(tt(dry, dry, dry, beach, beach, beach, beach, beach)) {
        id = 4;
    } else if(tt(beach, beach, dry, beach, beach, beach, beach, beach)) {
        id = 5;
    } else if(tt(beach, beach, dry, dry, dry, beach, beach, beach)) {
        id = 6;
    } else if(tt(beach, beach, beach, beach, dry, beach, beach, beach)) {
        id = 7;
    } else if(tt(dry, beach, beach, beach, dry, dry, dry, dry)) {
        id = 8;
    } else if(tt(dry, dry, dry, beach, beach, beach, dry, dry)) {
        id = 9;
    } else if(tt(dry, dry, dry, dry, dry, beach, beach, beach)) {
        id = 10;
    } else if(tt(beach, beach, dry, dry, dry, dry, dry, beach)) {
        id = 11;
    }
    return id;
}
