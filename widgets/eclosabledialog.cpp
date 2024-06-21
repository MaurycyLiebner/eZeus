#include "eclosabledialog.h"

bool eClosableDialog::keyPressEvent(const eKeyPressEvent& e) {
    const auto k = e.key();
    if(k == SDL_SCANCODE_ESCAPE) {
        deleteLater();
    }
    return true;
}

bool eClosableDialog::mousePressEvent(const eMouseEvent& e) {
    const auto b = e.button();
    if(b == eMouseButton::right) {
        deleteLater();
    }
    return true;
}
