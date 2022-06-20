#ifndef EOILVENDOR_H
#define EOILVENDOR_H

#include "evendor.h"

class eOilVendor : public eVendor {
public:
    eOilVendor(const stdsptr<eCommonAgora>& agora,
               eGameBoard& board);
};

#endif // EOILVENDOR_H
