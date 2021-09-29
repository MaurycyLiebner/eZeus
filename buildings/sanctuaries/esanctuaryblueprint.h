#ifndef ESANCTUARYBLUEPRINT_H
#define ESANCTUARYBLUEPRINT_H

#include <vector>

enum class eSanctEleType {
    none,
    stairs,
    tile,
    statue,
    monument,
    altar,
    sanctuary,
    copper
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

    void load();

    bool fLoaded = false;

    eSanctBlueprint fHephaestusW;
    eSanctBlueprint fHephaestusH;
};

#endif // ESANCTUARYBLUEPRINT_H
