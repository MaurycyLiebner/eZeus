#ifndef ECOLUMN_H
#define ECOLUMN_H

#include "eaestheticsbuilding.h"

class eColumn : public eAestheticsBuilding {
public:
    using eAestheticsBuilding::eAestheticsBuilding;

    std::vector<eOverlay> getOverlays(const eTileSize size) const;
};

class eDoricColumn : public eColumn {
public:
    eDoricColumn(eGameBoard& board);
};

class eIonicColumn : public eColumn {
public:
    eIonicColumn(eGameBoard& board);
};

class eCorinthianColumn : public eColumn {
public:
    eCorinthianColumn(eGameBoard& board);
};


#endif // ECOLUMN_H
