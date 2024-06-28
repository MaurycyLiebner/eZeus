#include "enumlineedit.h"

eNumLineEdit::eNumLineEdit(eMainWindow* const window) :
    eLineEdit(window) {
    setValue(0);
}

bool eNumLineEdit::keyPressEvent(const eKeyPressEvent& e) {
    const auto k = e.key();
    if(k == SDL_Scancode::SDL_SCANCODE_0 ||
       k == SDL_Scancode::SDL_SCANCODE_1 ||
       k == SDL_Scancode::SDL_SCANCODE_2 ||
       k == SDL_Scancode::SDL_SCANCODE_3 ||
       k == SDL_Scancode::SDL_SCANCODE_4 ||
       k == SDL_Scancode::SDL_SCANCODE_5 ||
       k == SDL_Scancode::SDL_SCANCODE_6 ||
       k == SDL_Scancode::SDL_SCANCODE_7 ||
       k == SDL_Scancode::SDL_SCANCODE_8 ||
       k == SDL_Scancode::SDL_SCANCODE_9 ||
       k == SDL_Scancode::SDL_SCANCODE_BACKSPACE) {
        eLineEdit::keyPressEvent(e);
        setValue(value());
        return true;
    }
    if(k == SDL_Scancode::SDL_SCANCODE_MINUS) {
        setValue(-value());
        return true;
    }
    return false;
}

int eNumLineEdit::value() const {
    const auto str = text();
    if(str == "" || str == "-") return 0;
    return std::stoi(str);
}

int eNumLineEdit::clampedValue() const {
    const int v = std::clamp(value(), mMin, mMax);
    return v;
}

void eNumLineEdit::setValue(const int value) {
    setText(std::to_string(value));
}

void eNumLineEdit::setRange(const int min, const int max) {
    mMin = min;
    mMax = max;
}

void eNumLineEdit::clamp() {
    const int v = clampedValue();
    setText(std::to_string(v));
}

bool eNumLineEdit::mouseWheelEvent(const eMouseWheelEvent& e) {
    setValue(value() + ((e.dy() > 0) ? 1 : -1));
    return true;
}
