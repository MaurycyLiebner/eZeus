#ifndef EHORSERANCHENCLOSURE_H
#define EHORSERANCHENCLOSURE_H

#include "ebuilding.h"

class eHorse;
class eHorseRanch;

class eHorseRanchEnclosure : public eBuilding {
public:
    eHorseRanchEnclosure(eGameBoard& board, eHorseRanch* const hr);

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
    std::vector<eOverlay> getOverlays(const eTileSize size) const;

    int horseCount() const { return mHorses.size(); }

    bool spawnHorse();
    bool takeHorse();
private:
    std::vector<stdsptr<eHorse>> mHorses;

    eHorseRanch* const mRanch;
};

#endif // EHORSERANCHENCLOSURE_H
