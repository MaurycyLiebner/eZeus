#ifndef EPEDDLER_H
#define EPEDDLER_H

#include "ebasicpatroler.h"

class eAgoraBase;

class ePeddler : public eBasicPatroler {
public:
    ePeddler(eGameBoard& board, eAgoraBase* const agora);

    void provideToBuilding(eBuilding* const b);
private:
    const stdptr<eAgoraBase> mAgora;
};

#endif // EPEDDLER_H
