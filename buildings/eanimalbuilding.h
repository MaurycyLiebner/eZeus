#ifndef EANIMALBUILDING_H
#define EANIMALBUILDING_H

#include "ebuilding.h"
#include "characters/edomesticatedanimal.h"

class eAnimalBuilding : public eBuilding {
public:
    eAnimalBuilding(eGameBoard& board,
                    eDomesticatedAnimal* const a,
                    const eBuildingType type);
    ~eAnimalBuilding();

    std::shared_ptr<eTexture> getTexture(
            const eTileSize) const { return nullptr; };

    void nextMonth();
private:
    const stdptr<eDomesticatedAnimal> mA;
};

#endif // EANIMALBUILDING_H
