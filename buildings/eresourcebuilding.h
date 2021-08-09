#ifndef ERESOURCEBUILDING_H
#define ERESOURCEBUILDING_H

#include "ebuilding.h"

enum class eResourceType {
    oliveTree,
    vine,
    wheat,
    carrots,
    onions
};

class eResourceBuilding : public eBuilding {
public:
    eResourceBuilding(eGameBoard& board,
                      const eResourceType type);

    eTexture getTexture(const eTileSize size) const;

    eResourceType type() const { return mType; }

    bool fullyRipe() const { return mRipe == 5; }
    int ripe() const { return mRipe; }
    int resource() const { return mResource; }
    void takeResource(const int by);
    void timeChanged();
private:
    const eResourceType mType;
    int mNextRipe = 0;
    int mRipe = 0; // 0 - 5
    int mResource = 0;
};

#endif // ERESOURCEBUILDING_H
