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
    bool mDeleteLater = false;
};

#endif // EOBJECT_H
