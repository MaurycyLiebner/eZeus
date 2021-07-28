#include "ewatertox.h"

#include "esurroundingterrain.h"

int eWaterToX::get(eTile* const tile, const eTerrain x) {
    const auto water = eTerrain::water;

    if(tile->terrain() != water) return -1;

    eSurroundingTerrain tt(tile);

    int id = -1;

    if(tt(water, water, water, water, x | water, x, x | water, water)) {
        id = 0;
    } else if(tt(x | water, water, water, water, water, water, x | water, x)) {
        id = 1;
    } else if(tt(x | water, x, x | water, water, water, water, water, water)) {
        id = 2;
    } else if(tt(water, water, x | water, x, x | water, water, water, water)) {
        id = 3;
    } else if(tt(x | water, water, water, water, x | water, x, x | water, x)) {
        id = 4;
    } else if(tt(x | water, x, x | water, water, water, water, x | water, x)) {
        id = 5;
    } else if(tt(x | water, x, x | water, x, x | water, water, water, water)) {
        id = 6;
    } else if(tt(water, water, x | water, x, x | water, x, x | water, water)) {
        id = 7;
    } else if(tt(x | water, x, x | water, water, x | water, x, x | water, water)) {
        id = 8;
    } else if(tt(x | water, water, x | water, x, x | water, water, x | water, x)) {
        id = 9;
    } else if(tt(x | water, water, x | water, x, x | water, x, x | water, x)) {
        id = 10;
    } else if(tt(x | water, x, x | water, water, x | water, x, x | water, x)) {
        id = 11;
    } else if(tt(x | water, x, x | water, x, x | water, water, x | water, x)) {
        id = 12;
    } else if(tt(x | water, x, x | water, x, x | water, x, x | water, water)) {
        id = 13;
    } else if(tt(water, water, x, water, water, water, x, water)) {
        id = 14;
    } else if(tt(x, water, water, water, x, water, water, water)) {
        id = 15;
    } else if(tt(water, water, water, water, water, water, x, water)) {
        id = 16;
    } else if(tt(x, water, water, water, water, water, water, water)) {
        id = 17;
    } else if(tt(water, water, x, water, water, water, water, water)) {
        id = 18;
    } else if(tt(water, water, water, water, x, water, water, water)) {
        id = 19;
    } else if(tt(x, water, water, water, water, water, x, water)) {
        id = 20;
    } else if(tt(x, water, x, water, water, water, water, water)) {
        id = 21;
    } else if(tt(water, water, x, water, x, water, water, water)) {
        id = 22;
    } else if(tt(water, water, water, water, x | water, water, x, water)) {
        id = 23;
    } else if(tt(x, water, x, water, water, water, x, water)) {
        id = 24;
    } else if(tt(x, water, x, water, x, water, water, water)) {
        id = 25;
    } else if(tt(water, water, x, water, x, water, x, water)) {
        id = 26;
    } else if(tt(x, water, water, water, x, water, x, water)) {
        id = 27;
    } else if(tt(x, water, x, water, x, water, x, water)) {
        id = 28;
    } else if(tt(x | water, water, water, water, x | water, x, x | water, water)) {
        id = 29;
    } else if(tt(water, water, x | water, water, x | water, x, x | water, water)) {
        id = 30;
    } else if(tt(x | water, water, x | water, water, x | water, x, x | water, water)) {
        id = 31;
    } else if(tt(x | water, water, x | water, water, water, water, x | water, x)) {
        id = 32;
    } else if(tt(x | water, water, water, water, x | water, water, x | water, x)) {
        id = 33;
    } else if(tt(x | water, water, x | water, water, x | water, water, x | water, x)) {
        id = 34;
    } else if(tt(x | water, x, x | water, water, x | water, water, water, water)) {
        id = 35;
    } else if(tt(x | water, x, x | water, water, water, water, x | water, water)) {
        id = 36;
    } else if(tt(x | water, x, x | water, water, x | water, water, x | water, water)) {
        id = 37;
    } else if(tt(water, water, x | water, x, x | water, water, x | water, water)) {
        id = 38;
    } else if(tt(x | water, water, x | water, x, x | water, water, water, water)) {
        id = 39;
    } else if(tt(x | water, water, x | water, x, x | water, water, x | water, water)) {
        id = 40;
    } else if(tt(x | water, water, x | water, water, x | water, x, x | water, x)) {
        id = 41;
    } else if(tt(x | water, x, x | water, water, x | water, water, x | water, x)) {
        id = 42;
    } else if(tt(x | water, x, x | water, x, x | water, water, x | water, water)) {
        id = 43;
    } else if(tt(x | water, water, x | water, x, x | water, x, x | water, water)) {
        id = 44;
    } else if(tt(x | water, x, x | water, x, x | water, x, x | water, x)) {
        id = 45;
    }

    return id;
}
