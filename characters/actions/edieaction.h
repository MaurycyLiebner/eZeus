#ifndef EDIEACTION_H
#define EDIEACTION_H

#include "echaracteraction.h"

class eDieAction : public eCharacterAction {
public:
    eDieAction(eCharacter* const c);

    void increment(const int by) override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
private:
    int mTime = 0;
};

#endif // EDIEACTION_H
