#ifndef ECARTTRANSPORTER_H
#define ECARTTRANSPORTER_H

#include "ebasicpatroler.h"

#include "engine/eresourcetype.h"

class eOx;
class eTrailer;

enum eCartActionTypeSupport {
    take = 1 << 0,
    give = 1 << 1,
    both = take | give
};

class eCartTransporter : public eBasicPatroler {
public:
    eCartTransporter(eGameBoard& board);

    eOverlay getSecondaryTexture(const eTileSize size) const;

    bool isOx() const { return mIsOx; }

    void setIsOx(const bool o);
    void setBigTrailer(const bool b);

    eResourceType resType() const { return mResourceType; }
    int resCount() const { return mResourceCount; }
    bool hasResource() const { return mResourceCount > 0; }

    void setResource(const eResourceType type,
                     const int count);

    int add(const eResourceType type, const int count);
    int take(const eResourceType type, const int count);

    void setActionType(const eCharacterActionType t);

    void setSupport(const eCartActionTypeSupport s) { mSupport = s; }
    eCartActionTypeSupport support() const { return mSupport; }

    bool waiting() const { return mWaiting; }
    void setWaiting(const bool w) { mWaiting = w; }
private:
    int mResourceCount = 0;
    eResourceType mResourceType = eResourceType::none;

    eCartActionTypeSupport mSupport = eCartActionTypeSupport::both;

    bool mWaiting = true;

    bool mIsOx = false;
    bool mBigTrailer = false;

    stdsptr<eOx> mOx;
    stdsptr<eTrailer> mTrailer;
};

#endif // ECARTTRANSPORTER_H
