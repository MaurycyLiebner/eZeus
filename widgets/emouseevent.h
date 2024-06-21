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

inline eMouseButton operator~(const eMouseButton a) {
    return static_cast<eMouseButton>(~static_cast<int>(a));
}

class eMouseEvent {
public:
    eMouseEvent(const int x, const int y,
                const bool shift,
                const eMouseButton buttons,
                const eMouseButton button = eMouseButton::none);

    eMouseEvent translated(const int x, const int y) const;
    eMouseEvent withPosition(const int x, const int y) const;
    int x() const { return mX; }
    int y() const { return mY; }
    eMouseButton button() const { return mButton; }
    eMouseButton buttons() const { return mButtons; }

    bool shiftPressed() const { return mShift; }
protected:
    int mX;
    int mY;

    bool mShift;

    eMouseButton mButtons;
    eMouseButton mButton;
};

#include <SDL2/SDL_scancode.h>

class eMouseWheelEvent : public eMouseEvent {
public:
    eMouseWheelEvent(const int x, const int y,
                     const bool shift,
                     const eMouseButton buttons,
                     const int dy);

    eMouseWheelEvent translated(const int x, const int y) const;
    eMouseWheelEvent withPosition(const int x, const int y) const;

    int dy() const { return mDY; }
private:
    int mDY;
};

class eKeyPressEvent : public eMouseEvent {
public:
    eKeyPressEvent(const int x, const int y,
                   const bool shift,
                   const eMouseButton buttons,
                   const SDL_Scancode key);

    eKeyPressEvent translated(const int x, const int y) const;
    eKeyPressEvent withPosition(const int x, const int y) const;

    SDL_Scancode key() const { return mKey; }
private:
    SDL_Scancode mKey;
};

#endif // EMOUSEEVENT_H
