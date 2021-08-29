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

    const double div = 25.;

    const int w = mBoard.width();
    const int h = mBoard.height();
    for(int x = 0; x < w; x++) {
        for(int y = 0; y < h; y++) {
            const auto tile = mBoard.tile(x, y);
            const double v = p.GetValue(x/div, y/div, 0.0);
            eTerrain terr;
            if(v < -0.5) {
                terr = eTerrain::water;
            } else if(v < -0.35) {
                terr = eTerrain::forest;
            } else if(v < -0.2) {
                if(rand() % 2) {
                    terr = eTerrain::forest;
                } else {
                    terr = eTerrain::fertile;
                }
            } else if(v < 0.0) {
                terr = eTerrain::fertile;
            } else if(v < 0.1) {
                terr = eTerrain::dry;
            } else if(v < 0.55) {
                const double dist = std::abs(v - 0.1);
                tile->setScrub(1.5*dist);
                terr = eTerrain::dry;
            } else if(v < 0.70) {
                terr = eTerrain::flatStones;
            } else if(v < 0.85) {
                terr = eTerrain::tallStones;
            }  else {
                tile->setAltitude(1);
                terr = eTerrain::dry;
            }
            tile->setTerrain(terr);
        }
    }

    module::Perlin resource;
    resource.SetSeed(p.GetSeed() + 100);
    resource.SetOctaveCount(1.0);
    resource.SetFrequency(1.0);
    resource.SetPersistence(0.5);

    for(int x = 0; x < w; x++) {
        for(int y = 0; y < h; y++) {
            const auto tile = mBoard.tile(x, y);
            if(tile->isElevationTile()) {
                tile->setTerrain(eTerrain::dry);
            } else {
                const auto terr = tile->terrain();
                if(terr == eTerrain::flatStones) {
                    const double r = resource.GetValue(x/div, y/div, 0.0);
                    if(r > 0.55) {
                        tile->setTerrain(eTerrain::bronze);
                    } else if(r < -0.55) {
                        tile->setTerrain(eTerrain::silver);
                    }
                }
            }
        }
    }
}
