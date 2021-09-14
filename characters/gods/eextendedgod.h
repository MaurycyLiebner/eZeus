#ifndef EEXTENDEDGOD_H
#define EEXTENDEDGOD_H

#include "egod.h"

#include "textures/egodtextures.h"

class eExtendedGod : public eGod {
public:
    using eGodTexs = eExtendedGodTextures eGodTextures::*;
    eExtendedGod(eGameBoard& board,
                 const eGodTexs godTexs,
                 const eGodType gt);

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
private:
    const eGodTexs mGodTexs;
};

#endif // EEXTENDEDGOD_H
