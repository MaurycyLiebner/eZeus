#include "ezeussanctuary.h"

eZeusSanctuary::eZeusSanctuary(
        const int sw, const int sh, eGameBoard& board) :
    eSanctuary(board, eBuildingType::templeZeus, sw, sh, 60) {}

eApolloSanctuary::eApolloSanctuary(
        const int sw, const int sh, eGameBoard& board) :
    eSanctuary(board, eBuildingType::templeApollo, sw, sh, 60) {}

eAthenaSanctuary::eAthenaSanctuary(
        const int sw, const int sh, eGameBoard& board) :
    eSanctuary(board, eBuildingType::templeAthena, sw, sh, 60) {}
