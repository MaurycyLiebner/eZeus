#ifndef ETRANSPORTERBASE_H
#define ETRANSPORTERBASE_H

#include "ebasicpatroler.h"

#include "engine/eresourcetype.h"

class eTransporterBase : public eBasicPatroler {
public:
    using eBasicPatroler::eBasicPatroler;

    eResourceType resType() const { return mResourceType; }
    int resCount() const { return mResourceCount; }

    void setResource(const eResourceType type,
                     const int count);
private:
    int mResourceCount = 0;
    eResourceType mResourceType = eResourceType::none;
};

#endif // ETRANSPORTERBASE_H
