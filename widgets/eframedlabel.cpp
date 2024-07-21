#include "eframedlabel.h"

eFramedLabel::eFramedLabel(eMainWindow* const window) :
    eFramedWidget(window), eLabelBase(window) {
    setFont(eFonts::defaultFont(resolution()));
}

eFramedLabel::eFramedLabel(const std::string& text,
                           eMainWindow* const window) :
    eFramedLabel(window) {
    setText(text);
}

void eFramedLabel::renderTargetsReset() {
    eWidget::renderTargetsReset();
    updateTexture();
}

void eFramedLabel::sizeHint(int& w, int& h) {
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
        p.drawTexture(rect(), tex, textAlignment());
    }
}
