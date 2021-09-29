#ifndef ESANCTUARY_H
#define ESANCTUARY_H

#include "../eemployingbuilding.h"

#include "esanctuaryblueprint.h"

class eBuildingTextures;

class eSanctuary : public eEmployingBuilding {
public:
    using eTexCollPtr = eTextureCollection eBuildingTextures::*;
    eSanctuary(const eTexCollPtr statues,
               const eTexCollPtr monuments,
               eGameBoard& board,
               const eBuildingType type,
               const int sw, const int sh,
               const int maxEmployees);

    std::shared_ptr<eTexture>
    getTexture(const eTileSize) const
    { return nullptr; }

    eTexCollPtr statues() const { return mStatues; }
    eTexCollPtr monuments() const { return mMonuments; }
private:
    const eTexCollPtr mStatues;
    const eTexCollPtr mMonuments;
};

#endif // ESANCTUARY_H
