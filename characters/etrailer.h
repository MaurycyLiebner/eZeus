#ifndef ETRAILER_H
#define ETRAILER_H

#include "echaracter.h"
#include "ecarttransporter.h"

class eTrailer : public eCharacter {
public:
    eTrailer(eCartTransporter* const follow,
             eGameBoard& board);

    std::shared_ptr<eTexture>
        getTexture(const eTileSize size) const;

    void setBig(const bool b) { mIsBig = b; }
private:
    const stdptr<eCartTransporter> mFollow;

    bool mIsBig = false;
};

#endif // ETRAILER_H
