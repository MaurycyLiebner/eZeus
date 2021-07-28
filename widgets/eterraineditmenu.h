#ifndef ETERRAINEDITMENU_H
#define ETERRAINEDITMENU_H

#include "ewidget.h"

#include "engine/etile.h"
#include "echeckablebutton.h"

enum class eTerrainEditMode {
    scrub = -1,
    dry = static_cast<int>(eTerrain::dry),
    beach = static_cast<int>(eTerrain::beach),
    water = static_cast<int>(eTerrain::water),
    fertile = static_cast<int>(eTerrain::fertile),
    forest = static_cast<int>(eTerrain::forest),

    flatStones = static_cast<int>(eTerrain::flatStones),
    bronze = static_cast<int>(eTerrain::bronze),
    silver = static_cast<int>(eTerrain::silver),
    tallStones = static_cast<int>(eTerrain::tallStones),
    tinyStones = static_cast<int>(eTerrain::tinyStones),
};

class eTerrainEditMenu : public eWidget {
public:
    eTerrainEditMenu(eMainWindow* const window);

    eTerrainEditMode mode() const { return mMode; }
private:
    eTerrainEditMode mMode;

    eWidget* mStonesWidget = nullptr;
    eWidget* mBasicWidget = nullptr;

    eCheckableButton* mBasicButton = nullptr;
    eCheckableButton* mStonesButton = nullptr;
};

#endif // ETERRAINEDITMENU_H
