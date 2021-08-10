#ifndef ETERRAINEDITMENU_H
#define ETERRAINEDITMENU_H

#include "egamemenubase.h"

#include "engine/etile.h"
#include "echeckablebutton.h"

enum class eTerrainEditMode {
    scrub = -1,
    dry = static_cast<int>(eTerrain::dry),
    beach = static_cast<int>(eTerrain::beach),
    water = static_cast<int>(eTerrain::water),
    fertile = static_cast<int>(eTerrain::fertile),
    forest = static_cast<int>(eTerrain::forest),
    choppedForest = static_cast<int>(eTerrain::choppedForest),

    flatStones = static_cast<int>(eTerrain::flatStones),
    bronze = static_cast<int>(eTerrain::bronze),
    silver = static_cast<int>(eTerrain::silver),
    tallStones = static_cast<int>(eTerrain::tallStones),
    tinyStones = static_cast<int>(eTerrain::tinyStones),

    raise,
    lower,
    levelOut,
    resetElev,
    makeWalkable,

    boar
};

class eTerrainEditMenu : public eGameMenuBase {
public:
    using eGameMenuBase::eGameMenuBase;

    void initialize();

    eTerrainEditMode mode() const;
private:
    eTerrainEditMode mMode = eTerrainEditMode::dry;

    eCheckableButton* mB1 = nullptr;
    eCheckableButton* mB4 = nullptr;
    eCheckableButton* mB7 = nullptr;

    std::vector<eWidget*> mWidgets;
};

#endif // ETERRAINEDITMENU_H
