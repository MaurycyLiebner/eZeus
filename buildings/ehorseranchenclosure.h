#ifndef EHORSERANCHENCLOSURE_H
#define EHORSERANCHENCLOSURE_H

#include "ebuilding.h"

class eHorse;
class eHorseRanch;

class eHorseRanchEnclosure : public eBuilding {
public:
    eHorseRanchEnclosure(eGameBoard& board);
    ~eHorseRanchEnclosure();

    void erase() override;

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const override;
    std::vector<eOverlay> getOverlays(const eTileSize size) const override;

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
