#ifndef EOBJECT_H
#define EOBJECT_H

#include "estdselfref.h"

class eGameBoard;

class eObject : public eStdSelfRef {
public:
    eObject(eGameBoard& board);

    eGameBoard& getBoard() const { return mBoard; }

    void deleteLater();
private:
    eGameBoard& mBoard;
};

#endif // EOBJECT_H
