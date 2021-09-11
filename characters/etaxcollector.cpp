#include "etaxcollector.h"

eTaxCollector::eTaxCollector(eGameBoard& board) :
    eBasicPatroler(board, &eCharacterTextures::fTaxCollector,
                   eCharacterType::taxCollector) {
    setProvide(eProvide::taxes, __INT_MAX__);
}
