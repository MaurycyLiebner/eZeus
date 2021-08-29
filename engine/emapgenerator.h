#ifndef EMAPGENERATOR_H
#define EMAPGENERATOR_H

#include "egameboard.h"

class eMapGenerator {
public:
    eMapGenerator(eGameBoard& board);

    void generate();
private:
    eGameBoard& mBoard;
};

#endif // EMAPGENERATOR_H
