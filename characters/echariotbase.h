#ifndef ECHARIOTBASE_H
#define ECHARIOTBASE_H

#include "esoldier.h"

class eChariotBase : public eSoldier {
public:
    using eCharTexs = eChariotTextures eCharacterTextures::*;
    eChariotBase(eGameBoard& board,
                 const eCharTexs charTexs,
                 const eCharacterType type);

       std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
   private:
       const eCharTexs mCharTexs;
};

#endif // ECHARIOTBASE_H
