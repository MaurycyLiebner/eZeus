#ifndef EAGORASPACE_H
#define EAGORASPACE_H

#include "ebuilding.h"

class eCommonAgora;

class eAgoraSpace : public eBuilding {
public:
    eAgoraSpace(const stdsptr<eCommonAgora>& agora, eGameBoard& board);

    stdsptr<eTexture> getTexture(const eTileSize size) const;

    eCommonAgora* agora() const { return mAgora.get(); }
private:
    const stdsptr<eCommonAgora> mAgora;
};

#endif // EAGORASPACE_H
