#ifndef EAGORASPACE_H
#define EAGORASPACE_H

#include "ebuilding.h"

class eAgoraSpace : public eBuilding {
public:
    eAgoraSpace(eGameBoard& board);

    stdsptr<eTexture> getTexture(const eTileSize size) const;
};

#endif // EAGORASPACE_H
