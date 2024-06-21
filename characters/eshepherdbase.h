#ifndef ESHEPHERDBASE_H
#define ESHEPHERDBASE_H

#include "eresourcecollectorbase.h"

#include "textures/echaractertextures.h"

class eShepherdBase : public eResourceCollectorBase {
public:
    using eCharTexs = eShepherdTextures eCharacterTextures::*;
    eShepherdBase(eGameBoard& board, const eCharTexs charTexs,
                  const eCharacterType type);

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
private:
    const std::vector<eCharacterTextures>& mTextures;
    eCharTexs mCharTexs;
};

#endif // ESHEPHERDBASE_H
