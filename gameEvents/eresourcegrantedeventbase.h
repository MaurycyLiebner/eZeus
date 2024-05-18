#ifndef ERESOURCEGRANTEDEVENTBASE_H
#define ERESOURCEGRANTEDEVENTBASE_H

#include "egameevent.h"

#include "engine/eworldcity.h"
#include "engine/eevent.h"

class eResourceGrantedEventBase : public eGameEvent {
public:
    eResourceGrantedEventBase(const eEvent giftCashAccepted,
                              const eEvent giftAccepted,
                              const eEvent giftPostponed,
                              const eEvent giftRefused,
                              const eEvent giftForfeited,
                              const eEvent giftGranted,
                              const eEvent giftLastChance,
                              const eEvent giftInsufficientSpace,
                              const eEvent giftPartialSpace,
                              const eGameEventType type,
                              const eGameEventBranch branch,
                              eGameBoard& board);

    void initialize(const bool postpone,
                    const eResourceType res,
                    const int count,
                    const stdsptr<eWorldCity>& c);

    void trigger() override;

    void write(eWriteStream& dst) const override;
    void read(eReadStream& src) override;

    const stdsptr<eWorldCity>& city() const { return mCity; }
    void setCity(const stdsptr<eWorldCity>& c);

    eResourceType resourceType() const { return mResource; }
    void setResourceType(const eResourceType type);

    int resourceCount() const { return mCount; }
    void setResourceCount(const int c);
protected:
    bool mPostpone = true;
    eResourceType mResource = eResourceType::fleece;
    int mCount = 16;
    stdsptr<eWorldCity> mCity;
private:
    eEvent mGiftCashAccepted;
    eEvent mGiftAccepted;
    eEvent mGiftPostponed;
    eEvent mGiftRefused;
    eEvent mGiftForfeited;
    eEvent mGiftGranted;
    eEvent mGiftLastChance;
    eEvent mGiftInsufficientSpace;
    eEvent mGiftPartialSpace;
};

#endif // ERESOURCEGRANTEDEVENTBASE_H
