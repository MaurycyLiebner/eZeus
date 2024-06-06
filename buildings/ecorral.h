#ifndef ECORRAL_H
#define ECORRAL_H

#include "eresourcebuildingbase.h"

class eCorral : public eResourceBuildingBase {
public:
    eCorral(eGameBoard& board);

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const override;
    std::vector<eOverlay> getOverlays(const eTileSize size) const override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;

    void timeChanged(const int by) override;

    int cattleCount() const { return mNCattle; }
    void addCattle();
private:
    bool killCattle();

    bool takeCattle();
    void replaceCattle();

    int mProcessing = 0;
    int mNCattle = 0;
    int mTakeWait = 0;
    int mKillWait = 0;
    int mReplaceWait = 0;
};

#endif // ECORRAL_H
