#ifndef ETHREADCHARACTER_H
#define ETHREADCHARACTER_H

#include "characters/echaracterbase.h"

class eThreadCharacter : public eCharacterBase {
public:
    eThreadCharacter();
    void load(eCharacterBase* const character);
};

#endif // ETHREADCHARACTER_H
