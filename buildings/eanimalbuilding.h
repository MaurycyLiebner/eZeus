#ifndef EANIMALBUILDING_H
#define EANIMALBUILDING_H

#include "ebuilding.h"
#include "characters/echaracter.h"

class eAnimalBuilding : public eBuilding {
public:
    eAnimalBuilding(eGameBoard& board,
                    eCharacter* const a,
                    const eBuildingType type);
    ~eAnimalBuilding();

    std::shared_ptr<eTexture> getTexture(
            const eTileSize) const override { return nullptr; };

    void nextMonth() override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;

    eCharacter* animal() const { return mA; }
    void setAnimal(eCharacter* const a);
private:
    stdptr<eCharacter> mA;
};

#endif // EANIMALBUILDING_H
