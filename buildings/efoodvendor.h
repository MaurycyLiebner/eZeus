#ifndef EFOODVENDOR_H
#define EFOODVENDOR_H

#include "evendor.h"

class eFoodVendor : public eVendor {
public:
    eFoodVendor(const stdsptr<eAgoraBase>& agora,
                eGameBoard& board);
};

#endif // EFOODVENDOR_H
