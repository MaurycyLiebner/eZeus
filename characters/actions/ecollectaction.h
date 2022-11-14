#ifndef ECOLLECTACTION_H
#define ECOLLECTACTION_H

#include "echaracteraction.h"

#include "characters/eresourcecollector.h"

enum class eTranformFunc {
    none,
    tree,
    marble
};

class eCollectAction : public eCharacterAction {
public:
    eCollectAction(eCharacter* const c,
                   const eTranformFunc tf);
    eCollectAction(eCharacter* const c);

    void increment(const int by);

    void read(eReadStream& src);
    void write(eWriteStream& dst) const;
private:
    int mSoundTime = 0;
    int mTime = 0;
    eTile* mTile = nullptr;
    eTranformFunc mTransFunc = eTranformFunc::none;
};

#endif // ECOLLECTACTION_H
