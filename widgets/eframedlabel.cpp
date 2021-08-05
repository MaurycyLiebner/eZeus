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
    if(tex.isNull()) {
        w = 0;
        h = 0;
    } else {
        w = tex.width();
        h = tex.height();
    }
}

void eFramedLabel::paintEvent(ePainter& p) {
    eFramedWidget::paintEvent(p);
    const auto& tex = texture();
    if(!tex.isNull()) {
        p.drawTexture(rect(), tex, eAlignment::center);
    }
}
