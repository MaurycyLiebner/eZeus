#include "ewaterdistributor.h"

eWaterDistributor::eWaterDistributor(eGameBoard& board) :
    eBasicPatroler(board, &eCharacterTextures::fWaterDistributor,
                   eCharacterType::waterDistributor) {}
