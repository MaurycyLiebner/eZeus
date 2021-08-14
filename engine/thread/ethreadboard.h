#ifndef ETHREADBOARD_H
#define ETHREADBOARD_H

#include "ethreadtile.h"

class eThreadBoard {
public:
    void initialize(const int x, const int y,
                    const int w, const int h);
    void clear();

    int x() const { return mX; }
    int y() const { return mY; }

    int width() const { return mWidth; }
    int height() const { return mHeight; }

    eThreadTile* relTile(const int x, const int y);
    eThreadTile* absTile(const int x, const int y);
    void updateNeighbours();

    void assign(const eThreadBoard& src);

    bool changed() const { return mChanged; }
    void setChanged(const bool c) { mChanged  = c; }
private:
    bool mChanged = false;

    int mX = 0;
    int mY = 0;
    int mWidth = 0;
    int mHeight = 0;
    std::vector<std::vector<eThreadTile>> mTiles;
};

#endif // ETHREADBOARD_H
