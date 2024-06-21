#include "echaracteractionfunction.h"

#include "characters/echaracter.h"

eCharacterActionFunction::eCharacterActionFunction(
        eGameBoard& board, const eCharActFuncType t) :
    mBoard(board), mType(t) {}
