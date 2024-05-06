#ifndef ETEMPLEMONUMENTBUILDING_H
#define ETEMPLEMONUMENTBUILDING_H


#include "characters/gods/egod.h"

#include "esanctbuilding.h"

class eTempleMonumentBuilding : public eSanctBuilding {
public:
    eTempleMonumentBuilding(const eGodType god,
                            const int id, eGameBoard& board);

    static const eTextureCollection* sGodMonumentTextureCollection(
            const eTileSize size, const eGodType god);

    std::shared_ptr<eTexture>
        getTexture(const eTileSize size) const;

    eGodType godType() const { return mGod; }
    int id() const { return mId; }
private:
    const eGodType mGod;
    const int mId;
};

#endif // ETEMPLEMONUMENTBUILDING_H
