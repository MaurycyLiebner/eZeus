#ifndef EMAPGENERATOR_H
#define EMAPGENERATOR_H

#ifdef __unix__

enum class eTerrain;
class eGameBoard;

struct eMapGeneratorSettings {
    int fWater = sLastWater;
    int fForest = sLastForest;
    int fForestToFertile = sLastForestToFertile;
    int fFertile = sLastFertile;
    int fEmptyDry = sLastEmptyDry;
    int fScrubDry = sLastScrubDry;
    int fFlatStones = sLastFlatStones;
    int fTallStones = sLastTallStones;
    int fElevation = sLastElevation;

    static int sLastWater;
    static int sLastForest;
    static int sLastForestToFertile;
    static int sLastFertile;
    static int sLastEmptyDry;
    static int sLastScrubDry;
    static int sLastFlatStones;
    static int sLastTallStones;
    static int sLastElevation;

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

#endif

#endif // EMAPGENERATOR_H
