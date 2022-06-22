#ifndef EHORSEVENDOR_H
#define EHORSEVENDOR_H

#include "evendor.h"

class eHorseVendor : public eVendor {
public:
    eHorseVendor(const stdsptr<eAgoraBase>& agora,
                 eGameBoard& board);
};

#endif // EHORSEVENDOR_H
