#ifndef EFLEECEVENDOR_H
#define EFLEECEVENDOR_H

#include "evendor.h"

class eFleeceVendor : public eVendor {
public:
    eFleeceVendor(const stdsptr<eAgoraBase>& agora,
                  eGameBoard& board);
};

#endif // EFLEECEVENDOR_H
