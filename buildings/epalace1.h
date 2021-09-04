#ifndef EPALACE1_H
#define EPALACE1_H

#include "ebuilding.h"
#include "textures/ebuildingtextures.h"
#include "characters/actions/epatrolaction.h"

class ePalace1Base : public eBuilding {
public:
    ePalace1Base(eGameBoard& board);
    ~ePalace1Base();
};

class ePalace1W : public ePalace1Base {
public:
    using ePalace1Base::ePalace1Base;

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
};

class ePalace1H : public ePalace1Base {
public:
    using ePalace1Base::ePalace1Base;

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
};

#endif // EPALACE1_H
