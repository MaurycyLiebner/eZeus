#ifndef EMOUSEEVENT_H
#define EMOUSEEVENT_H

enum class eMouseButton {
    none = 0,
    left = 1,
    middle = 2,
    right = 4
};

inline eMouseButton operator|(const eMouseButton a, const eMouseButton b) {
    return static_cast<eMouseButton>(static_cast<int>(a) | static_cast<int>(b));
}

inline eMouseButton operator&(const eMouseButton a, const eMouseButton b) {
    return static_cast<eMouseButton>(static_cast<int>(a) & static_cast<int>(b));
}

class eMouseEvent {
public:
    eMouseEvent(const int x, const int y,
                const eMouseButton buttons,
                const eMouseButton button = eMouseButton::none);

    eMouseEvent translated(const int x, const int y) const;
    eMouseEvent withPosition(const int x, const int y) const;
    int x() const { return mX; }
    int y() const { return mY; }
    eMouseButton button() const { return mButton; }
    eMouseButton buttons() const { return mButtons; }
private:
    int mX;
    int mY;

    eMouseButton mButtons;
    eMouseButton mButton;
};

#endif // EMOUSEEVENT_H
