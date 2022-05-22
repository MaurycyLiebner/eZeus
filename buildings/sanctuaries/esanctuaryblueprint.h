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

    static void load();
    static bool loaded();

    eSanctBlueprint fHephaestusW;
    eSanctBlueprint fHephaestusH;

    eSanctBlueprint fArtemisW;
    eSanctBlueprint fArtemisH;
private:
    void loadImpl();

    bool mLoaded = false;
};

#endif // ESANCTUARYBLUEPRINT_H
