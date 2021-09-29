#include "ehephaestussanctuary.h"

#include "textures/ebuildingtextures.h"

eHephaestusSanctuary::eHephaestusSanctuary(
        const int sw, const int sh, eGameBoard& board) :
    eSanctuary(&eBuildingTextures::fHephaestusStatues,
               &eBuildingTextures::fHephaestusMonuments,
               board, eBuildingType::templeHephaestus, sw, sh, 60) {

}
