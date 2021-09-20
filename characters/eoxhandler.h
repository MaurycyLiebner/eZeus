#ifndef EOXHANDLER_H
#define EOXHANDLER_H

#include "etransporterbase.h"

class eOx;
class eOxHandler;
class eTrailer;

struct eOxTransporter {
    stdsptr<eOxHandler> fHandler;
    stdsptr<eOx> fOx;
    stdsptr<eTrailer> fTrailer;
};

class eOxHandler : public eTransporterBase {
public:
    eOxHandler(eGameBoard& board);

    static eOxTransporter sCreate(
            eGameBoard& board, eTile* const t);
};

#endif // EOXHANDLER_H
