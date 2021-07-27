#ifndef ETERRAINEDITMENU_H
#define ETERRAINEDITMENU_H

#include "ewidget.h"

enum class eTerrainEditMode {
    scrub, forest, dry, beach, river, fertile
};

class eTerrainEditMenu : public eWidget {
public:
    eTerrainEditMenu(eMainWindow* const window);

private:
    eTerrainEditMode mMode;
};

#endif // ETERRAINEDITMENU_H
