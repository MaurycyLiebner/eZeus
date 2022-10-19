#ifndef EGODMISSILE_H
#define EGODMISSILE_H

#include "emissile.h"
#include "textures/egametextures.h"

class eGodMissile : public eMissile {
public:
    using eMissile::eMissile;

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;

    using eTexPtr = eTextureCollection eDestructionTextures::*;
    void setTexture(const eTexPtr tex);
private:
    eTexPtr mTex;
};

#endif // EGODMISSILE_H
