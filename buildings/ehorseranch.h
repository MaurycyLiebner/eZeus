#ifndef EHORSERANCH_H
#define EHORSERANCH_H

#include "eemployingbuilding.h"

class eHorseRanchEnclosure;

class eHorseRanch : public eEmployingBuilding {
public:
    eHorseRanch(eGameBoard& board);
    ~eHorseRanch();

    void erase();

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
    std::vector<eOverlay> getOverlays(const eTileSize size) const;

    void timeChanged(const int by);

    int add(const eResourceType type, const int count);
    int take(const eResourceType type, const int count);

    int count(const eResourceType type) const;
    int spaceLeft(const eResourceType type) const;

    std::vector<eCartTask> cartTasks() const;

    eHorseRanchEnclosure* enclosure() const { return mEnclosure; }
    void setEnclosure(eHorseRanchEnclosure* const e);

    int horseCount() const;
    bool takeHorse();
private:
    int mWheat = 0;
    int mWheatTime = 0;
    int mHorseTime = 0;
    eHorseRanchEnclosure* mEnclosure = nullptr;

    stdsptr<eCartTransporter> mTakeCart;
};

#endif // EHORSERANCH_H
