#include "elabel.h"

eLabel::eLabel(eMainWindow* const window) :
    eWidget(window), eLabelBase(renderer()) {
    setFont(eFonts::defaultFont(resolution()));
}

eLabel::eLabel(const std::string& text,
               eMainWindow* const window) :
    eLabel(window) {
    setText(text);
}

bool eLabel::setSmallFontSize() {
    const int s = eResolution::smallFontSize(resolution());
    return setFontSize(s);
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
    }
}
