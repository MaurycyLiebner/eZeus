#ifndef ETILE_H
#define ETILE_H

enum class eTerrain {
    dry, beach
};

enum class eSurroundings {
    bottomLeft,
    left,
    topLeft,
    top,
    topRight,
    right,
    bottomRight,
    bottom,
    topLeftAndBottomLeft,
    topLeftAndTopRight,
    topRightAndBottomRight,
    bottomLeftAndBottomRight,
    end
};

struct eTypedSurroundings {
    eTerrain fTerr;
    eSurroundings fSurr;
};

class eTile {
public:
    eTile(const int x, const int y);
    int id() const { return mId; }
    int x() const { return mX; }
    int y() const { return mY; }
    int altitude() const { return mAltitude; }
    eTerrain terrain() const { return mTerr; }

    eTile* topLeft() const { return mTopLeft; }
    eTile* topRight() const { return mTopRight; }
    eTile* bottomRight() const { return mBottomRight; }
    eTile* bottomLeft() const { return mBottomLeft; }

    eTile* left() const;
    eTile* top() const;
    eTile* right() const;
    eTile* bottom() const;

    void setTerrain(const eTerrain& terr);

    void setTopLeft(eTile* const tl);
    void setTopRight(eTile* const tr);
    void setBottomRight(eTile* const br);
    void setBottomLeft(eTile* const bl);

    eTypedSurroundings surroundings() const;
private:
    const int mId;
    const int mX;
    const int mY;

    eTile* mTopLeft = nullptr;
    eTile* mTopRight = nullptr;
    eTile* mBottomRight = nullptr;
    eTile* mBottomLeft = nullptr;

    eTerrain mTerr = eTerrain::dry;
    int mAltitude = 0;
};

#endif // ETILE_H
