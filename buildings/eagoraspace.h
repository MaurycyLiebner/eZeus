#ifndef EAGORASPACE_H
#define EAGORASPACE_H

#include "ebuilding.h"

class eAgoraBase;

class eAgoraSpace : public eBuilding {
public:
    eAgoraSpace(const stdsptr<eAgoraBase>& agora, eGameBoard& board);

    stdsptr<eTexture> getTexture(const eTileSize size) const;

    eAgoraBase* agora() const { return mAgora.get(); }
private:
    const stdsptr<eAgoraBase> mAgora;
};

#endif // EAGORASPACE_H
