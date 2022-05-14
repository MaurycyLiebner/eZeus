#ifndef ERESOURCECOLLECTORBASE_H
#define ERESOURCECOLLECTORBASE_H

#include "echaracter.h"

class eResourceCollectorBase : public eCharacter {
public:
    using eCharacter::eCharacter;

    int collected() const { return mResCollected; }
    void incCollected(const int by = 1) { mResCollected += by; }
private:
    int mResCollected = 0;
};

#endif // ERESOURCECOLLECTORBASE_H
