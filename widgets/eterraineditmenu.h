#ifndef ETERRAINEDITMENU_H
#define ETERRAINEDITMENU_H

#include "ewidget.h"

enum class eTerrainEditMode {
    scrub, forest, dry, beach, water, fertile
};

class eTerrainEditMenu : public eWidget {
public:
    eTerrainEditMenu(eMainWindow* const window);

    eTerrainEditMode mode() const { return mMode; }
private:
    eTerrainEditMode mMode;
};

#endif // ETERRAINEDITMENU_H
