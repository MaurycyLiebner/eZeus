#ifndef EWINEVENDOR_H
#define EWINEVENDOR_H

#include "evendor.h"

class eWineVendor : public eVendor {
public:
    eWineVendor(const stdsptr<eCommonAgora>& agora,
                eGameBoard& board);
};

#endif // EWINEVENDOR_H
