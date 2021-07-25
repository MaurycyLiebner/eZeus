#include "egamewidget.h"

eGameWidget::eGameWidget(eMainWindow* const window) :
    eWidget(window) {
    mLoopThread = std::thread(std::bind(&eGameEventLoop::exec, &mLoop));
}

eGameWidget::~eGameWidget() {
    mLoop.quit();
    mLoopThread.join();
}

void eGameWidget::initialize(const int w, const int h) {
    mLoop.initialize(w, h);
}

void eGameWidget::paintEvent(ePainter& p) {
    const int tileW = 100;
    const int tileH = 50;
    const auto board = mLoop.requestBoard();
//    const int w = board.width();
//    const int h = board.height();
//    const int pixW = tileW*(w + h)/2;
    p.setFont(eFonts::defaultFont(resolution()));
    p.translate(mDX + width()/2, mDY);
    for(auto it = board.dBegin(); it != board.dEnd(); ++it) {
        const auto tile = *it;
        std::vector<SDL_Point> pts;
        const int tx = tile->x();
        const int ty = tile->y();
        const int pixX = (tx*tileW - ty*tileW)/2;
        const int pixY = (tx*tileH + ty*tileH)/2;
        pts.push_back({pixX, pixY});
        pts.push_back({pixX + tileW/2, pixY + tileH/2});
        pts.push_back({pixX, pixY + tileH});
        pts.push_back({pixX - tileW/2, pixY + tileH/2});
        pts.push_back({pixX, pixY});
        p.drawPolygon(pts, {0, 0, 0, 255});
        p.drawText({pixX - tileW/2, pixY, tileW, tileH},
                   std::to_string(tx) + " " + std::to_string(ty),
                   {0, 0, 0, 255}, eAlignment::center);
    }
}

int gLastX = 0;
int gLastY = 0;

bool eGameWidget::mousePressEvent(const eMouseEvent& e) {
    switch(e.button()) {
    case eMouseButton::left:
        gLastX = e.x();
        gLastY = e.y();
        return true;
    default: return false;
    }
}

bool eGameWidget::mouseMoveEvent(const eMouseEvent& e) {
    if(static_cast<bool>(e.buttons() & eMouseButton::left)) {
        const int dx = e.x() - gLastX;
        const int dy = e.y() - gLastY;
        mDX += dx;
        mDY += dy;
        gLastX = e.x();
        gLastY = e.y();
        return true;
    }
    return false;
}
