#ifndef ECARTTRANSPORTER_H
#define ECARTTRANSPORTER_H

#include "ebasicpatroler.h"

#include "engine/eresourcetype.h"

class eOx;
class eTrailer;

class eCartTransporter : public eBasicPatroler {
public:
    eCartTransporter(eGameBoard& board);

    eOverlay getSecondaryTexture(const eTileSize size) const;

    bool isOx() const { return mIsOx; }

    void setIsOx(const bool o);
    void setBigTrailer(const bool b);

    eResourceType resType() const { return mResourceType; }
    int resCount() const { return mResourceCount; }

    void setResource(const eResourceType type,
                     const int count);

    void setActionType(const eCharacterActionType t);
private:
    int mResourceCount = 0;
    eResourceType mResourceType = eResourceType::none;

    bool mIsOx = false;
    bool mBigTrailer = false;

    stdsptr<eOx> mOx;
    stdsptr<eTrailer> mTrailer;
};

#endif // ECARTTRANSPORTER_H
