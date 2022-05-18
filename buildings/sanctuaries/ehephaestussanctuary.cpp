#include "ehephaestussanctuary.h"

#include "textures/ebuildingtextures.h"

eHephaestusSanctuary::eHephaestusSanctuary(
        const int sw, const int sh, eGameBoard& board) :
    eSanctuary(board, eBuildingType::templeHephaestus, sw, sh, 60) {

}
