#include "egymnast.h"

eGymnast::eGymnast(eGameBoard& board) :
    eBasicPatroler(board, &eCharacterTextures::fGymnast,
                   eCharacterType::gymnast) {
    setProvide(eProvide::gymnast, 10000);
}
