#ifndef EFIGHTACTION_H
#define EFIGHTACTION_H

#include "echaracteraction.h"
#include "characters/echaracter.h"

class eFightAction : public eCharacterAction {
public:
    eFightAction(eCharacter* const c,
                 eCharacter* const o);

    void increment(const int by) override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
private:
    stdptr<eCharacter> mOpponent;

    int mTime = 0;
};

#endif // EFIGHTACTION_H
