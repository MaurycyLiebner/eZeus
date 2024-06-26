#include "emapgenerator.h"
#include <libnoise/noise.h>
#include <libnoise/module/perlin.h>
using namespace noise;

#include "spawners/eboarspawner.h"
#include "spawners/edeerspawner.h"

#include "egameboard.h"

int eMapGeneratorSettings::sLastWater = 25;
int eMapGeneratorSettings::sLastForest = 8;
int eMapGeneratorSettings::sLastForestToFertile = 8;
int eMapGeneratorSettings::sLastFertile = 10;
int eMapGeneratorSettings::sLastEmptyDry = 5;
int eMapGeneratorSettings::sLastScrubDry = 25;
int eMapGeneratorSettings::sLastFlatStones = 5;
int eMapGeneratorSettings::sLastTallStones = 5;
int eMapGeneratorSettings::sLastElevation = 9;

eMapGenerator::eMapGenerator(eGameBoard& board) :
    mBoard(board) {
}

void eMapGenerator::generateTerrain(const eMGS& settings) {
    (void)settings;
    module::Perlin p;
    p.SetSeed(rand());
    p.SetOctaveCount(4.0);
    p.SetFrequency(1.0);
    p.SetPersistence(0.5);

    const double div = 50.;

    const int weightSum = settings.fWater +
                          settings.fForest +
                          settings.fForestToFertile +
                          settings.fFertile +
                          settings.fEmptyDry +
                          settings.fScrubDry +
                          settings.fFlatStones +
                          settings.fTallStones +
                          settings.fElevation;
    const int w = mBoard.width();
    const int h = mBoard.height();
    for(int x = 0; x < w; x++) {
        for(int y = 0; y < h; y++) {
            const auto tile = mBoard.dtile(x, y);
            const double v = p.GetValue(x/div, y/div/2, 0.0);
            int w = std::round(0.5*(v + 1)*weightSum);
            eTerrain terr;
            const auto checker = [&w](const int ww) {
                const int oldW = w;
                w -= ww;
                return oldW < ww;
            };
            if(checker(settings.fWater)) {
                terr = eTerrain::water;
            } else if(checker(settings.fForest)) {
                terr = eTerrain::forest;
            } else if(checker(settings.fForestToFertile)) {
                if(rand() % 2) {
                    terr = eTerrain::forest;
                } else {
                    terr = eTerrain::fertile;
                }
            } else if(checker(settings.fFertile)) {
                terr = eTerrain::fertile;
            } else if(checker(settings.fEmptyDry)) {
                terr = eTerrain::dry;
            } else if(checker(settings.fScrubDry)) {
                const int oldW = w + settings.fScrubDry;
                const double frac = double(oldW)/settings.fScrubDry;
                const double dist = std::abs(frac*0.65);
                tile->setScrub(1.25*dist);
                terr = eTerrain::dry;
            } else if(checker(settings.fFlatStones)) {
                terr = eTerrain::flatStones;
            } else if(checker(settings.fTallStones)) {
                terr = eTerrain::tallStones;
            }  else { // if(checker(settings.fElevation)) {
                tile->setAltitude(1);
                terr = eTerrain::dry;
            }
            tile->setTerrain(terr);
        }
    }

    for(int x = 0; x < w; x++) {
        for(int y = 0; y < h; y++) {
            const auto tile = mBoard.dtile(x, y);
            const int alt = tile->altitude();
            const auto tl = tile->topLeft<eTile>();
            const auto tr = tile->topRight<eTile>();
            const auto br = tile->bottomRight<eTile>();
            const auto bl = tile->bottomLeft<eTile>();

            const int tla = tl ? tl->altitude() : alt;
            const int tra = tr ? tr->altitude() : alt;
            const int bra = br ? br->altitude() : alt;
            const int bla = bl ? bl->altitude() : alt;

            double avrg = 0;
            avrg += tla;
            avrg += tra;
            avrg += bra;
            avrg += bla;
            avrg *= 0.25;
            const int iavrg = std::round(avrg);
            int ndiff = 0;
            if(tla != alt) ndiff++;
            if(tra != alt) ndiff++;
            if(bra != alt) ndiff++;
            if(bla != alt) ndiff++;
            if(ndiff > 2) {
                if(iavrg == 0) {
                    if(settings.fTallStones > 0) {
                        tile->setTerrain(eTerrain::tallStones);
                    } else if(settings.fFlatStones > 0) {
                        tile->setTerrain(eTerrain::flatStones);
                    } else if(settings.fScrubDry > 0) {
                        tile->setTerrain(eTerrain::dry);
                        tile->setScrub(1.25*0.65);
                    }
                }
                tile->setAltitude(iavrg);
            }
        }
    }

    for(int x = 0; x < w; x++) {
        for(int y = 0; y < h; y++) {
            const auto tile = mBoard.dtile(x, y);
            if(tile->isElevationTile()) {
                tile->setTerrain(eTerrain::dry);
            }
        }
    }
}

