#include "ezeussanctuary.h"

eZeusSanctuary::eZeusSanctuary(
        const int sw, const int sh, eGameBoard& board) :
    eSanctuary(board, eBuildingType::templeZeus, sw, sh, 60) {}
