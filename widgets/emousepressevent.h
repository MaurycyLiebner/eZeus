#ifndef EMOUSEPRESSEVENT_H
#define EMOUSEPRESSEVENT_H

enum class eMouseButton {
    none, left, middle, right
};

class eMouseEvent {
public:
    eMouseEvent();

    eMouseEvent translated(const int x, const int y) const;
    int x() const { return mX; }
    int y() const { return mY; }
    eMouseButton button() const { return mButton; }
private:
    eMouseButton mButton;
    int mX;
    int mY;
};

#endif // EMOUSEPRESSEVENT_H
