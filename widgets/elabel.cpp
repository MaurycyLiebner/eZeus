#include "elabel.h"

eLabel::eLabel(eMainWindow* const window) :
    eWidget(window), eLabelBase(window) {
    setFont(eFonts::defaultFont(resolution()));
}

eLabel::eLabel(const std::string& text,
               eMainWindow* const window) :
    eLabel(window) {
    setText(text);
}

void eLabel::sizeHint(int& w, int& h) {
    const auto& tex = texture();
    if(tex) {
        w = tex->width();
        h = tex->height();
    } else {
        w = 0;
        h = 0;
    }
}

void eLabel::paintEvent(ePainter& p) {
    const auto& tex = texture();
    if(tex) {
        p.drawTexture(rect(), tex, eAlignment::center);
        p.drawRect(rect(), {0, 0, 0, 255}, 1);
    }
}
