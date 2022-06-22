#ifndef EARMSVENDOR_H
#define EARMSVENDOR_H

#include "evendor.h"

class eArmsVendor : public eVendor {
public:
    eArmsVendor(const stdsptr<eAgoraBase>& agora,
                eGameBoard& board);
};

#endif // EARMSVENDOR_H
