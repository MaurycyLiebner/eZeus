#ifndef EHORSERANCHENCLOSURE_H
#define EHORSERANCHENCLOSURE_H

#include "ebuildingwithresource.h"

class eHorse;
class eHorseRanch;

class eHorseRanchEnclosure : public eBuildingWithResource {
public:
    eHorseRanchEnclosure(eGameBoard& board);
    ~eHorseRanchEnclosure();

    void erase() override;

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const override;
    std::vector<eOverlay> getOverlays(const eTileSize size) const override;

    int count(const eResourceType type) const override;
    int take(const eResourceType type, const int count) override;

    int horseCount() const { return mHorses.size(); }

    bool spawnHorse();
    bool takeHorse();

    void setRanch(eHorseRanch* const ranch);
    eHorseRanch* ranch() const { return mRanch; }

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
private:
    std::vector<stdsptr<eHorse>> mHorses;

    eHorseRanch* mRanch = nullptr;
};

#endif // EHORSERANCHENCLOSURE_H
