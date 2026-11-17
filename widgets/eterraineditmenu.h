#ifndef ETERRAINEDITMENU_H
#define ETERRAINEDITMENU_H

#include "egamemenubase.h"

#include "engine/etile.h"
#include "echeckablebutton.h"

class eRotateButton;
class eMiniMap;
class eGameWidget;
class eActionListWidget;

enum class eTerrainEditMode {
    dry = static_cast<int>(eTerrain::dry),
    beach = static_cast<int>(eTerrain::beach),
    water = static_cast<int>(eTerrain::water),
    marsh = static_cast<int>(eTerrain::marsh),
    fertile = static_cast<int>(eTerrain::fertile),
    forest = static_cast<int>(eTerrain::forest),
    choppedForest = static_cast<int>(eTerrain::choppedForest),

    flatStones = static_cast<int>(eTerrain::flatStones),
    bronze = static_cast<int>(eTerrain::copper),
    silver = static_cast<int>(eTerrain::silver),
    orichalc = static_cast<int>(eTerrain::orichalc),
    tallStones = static_cast<int>(eTerrain::tallStones),
    marble = static_cast<int>(eTerrain::marble),

    none = static_cast<int>(eTerrain::marble) + 1,
    scrub,
    scrubArea,
    removeScrub,
    softenScrub,

    rainforest,
    normalForest,

    raise,
    lower,
    raiseHigh,
    lowerHigh,
    levelOut,
    resetElev,
    halfSlope,
    makeWalkable,

    boar,
    deer,
    fish,
    urchin,

    fire,
    ruins,

    entryPoint,
    exitPoint,
    riverEntryPoint,
    riverExitPoint,
    landInvasion,
    seaInvasion,
    disembarkPoint,
    monsterPoint,

    quake,
    lava,
    tidalWave,
    landSlide,
    disasterPoint,
    landSlidePoint,

    cityTerritory,
    assignAllCityTerritory,

    blackMarble = static_cast<int>(eTerrain::blackMarble)
};

enum class eBrushType {
    apply,
    brush,
    square
};

class eTerrainEditMenu : public eGameMenuBase {
public:
    using eGameMenuBase::eGameMenuBase;

    void initialize(eGameWidget* const gw,
                    eGameBoard* const board);

    eTerrainEditMode mode() const;
    int modeId() const { return mModeId; }

    eMiniMap* miniMap() const { return mMiniMap; }

    void setWorldDirection(const eWorldDirection dir);

    eBrushType brushType() const;
    int brushSize() const;

    void updateCitiesOnBoard(eGameBoard& board);
private:
    eBrushType mBrushType = eBrushType::apply;
    int mBrushSize = 1;
    eTerrainEditMode mMode = eTerrainEditMode::dry;
    int mModeId = 0;
    int mSpacing = 0;

    eCheckableButton* mB1 = nullptr;
    eCheckableButton* mB4 = nullptr;

    std::map<eCityId, eWidget*> mTerrioryButtons;
    eActionListWidget* mW12 = nullptr;

    eRotateButton* mRotateButton = nullptr;
    eMiniMap* mMiniMap = nullptr;

    std::vector<eWidget*> mWidgets;
};

#endif // ETERRAINEDITMENU_H
