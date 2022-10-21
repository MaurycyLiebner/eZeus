#ifndef ECOMMONAGORA_H
#define ECOMMONAGORA_H

#include "buildings/eagorabase.h"

class eCommonAgora : public eAgoraBase {
public:
    eCommonAgora(const eAgoraOrientation o, eGameBoard& board);

    SDL_Point pt(const int id) const;

    eAgoraOrientation orientation() const { return mO; }
private:
    const eAgoraOrientation mO;
};

#endif // ECOMMONAGORA_H
