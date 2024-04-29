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

eAtlasSanctuary::eAtlasSanctuary(
        const int sw, const int sh, eGameBoard& board) :
    eSanctuary(board, eBuildingType::templeAtlas, sw, sh, 60) {}

eAthenaSanctuary::eAthenaSanctuary(
        const int sw, const int sh, eGameBoard& board) :
    eSanctuary(board, eBuildingType::templeAthena, sw, sh, 60) {}

eDemeterSanctuary::eDemeterSanctuary(
        const int sw, const int sh, eGameBoard& board) :
    eSanctuary(board, eBuildingType::templeDemeter, sw, sh, 60) {}

eDionysusSanctuary::eDionysusSanctuary(
        const int sw, const int sh, eGameBoard& board) :
    eSanctuary(board, eBuildingType::templeDionysus, sw, sh, 60) {}

eHadesSanctuary::eHadesSanctuary(
        const int sw, const int sh, eGameBoard& board) :
    eSanctuary(board, eBuildingType::templeHades, sw, sh, 60) {}

eHeraSanctuary::eHeraSanctuary(
        const int sw, const int sh, eGameBoard& board) :
    eSanctuary(board, eBuildingType::templeHera, sw, sh, 60) {}

eHermesSanctuary::eHermesSanctuary(
        const int sw, const int sh, eGameBoard& board) :
    eSanctuary(board, eBuildingType::templeHermes, sw, sh, 60) {}

ePoseidonSanctuary::ePoseidonSanctuary(
        const int sw, const int sh, eGameBoard& board) :
    eSanctuary(board, eBuildingType::templePoseidon, sw, sh, 60) {}
