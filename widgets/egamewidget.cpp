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

    const std::string pathBase{"textures/720p/tiles/grass/flat_"};
    for(int i = 1; i < 5; i++) {
        const auto path = pathBase + std::to_string(i) + ".png";
        eTexture tex;
        tex.load(renderer(), path);
        mFlatGrassTexs.push_back(tex);
    }

    {
        const auto path = "textures/720p/tiles/grass/flat_1_bottom_left.png";
        mBottomLeft.load(renderer(), path);
    }
    {
        const auto path = "textures/720p/tiles/grass/flat_1_bottom_right.png";
        mBottomRight.load(renderer(), path);
    }
}

void eGameWidget::paintEvent(ePainter& p) {
    const int tileW = 128;
    const int tileH = 64;
    const auto board = mLoop.requestBoard();
    const int w = board.width();
    const int h = board.height();
    const int nRows = w + h - 1;

    int minRow = -2*(mDY - 100)/tileH;
    int maxRow = minRow + 2*(height() - 200)/tileH;
    minRow = std::clamp(minRow, 0, nRows);
    maxRow = std::clamp(maxRow, 0, nRows);

    const int minXYDiff = 2*(-mDX + 100)/tileW;
    const int maxXYDiff = minXYDiff + 2*(width() - 200)/tileW;

    p.setFont(eFonts::defaultFont(resolution()));
    p.translate(mDX, mDY);
    const auto iniIt = eGameBoardDiagonalIterator(minRow, 0, &board);
    for(auto it = iniIt; it != board.dEnd(); ++it) {
        if(it.row() > maxRow) break;
        const auto tile = *it;
        const int tx = tile->x();
        const int ty = tile->y();
        const int xmy = tx - ty;
        if(xmy < minXYDiff) continue;
        if(xmy > maxXYDiff) continue;
        const int pixX = (tx*tileW - ty*tileW)/2;
        int pixY = (tx*tileH + ty*tileH)/2;
        const int alt = tile->altitude();
        if(alt > 0) {
            for(int i = 0; i < alt; i++) {
                const int y = pixY - i*tileH/2;
                p.drawTexture(pixX - tileW/2, y, mBottomLeft);
                p.drawTexture(pixX, y, mBottomRight);
            }
            pixY -= alt*tileH/2;
        }

        const int texId = (tx + ty) % 4;
        const auto& tex = mFlatGrassTexs[texId];
        p.drawTexture(pixX - tileW/2, pixY, tex);

//        std::vector<SDL_Point> pts;
//        pts.push_back({pixX, pixY});
//        pts.push_back({pixX + tileW/2, pixY + tileH/2});
//        pts.push_back({pixX, pixY + tileH});
//        pts.push_back({pixX - tileW/2, pixY + tileH/2});
//        pts.push_back({pixX, pixY});
//        p.drawPolygon(pts, {0, 0, 0, 255});
//        p.drawText({pixX - tileW/2, pixY, tileW, tileH},
//                   std::to_string(tx) + " " + std::to_string(ty),
//                   {0, 0, 0, 255}, eAlignment::center);
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
