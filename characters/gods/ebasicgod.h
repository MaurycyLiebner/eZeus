#ifndef EBASICGOD_H
#define EBASICGOD_H

#include "egod.h"

#include "textures/egodtextures.h"

class eBasicGod : public eGod {
public:
    using eGodTexs = eBasicGodTextures eGodTextures::*;
    eBasicGod(eGameBoard& board,
              const eGodTexs godTexs,
              const eGodType gt);

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
private:
    const eGodTexs mGodTexs;
};

#endif // EBASICGOD_H
