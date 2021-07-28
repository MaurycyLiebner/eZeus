#include "ewatercorner.h"

#include "engine/etile.h"
#include "esurroundingterrain.h"

int eWaterCorner::get(eTile* const tile) {
    const auto dry = eTerrain::dryBased;
    const auto water = eTerrain::water;
    const auto beach = eTerrain::beach;

    if(tile->terrain() != water) return -1;

    eSurroundingTerrain tt(tile);

    int id = -1;
    if(tt(water, water, water, water, beach | water, beach, dry, water)) {
        id = 0;
    } else if(tt(water, water, water, water, dry, beach, beach, water)) {
        id = 1;
    } else if(tt(dry, water, water, water, beach, beach, dry, dry)) {
        id = 2;
    } else if(tt(water, water, dry, dry, dry, beach, beach, water)) {
        id = 3;
    } else if(tt(water, water, beach | water, beach, beach | water, beach, dry, water)) {
        id = 4;
    } else if(tt(beach | water, water, water, water, dry, beach, beach | water, beach)) {
        id = 5;
    } else if(tt(dry, water, water, water, water, water, beach | water, beach)) {
        id = 6;
    } else if(tt(beach | water, water, water, water, water, water, dry, beach)) {
        id = 7;
    } else if(tt(dry, dry, dry, water, water, water, beach | water, beach)) {
        id = 8;
    } else if(tt(beach | water, water, water, water, dry, dry, dry, beach)) {
        id = 9;
    } else if(tt(dry, water, water, water, beach | water, beach, beach | water, beach)) {
        id = 10;
    } else if(tt(beach | water, beach, beach | water, water, water, water, dry, beach)) {
        id = 11;
    } else if(tt(beach | water, beach, dry, water, water, water, water, water)) {
        id = 12;
    } else if(tt(dry, beach, beach | water, water, water, water, water, water)) {
        id = 13;
    } else if(tt(beach | water, beach, dry, dry, dry | water, water, water, water)) {
        id = 14;
    } else if(tt(dry | beach, beach, beach | water, water, water, water, dry | water, dry)) {
        id = 15;
    } else if(tt(beach | water, beach, dry, water, water, water, beach | water, beach)) {
        id = 16;
    } else if(tt(dry, beach, beach | water, beach, beach | water, water, water, water)) {
        id = 17;
    } else if(tt(water, water, beach | water, beach, dry, water, water, water)) {
        id = 18;
    } else if(tt(water, water, dry, beach, beach | water, water, water, water)) {
        id = 19;
    } else if(tt(water, water, beach | water, beach, dry, dry, dry, water)) {
        id = 20;
    } else if(tt(dry, dry, dry, beach, beach | water, water, water, water)) {
        id = 21;
    } else if(tt(beach | water, beach, beach | water, beach, dry, water, water, water)) {
        id = 22;
    } else if(tt(water, water, dry, dry, beach | water, beach, beach | water, water)) {
        id = 23;
    }
    return id;
}
