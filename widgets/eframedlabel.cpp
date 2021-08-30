#include "eframedlabel.h"

eFramedLabel::eFramedLabel(eMainWindow* const window) :
    eFramedWidget(window), eLabelBase(renderer()) {
    setFont(eFonts::defaultFont(resolution()));
}

eFramedLabel::eFramedLabel(const std::string& text,
                           eMainWindow* const window) :
    eFramedLabel(window) {
    setText(text);
}

void eFramedLabel::sizeHint2(int& w, int& h) {
    const auto& tex = texture();
    if(tex) {
        w = tex->width();
        h = tex->height();
    } else {
        w = 0;
        h = 0;
    }
}

void eFramedLabel::paintEvent(ePainter& p) {
    eFramedWidget::paintEvent(p);
    const auto& tex = texture();
    if(tex) {
        p.drawTexture(rect(), tex, eAlignment::center);
    }
}
