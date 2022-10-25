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

    static eGodType sCharacterToGodType(const eCharacterType type,
                                        bool* const valid = nullptr);
    static eCharacterType sGodToCharacterType(const eGodType type);
    static stdsptr<eGod> sCreateGod(const eGodType type, eGameBoard& board);

    eGodType type() const { return mType; }
private:
    const eGodType mType;
};

#endif // EGOD_H
