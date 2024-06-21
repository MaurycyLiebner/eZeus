#ifndef EHORSERANCH_H
#define EHORSERANCH_H

#include "eemployingbuilding.h"

class eHorseRanchEnclosure;

class eHorseRanch : public eEmployingBuilding {
public:
    eHorseRanch(eGameBoard& board);
    ~eHorseRanch();

    void erase() override;

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const override;
    std::vector<eOverlay> getOverlays(const eTileSize size) const override;

    void timeChanged(const int by) override;

    int add(const eResourceType type, const int count) override;
    int take(const eResourceType type, const int count) override;

    int count(const eResourceType type) const override;
    int spaceLeft(const eResourceType type) const override;

    std::vector<eCartTask> cartTasks() const override;

    int wheat() const { return mWheat; }

    eHorseRanchEnclosure* enclosure() const { return mEnclosure; }
    void setEnclosure(eHorseRanchEnclosure* const e);

    int horseCount() const;
    bool takeHorse();

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
private:
    int mWheat = 0;
    int mWheatTime = 0;
    int mHorseTime = 0;
    eHorseRanchEnclosure* mEnclosure = nullptr;

    stdptr<eCartTransporter> mTakeCart;
};

#endif // EHORSERANCH_H
