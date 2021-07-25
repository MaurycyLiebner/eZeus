#ifndef ETILE_H
#define ETILE_H


class eTile {
public:
    eTile(const int x, const int y);

    int x() const { return mX; }
    int y() const { return mY; }
    int altitude() const { return mAltitude; }
private:
    const int mX;
    const int mY;
    int mAltitude = 0;
};

#endif // ETILE_H
