#ifndef ETHREADCHARACTER_H
#define ETHREADCHARACTER_H

#include "characters/echaracter.h"

class eThreadCharacter {
public:
    void load(eCharacter* const character);

    eCharacterType type() const { return mType; }
    int playerId() const { return mPlayerId; }
    bool isDead() const { return mHP <= 0; }
private:
    eCharacterType mType;
    int mPlayerId{1};
    int mHP = 1000;
    eCharacterActionType mActionType{eCharacterActionType::walk};
};

#endif // ETHREADCHARACTER_H
