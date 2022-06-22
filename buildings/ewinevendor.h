#ifndef EWINEVENDOR_H
#define EWINEVENDOR_H

#include "evendor.h"

class eWineVendor : public eVendor {
public:
    eWineVendor(const stdsptr<eAgoraBase>& agora,
                eGameBoard& board);
};

#endif // EWINEVENDOR_H
