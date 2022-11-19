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

enum class eCartTransporterType {
    basic,
    ox,
    food,
    fleece,
    oil,
    wine,
    arms,
    horse
};

class eCartTransporter : public eBasicPatroler {
public:
    eCartTransporter(eGameBoard& board);

    eOverlay getSecondaryTexture(const eTileSize size) const override;

    bool isOx() const { return mIsOx; }

    void setType(const eCartTransporterType t);
    void setBigTrailer(const bool b);

    eResourceType resType() const { return mResourceType; }
    int resCount() const { return mResourceCount; }
    bool hasResource() const { return mResourceCount > 0; }

    void setResource(const eResourceType type,
                     const int count);

    int add(const eResourceType type, const int count);
    int take(const eResourceType type, const int count);

    void setActionType(const eCharacterActionType t) override;

    void setSupport(const eCartActionTypeSupport s) { mSupport = s; }
    eCartActionTypeSupport support() const { return mSupport; }

    bool waiting() const { return mWaiting; }
    void setWaiting(const bool w) { mWaiting = w; }

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
private:
    void updateTextures();

    int mResourceCount = 0;
    eCartTransporterType mType = eCartTransporterType::basic;
    eResourceType mResourceType = eResourceType::none;

    eCartActionTypeSupport mSupport = eCartActionTypeSupport::both;

    bool mWaiting = true;

    bool mIsOx = false;
    bool mBigTrailer = false;

    stdptr<eOx> mOx;
    stdptr<eTrailer> mTrailer;

    std::vector<stdptr<eCharacter>> mFollowers;
};

#endif // ECARTTRANSPORTER_H
