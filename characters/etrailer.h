#ifndef ETRAILER_H
#define ETRAILER_H

#include "echaracter.h"

#include "engine/eresourcetype.h"

class eTrailer : public eCharacter {
public:
    eTrailer(eGameBoard& board);

    std::shared_ptr<eTexture>
        getTexture(const eTileSize size) const;

    void setResource(const eResourceType type,
                     const int count);

    void setBig(const bool b) { mIsBig = b; }
private:
    bool mIsBig = false;

    int mResourceCount = 0;
    eResourceType mResourceType = eResourceType::none;
};

#endif // ETRAILER_H
