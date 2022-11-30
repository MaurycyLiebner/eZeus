#include "ewaterdistributor.h"

#include "textures/egametextures.h"

eWaterDistributor::eWaterDistributor(eGameBoard& board) :
    eBasicPatroler(board, &eCharacterTextures::fWaterDistributor,
                   eCharacterType::waterDistributor) {
    eGameTextures::loadWaterDistributor();
    setProvide(eProvide::water, 10000);
}
