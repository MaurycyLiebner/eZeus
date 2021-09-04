#ifndef ESTADIUM1_H
#define ESTADIUM1_H

#include "eemployingbuilding.h"
#include "textures/ebuildingtextures.h"
#include "characters/actions/epatrolaction.h"

class eStadium1Base : public eEmployingBuilding {
public:
    eStadium1Base(eGameBoard& board);
    ~eStadium1Base();
};

class eStadium1W : public eStadium1Base {
public:
    using eStadium1Base::eStadium1Base;

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
};

class eStadium1H : public eStadium1Base {
public:
    using eStadium1Base::eStadium1Base;

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
};

#endif // ESTADIUM1_H
