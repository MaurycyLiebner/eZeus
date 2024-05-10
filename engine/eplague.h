#ifndef EPLAGUE_H
#define EPLAGUE_H

#include <vector>

#include "pointers/estdselfref.h"

class eGameBoard;
class eSmallHouse;

class eReadStream;
class eWriteStream;

class ePlague {
public:
    ePlague(eGameBoard& board);

    void randomSpread();
    void spreadFrom(eSmallHouse* const h);
    void healAll();
    void healHouse(eSmallHouse* const h);
    bool hasHouse(eSmallHouse* const h) const;
    void removeHouse(eSmallHouse* const h);
    int houseCount() const { return mHouses.size(); }

    void read(eReadStream& src);
    void write(eWriteStream& dst) const;
private:
    eGameBoard& mBoard;
    std::vector<eSmallHouse*> mHouses;
};

#endif // EPLAGUE_H
