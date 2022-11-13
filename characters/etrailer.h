#ifndef ETRAILER_H
#define ETRAILER_H

#include "echaracter.h"
#include "ecarttransporter.h"

class eTrailer : public eCharacter {
public:
    eTrailer(eGameBoard& board);

    std::shared_ptr<eTexture>
        getTexture(const eTileSize size) const;

    void setFollow(eCartTransporter* const c) { mFollow = c; }

    void setBig(const bool b) { mIsBig = b; }
private:
    stdptr<eCartTransporter> mFollow;

    bool mIsBig = false;

    mutable int mResCount = 0;
    mutable eResourceType mResType = eResourceType::marble;
};

#endif // ETRAILER_H
