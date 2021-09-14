#ifndef EGOD_H
#define EGOD_H

#include "characters/echaracter.h"

enum class eGodType {
    aphrodite,
    apollo,
    ares,
    artemis,
    athena,
    atlas,
    demeter,
    dionysus,
    hades,
    hephaestus,
    hera,
    hermes,
    poseidon,
    zeus
};

class eGod : public eCharacter {
public:
    eGod(eGameBoard& board, const eGodType gt);

    static eGodType sCharacterToGodType(const eCharacterType type);
    static eCharacterType sGodToCharacterType(const eGodType type);

    eGodType type() const { return mType; }
private:
    const eGodType mType;
};

#endif // EGOD_H
