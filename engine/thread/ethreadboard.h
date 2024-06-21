#ifndef ETHREADBOARD_H
#define ETHREADBOARD_H

#include "ethreadtile.h"

class eThreadBoard {
public:
    void initialize(const int w, const int h);
    void clear();

    int width() const { return mWidth; }
    int height() const { return mHeight; }

    eThreadTile* tile(const int x, const int y);
    eThreadTile* dtile(const int x, const int y);
private:
    void updateNeighbours();

    int mWidth = 0;
    int mHeight = 0;
    std::vector<std::vector<eThreadTile>> mTiles;
};

#endif // ETHREADBOARD_H
