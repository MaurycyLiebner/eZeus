#ifndef EGAMEOBJECT_H
#define EGAMEOBJECT_H

class eGameBoard;

class eGameObject {
public:
    eGameObject(const int type, eGameBoard* board);

    int x() const { return mX; }
    int y() const { return mY; }

    void moveTo(const int x, const int y);
    void moveBy(const int dx, const int dy);
private:
    eGameBoard* mBoard;
    int mType;
    int mX;
    int mY;
    int mXSpan;
    int mYSpan;
};

#endif // EGAMEOBJECT_H
