#include "echaracteractionfunction.h"

eCharacterActionFunction::eCharacterActionFunction(
        eGameBoard& board, const eCharActFuncType t) :
    mBoard(board), mType(t) {}
