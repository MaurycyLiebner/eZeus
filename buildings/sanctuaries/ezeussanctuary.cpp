#include "ezeussanctuary.h"

eZeusSanctuary::eZeusSanctuary(
        const int sw, const int sh, eGameBoard& board) :
    eSanctuary(board, eBuildingType::templeZeus, sw, sh, 60) {}

eAphroditeSanctuary::eAphroditeSanctuary(
        const int sw, const int sh, eGameBoard& board) :
    eSanctuary(board, eBuildingType::templeAphrodite, sw, sh, 60) {}

eApolloSanctuary::eApolloSanctuary(
        const int sw, const int sh, eGameBoard& board) :
    eSanctuary(board, eBuildingType::templeApollo, sw, sh, 60) {}

eAthenaSanctuary::eAthenaSanctuary(
        const int sw, const int sh, eGameBoard& board) :
    eSanctuary(board, eBuildingType::templeAthena, sw, sh, 60) {}

eDionysusSanctuary::eDionysusSanctuary(
        const int sw, const int sh, eGameBoard& board) :
    eSanctuary(board, eBuildingType::templeDionysus, sw, sh, 60) {}

eHeraSanctuary::eHeraSanctuary(
        const int sw, const int sh, eGameBoard& board) :
    eSanctuary(board, eBuildingType::templeHera, sw, sh, 60) {}
