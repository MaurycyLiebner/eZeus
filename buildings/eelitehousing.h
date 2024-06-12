#ifndef EELITEHOUSING_H
#define EELITEHOUSING_H

#include "ehousebase.h"

class eEliteHousing : public eHouseBase {
public:
    eEliteHousing(eGameBoard& board);

    std::shared_ptr<eTexture>
    getTexture(const eTileSize) const override { return nullptr; }

    eTextureSpace
    getTextureSpace(const int tx, const int ty,
                    const eTileSize size) const override;

    std::vector<eOverlay>
    getOverlays(const eTileSize size) const override;

    std::shared_ptr<eTexture>
        getLeftTexture(const eTileSize size) const;
    std::shared_ptr<eTexture>
        getBottomTexture(const eTileSize size) const;
    std::shared_ptr<eTexture>
        getTopTexture(const eTileSize size) const;
    std::shared_ptr<eTexture>
        getRightTexture(const eTileSize size) const;
    std::vector<eOverlay>
        getHorseOverlays(const eTileSize size) const;

    int provide(const eProvide p, const int n) override;

    void timeChanged(const int by) override;

    void nextMonth() override;

    int wine() const { return mWine; }
    int arms() const { return mArms; }

    int horses() const { return mHorses; }

    bool lowFood() const;
    bool lowFleece() const { return mFleece < 2; }
    bool lowOil() const { return mOil < 2; }
    bool lowWine() const { return mWine < 2; }
    bool lowArms() const { return !mArms; }
    bool lowHorses() const { return !mHorses; }

    void removeArmor();
    void removeHorse();

    eHouseMissing missing() const override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;

    static std::string sName(const int level);
private:
    const eTextureCollection& getTextureCollection(
            const eTileSize size) const;

    void updateLevel();

    int mUpdateLevel = 0;

    int mWine = 0;
    int mArms = 0;
    int mHorses = 0;
};

#endif // EELITEHOUSING_H
