#include "emapgenerator.h"
#include <libnoise/noise.h>
#include <libnoise/module/perlin.h>
using namespace noise;

#include "spawners/eboarspawner.h"
#include "spawners/edeerspawner.h"

#include "egameboard.h"

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

    const int w = mBoard.width();
    const int h = mBoard.height();
    for(int x = 0; x < w; x++) {
        for(int y = 0; y < h; y++) {
            const auto tile = mBoard.dtile(x, y);
            const double v = p.GetValue(x/div, y/div/2, 0.0);
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
            } else if(v < 0.65) {
                const double dist = std::abs(v - 0.1);
                tile->setScrub(1.25*dist);
                terr = eTerrain::dry;
            } else if(v < 0.75) {
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

    std::vector<std::vector<eTile*>> waterMasses;

    const auto inMasses = [&](eTile* const t) {
        for(const auto& mass : waterMasses) {
            for(const auto tm : mass) {
                if(tm == t) return true;
            }
        }
        return false;
    };

    const auto neighsWithWater = [&](eTile* const t) {
        const auto tl = t->topLeft<eTile>();
        const auto bl = t->bottomLeft<eTile>();
        const auto br = t->bottomRight<eTile>();
        const auto tr = t->topRight<eTile>();
        std::vector<eTile*> result;
        if(tl && tl->terrain() == eTerrain::water) {
            result.push_back(tl);
        }
        if(bl && bl->terrain() == eTerrain::water) {
            result.push_back(bl);
        }
        if(br && br->terrain() == eTerrain::water) {
            result.push_back(br);
        }
        if(tr && tr->terrain() == eTerrain::water) {
            result.push_back(tr);
        }
        return result;
    };

    std::function<void(eTile* const tt, std::vector<eTile*>& newMass)> processTile;
    processTile = [&](eTile* const tt, std::vector<eTile*>& newMass) {
        newMass.push_back(tt);
        const auto ns = neighsWithWater(tt);
        for(const auto n : ns) {
            if(inMasses(n)) continue;
            processTile(n, newMass);
        }
    };

    for(int tx = 0; tx < w; tx++) {
        for(int ty = 0; ty < h; ty++) {
            const auto t = mBoard.dtile(tx, ty);
            if(t->terrain() != eTerrain::water) continue;
            if(inMasses(t)) continue;
            auto& newMass = waterMasses.emplace_back();
            processTile(t, newMass);
        }
    }

    for(const auto& rm : waterMasses) {
        const int iMax = sqrt(rm.size())/5;
        for(int i = 0; i < iMax; i++) {
            const auto tile = rm[rand() % rm.size()];
            eTile* ct = tile;
            while(true) {
                const int tx = ct->x();
                const int ty = ct->y();
                const double v = p.GetValue(tx/div, ty/div, 0.0);
                bool found = false;
                std::vector<eTile*> valiable;
                for(int x = -1; x <= 1 && !found; x++) {
                    for(int y = -1; y <= 1 && !found; y++) {
                        if(x == 0 && y == 0) continue;
                        const int ttx = tx + x;
                        const int tty = ty + y;
                        const auto tt = mBoard.dtile(ttx, tty);
                        if(!tt) continue;
                        const double vv = p.GetValue(ttx/div, tty/div, 0.0);
                        if(v < vv) {
                            if(x != 0 && y != 0) {
                                tt->setTerrain(eTerrain::water);
                            } else {
                                valiable.push_back(tt);
                            }
                        }
                    }
                }
                if(valiable.empty()) break;

                ct = valiable[rand() % valiable.size()];
                ct->setTerrain(eTerrain::water);
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
            if(ndiff > 2) tile->setAltitude(iavrg);
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
    mBoard.initialize(mBoard.width(), mBoard.height());
    generateTerrain(settings);
    generateSilverAndBronze(settings);
    generateAnimals(settings);
    mBoard.updateMarbleTiles();
    mBoard.scheduleTerrainUpdate();
}
