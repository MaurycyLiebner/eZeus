#ifndef ESANCTUARYBLUEPRINT_H
#define ESANCTUARYBLUEPRINT_H

#include <vector>

#include "buildings/ebuilding.h"

enum class eSanctEleType {
    none,
    stairs,
    tile,
    monument,
    altar,
    sanctuary,
    copper,
    oliveTree,
    vine,
    orangeTree,

    defaultStatue,
    aphroditeStatue,
    apolloStatue,
    aresStatue,
    artemisStatue,
    athenaStatue,
    atlasStatue,
    demeterStatue,
    dionysusStatue,
    hadesStatue,
    hephaestusStatue,
    heraStatue,
    hermesStatue,
    poseidonStatue,
    zeusStatue,
};

struct eSanctEle {
    int fX;
    int fY;
    int fA;
    int fId;
    eSanctEleType fType;
};

struct eSanctBlueprint {
    int fW;
    int fH;
    std::vector<std::vector<eSanctEle>> fTiles;
};

class eSanctBlueprints {
public:
    static eSanctBlueprints instance;

    static const eSanctBlueprint* sSanctuaryBlueprint(
            const eBuildingType type, const bool rotate);

    static void load();
    static bool loaded();

    eSanctBlueprint fZeusW;
    eSanctBlueprint fZeusH;

    eSanctBlueprint fAresW;
    eSanctBlueprint fAresH;

    eSanctBlueprint fAphroditeW;
    eSanctBlueprint fAphroditeH;

    eSanctBlueprint fApolloW;
    eSanctBlueprint fApolloH;

    eSanctBlueprint fAthenaW;
    eSanctBlueprint fAthenaH;

    eSanctBlueprint fArtemisW;
    eSanctBlueprint fArtemisH;

    eSanctBlueprint fDemeterW;
    eSanctBlueprint fDemeterH;

    eSanctBlueprint fDionysusW;
    eSanctBlueprint fDionysusH;

    eSanctBlueprint fHephaestusW;
    eSanctBlueprint fHephaestusH;

    eSanctBlueprint fHeraW;
    eSanctBlueprint fHeraH;

    eSanctBlueprint fHermesW;
    eSanctBlueprint fHermesH;
private:
    void loadImpl();

    bool mLoaded = false;
};

#endif // ESANCTUARYBLUEPRINT_H
