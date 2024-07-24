#ifndef ETOWER_H
#define ETOWER_H

#include "eemployingbuilding.h"

#include "characters/earcher.h"

class eTower : public eEmployingBuilding {
public:
    eTower(eGameBoard& board);
    ~eTower();

    std::shared_ptr<eTexture>
    getTexture(const eTileSize size) const override;
    std::vector<eOverlay>
    getOverlays(const eTileSize size) const override;

    void timeChanged(const int by) override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;

    bool spawn();

    void setDeleteArchers(const bool d) { mDeleteArchers = d; }
private:
    bool mDeleteArchers = true;

    int mMissile = 0;
    int mRangeAttack = 0;
    int mAttackTime = 0;
    bool mAttack = false;
    eOrientation mAttackOrientation{eOrientation::topRight};
    stdptr<eCharacter> mAttackTarget;

    int mSpawnTime = 0;

    stdptr<eArcher> mArcher;
};

#endif // ETOWER_H