void eMapGenerator::generateStonesResource(
        const eMGS& settings, const eTerrain resource,
        const int min, const int max) {
    (void)settings;

    int generated = 0;
    const int maxIt = 10;
    int it = 0;

    while(generated < min && it++ < maxIt) {
        const double div = 12.5;
        module::Perlin p;
        p.SetSeed(rand());
        p.SetOctaveCount(1.0);
        p.SetFrequency(1.0);
        p.SetPersistence(0.5);

        const int w = mBoard.width();
        const int h = mBoard.height();
        for(int x = 0; x < w; x++) {
            for(int y = 0; y < h; y++) {
                const auto tile = mBoard.dtile(x, y);
                if(tile->isElevationTile()) {
                    tile->setTerrain(eTerrain::dry);
                } else {
                    const auto terr = tile->terrain();
                    if(terr == eTerrain::flatStones) {
                        const double r = p.GetValue(x/div, y/div, 0.0);
                        if(r > 0.4) {
                            tile->setTerrain(resource);
                            if(++generated >= max) return;
                        }
                    }
                }
            }
        }
    }
}

void eMapGenerator::generateSilverAndBronze(const eMGS& settings) {
    if(settings.fCoppper) {
        generateStonesResource(settings, eTerrain::copper, 10, 15);
    }
    if(settings.fSilver) {
        generateStonesResource(settings, eTerrain::silver, 10, 15);
    }
}

void eMapGenerator::generateAnimals(const eMGS& settings) {
    const int n = settings.fHuntable;
    for(int i = 0; i < n; i++) {
        const int w = mBoard.width();
        const int h = mBoard.height();

        const int margin = 10;
        const int x = margin + rand() % (w - 2*margin);
        const int y = margin + rand() % (h - 2*margin);

        const auto tile = mBoard.dtile(x, y);
        const auto terr = tile->terrain();
        if(terr != eTerrain::dry &&
           terr != eTerrain::forest &&
           terr != eTerrain::fertile) {
            i--;
            continue;
        }
        stdsptr<eSpawner> spawner;
        if(rand() % 2) {
            spawner = std::make_shared<eBoarSpawner>(0, tile, mBoard);
        } else {
            spawner = std::make_shared<eDeerSpawner>(0, tile, mBoard);
        }
        tile->setBanner(spawner);
    }
}

void eMapGenerator::generate(const eMGS& settings) {
    eMGS::sLastWater = settings.fWater;
    eMGS::sLastForest = settings.fForest;
    eMGS::sLastForestToFertile = settings.fForestToFertile;
    eMGS::sLastFertile = settings.fFertile;
    eMGS::sLastEmptyDry = settings.fEmptyDry;
    eMGS::sLastScrubDry = settings.fScrubDry;
    eMGS::sLastFlatStones = settings.fFlatStones;
    eMGS::sLastTallStones = settings.fTallStones;
    eMGS::sLastElevation = settings.fElevation;

    mBoard.initialize(mBoard.width(), mBoard.height());
    generateTerrain(settings);
//    generateSilverAndBronze(settings);
//    generateAnimals(settings);
    mBoard.updateMarbleTiles();
    mBoard.scheduleTerrainUpdate();
}
