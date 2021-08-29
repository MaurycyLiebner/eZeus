#include "emapgenerator.h"

#include <libnoise/noise.h>
#include <libnoise/module/perlin.h>
using namespace noise;

eMapGenerator::eMapGenerator(eGameBoard& board) :
    mBoard(board) {
}

void eMapGenerator::generate() {
    module::Perlin p;
    p.SetOctaveCount(4.0);
    p.SetFrequency(1.0);
    p.SetPersistence(0.5);

    const int w = mBoard.width();
    const int h = mBoard.height();
    for(int x = 0; x < w; x++) {
        for(int y = 0; y < h; y++) {
            const auto tile = mBoard.tile(x, y);
            const double div = 25.;
            const double v = p.GetValue(x/div, y/div, 0.0);
            eTerrain terr;
            if(v < -0.5) {
                terr = eTerrain::water;
            } else if(v < -0.45) {
                terr = eTerrain::beach;
            } else if(v < -0.15) {
                terr = eTerrain::forest;
            } else if(v < 0) {
                if(rand() % 2) {
                    terr = eTerrain::forest;
                } else {
                    terr = eTerrain::fertile;
                }
            } else if(v < 0.1) {
                terr = eTerrain::fertile;
            } else if(v < 0.25) {
                terr = eTerrain::dry;
            } else if(v < 0.65) {
                const double dist = std::abs(v - 0.65);
                tile->setScrub(0.6 - dist);
                terr = eTerrain::dry;
            } else if(v < 0.75) {
                terr = eTerrain::flatStones;
            } else if(v < 0.90) {
                terr = eTerrain::tallStones;
            }  else {
                tile->setAltitude(1);
                terr = eTerrain::dry;
            }
            tile->setTerrain(terr);
        }
    }
}
