#ifndef ETRAILER_H
#define ETRAILER_H

#include "echaracter.h"
#include "etransporterbase.h"

class eTrailer : public eCharacter {
public:
    eTrailer(eTransporterBase* const follow,
             eGameBoard& board);

    std::shared_ptr<eTexture>
        getTexture(const eTileSize size) const;

    void setBig(const bool b) { mIsBig = b; }
private:
    const stdptr<eTransporterBase> mFollow;

    bool mIsBig = false;
};

#endif // ETRAILER_H
