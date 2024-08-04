#ifndef ENUMBERS_H
#define ENUMBERS_H

struct eNumbers {
    static void sLoad();

    static int sBoarMaxCount;
    static int sBoarSpawnPeriod;
    static int sDeerMaxCount;
    static int sDeerSpawnPeriod;

    static int sOlivePressProcessingPeriod;
    static int sWineryProcessingPeriod;
    static int sArmoryProcessingPeriod;
    static int sSculptureStudioProcessingPeriod;

    static int sOliveTreeRipePeriod;
    static int sVineRipePeriod;
    static int sOrangeTreeRipePeriod;

    static double sTreeVineFullyRipePeriodMultiplier;

    static double sTreeVineBlessedFullyRipePeriodMultiplier;
    static double sTreeVineBlessedRipePeriodMultiplier;
    static double sTreeVineCursedFullyRipePeriodMultiplier;
    static double sTreeVineCursedRipePeriodMultiplier;

    static int sLandMonsterInvadePeriod;
    static int sWaterMonsterInvadePeriod;
    static int sMonsterAttackPeriod;

    static int sFriendlyGodVisitPeriod;
    static int sGodHelpPeriod;
};

#endif // ENUMBERS_H
