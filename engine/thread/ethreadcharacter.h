#ifndef ETHREADCHARACTER_H
#define ETHREADCHARACTER_H

#include "characters/echaracter.h"

class eThreadCharacter {
public:
    eThreadCharacter(eCharacter* const character);

private:
    eCharacterType mType;
    int mPlayerId{1};
    int mHP = 1000;
    eCharacterActionType mActionType{eCharacterActionType::walk};
};

#endif // ETHREADCHARACTER_H
