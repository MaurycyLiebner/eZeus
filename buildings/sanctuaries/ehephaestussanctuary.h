#ifndef EHEPHAESTUSSANCTUARY_H
#define EHEPHAESTUSSANCTUARY_H

#include "esanctuary.h"

class eHephaestusSanctuary : public eSanctuary {
public:
    eHephaestusSanctuary(const int sw, const int sh,
                         eGameBoard& board);
};

#endif // EHEPHAESTUSSANCTUARY_H
