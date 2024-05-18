#ifndef ETERRAINEDITMENU_H
#define ETERRAINEDITMENU_H

#include "egamemenubase.h"

#include "engine/etile.h"
#include "echeckablebutton.h"

enum class eTerrainEditMode {
    dry = static_cast<int>(eTerrain::dry),
    beach = static_cast<int>(eTerrain::beach),
    water = static_cast<int>(eTerrain::water),
    fertile = static_cast<int>(eTerrain::fertile),
    forest = static_cast<int>(eTerrain::forest),
    choppedForest = static_cast<int>(eTerrain::choppedForest),

    flatStones = static_cast<int>(eTerrain::flatStones),
    bronze = static_cast<int>(eTerrain::copper),
    silver = static_cast<int>(eTerrain::silver),
    tallStones = static_cast<int>(eTerrain::tallStones),
    marble = static_cast<int>(eTerrain::marble),

    none,
    scrub,

    raise,
    lower,
    levelOut,
    resetElev,
    makeWalkable,

    boar,
    deer,
    fish,

    fire,
    ruins,

    entryPoint,
    exitPoint,
    landInvasion
};

class eTerrainEditMenu : public eGameMenuBase {
public:
    using eGameMenuBase::eGameMenuBase;

    void initialize();

    eTerrainEditMode mode() const;
    int modeId() const { return mModeId; }
private:
    eTerrainEditMode mMode = eTerrainEditMode::dry;
    int mModeId = 0;

    eCheckableButton* mB1 = nullptr;
    eCheckableButton* mB4 = nullptr;
    eCheckableButton* mB7 = nullptr;

    std::vector<eWidget*> mWidgets;
};

#endif // ETERRAINEDITMENU_H
