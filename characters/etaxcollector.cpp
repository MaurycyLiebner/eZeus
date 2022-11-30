#include "etaxcollector.h"

#include "textures/egametextures.h"

eTaxCollector::eTaxCollector(eGameBoard& board) :
    eBasicPatroler(board, &eCharacterTextures::fTaxCollector,
                   eCharacterType::taxCollector) {
    eGameTextures::loadTaxCollector();
    setProvide(eProvide::taxes, __INT_MAX__);
}
