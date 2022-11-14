#ifndef EBUILDACTION_H
#define EBUILDACTION_H

#include "echaracteraction.h"

#include "characters/eartisan.h"

class eBuildAction : public eCharacterAction {
public:
    eBuildAction(eCharacter* const c);

    void increment(const int by);

    void read(eReadStream& src);
    void write(eWriteStream& dst) const;
private:
    int mSoundTime = 0;
    int mTime = 0;
};

#endif // EBUILDACTION_H
