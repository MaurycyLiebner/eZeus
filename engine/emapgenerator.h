#ifndef EMAPGENERATOR_H
#define EMAPGENERATOR_H

#include "egameboard.h"

struct eMapGeneratorSettings {
    bool fCoppper = true;
    bool fSilver = true;
    int fHuntable = 2;
    int fFish = 2;
};

class eMapGenerator {
public:
    eMapGenerator(eGameBoard& board);

    using eMGS = eMapGeneratorSettings;
    void generate(const eMGS& settings);
private:
    void generateTerrain(const eMGS& settings);
    void generateStonesResource(const eMGS& settings,
                               const eTerrain resource,
                               const int min, const int max);
    void generateSilverAndBronze(const eMGS& settings);
    void generateAnimals(const eMGS& settings);

    eGameBoard& mBoard;
};

#endif // EMAPGENERATOR_H
