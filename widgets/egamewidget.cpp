#include "egamewidget.h"

#include "engine/ebeachtodry.h"
#include "engine/erivertodry.h"
#include "engine/efertiletodry.h"

eGameWidget::eGameWidget(eMainWindow* const window) :
    eWidget(window),
    mDryTerrainTexs(renderer()),
    mBeachTerrainTexs(renderer()),
    mBeachToDryTerrainTexs(renderer()),
    mRiverTerrainTexs(renderer()),
    mFertileTerrainTexs(renderer()),
    mFertileToDryTerrainTexs(renderer()),
    mScrubTerrainTexs(renderer()) {
    mLoopThread = std::thread(std::bind(&eGameEventLoop::exec, &mLoop));
}

eGameWidget::~eGameWidget() {
    mLoop.quit();
    mLoopThread.join();
}

void eGameWidget::initialize(const int w, const int h) {
    mLoop.initialize(w, h);

    const std::string terrDir{"../ZeusTextures/Zeus_Terrain/"};

    {
        const std::string pathBase{terrDir + "Zeus_land1_00"};
        for(int i = 106; i < 164; i++) {
            const auto path = pathBase + std::to_string(i) + ".png";
            const bool r = mDryTerrainTexs.loadTexture(path);
            if(!r) std::printf("Failed to load %s\n", path.c_str());
        }

        for(int i = 164; i < 172; i++) {
            const auto path = pathBase + std::to_string(i) + ".png";
            const bool r = mRiverTerrainTexs.loadTexture(path);
            if(!r) std::printf("Failed to load %s\n", path.c_str());
        }

        {
            for(int i = 172; i < 204;) {
                eTextureCollection coll(renderer());
                for(int j = 0; j < 4; j++, i++) {
                    const auto path = pathBase + std::to_string(i) + ".png";
                    const bool r = coll.loadTexture(path);
                    if(!r) std::printf("Failed to load %s\n", path.c_str());
                }
                mRiverToDryTerrainTexs.push_back(coll);
            }

            for(int i = 204; i < 208;) {
                eTextureCollection coll(renderer());
                for(int j = 0; j < 2; j++, i++) {
                    const auto path = pathBase + std::to_string(i) + ".png";
                    const bool r = coll.loadTexture(path);
                    if(!r) std::printf("Failed to load %s\n", path.c_str());
                }
                mRiverToDryTerrainTexs.push_back(coll);
            }

            for(int i = 208; i < 244; i++) {
                eTextureCollection coll(renderer());
                const auto path = pathBase + std::to_string(i) + ".png";
                const bool r = coll.loadTexture(path);
                if(!r) std::printf("Failed to load %s\n", path.c_str());
                mRiverToDryTerrainTexs.push_back(coll);
            }
        }

        for(int i = 2; i < 38;) {
            eTextureCollection coll(renderer());
            for(int j = 0; j < 12; j++, i++) {
                auto iStr = std::to_string(i);
                while(iStr.size() < 3) {
                    iStr.insert(iStr.begin(), '0');
                }
                const auto path = pathBase + iStr + ".png";
                const bool r = coll.loadTexture(path);
                if(!r) std::printf("Failed to load %s\n", path.c_str());
            }
            mDryToScrubTerrainTexs.push_back(coll);
        }

        for(int i = 38; i < 50; i++) {
            const auto iStr = "0" + std::to_string(i);
            const auto path = pathBase + iStr + ".png";
            const bool r = mScrubTerrainTexs.loadTexture(path);
            if(!r) std::printf("Failed to load %s\n", path.c_str());
        }

        for(int i = 62; i < 74; i++) {
            const auto iStr = "0" + std::to_string(i);
            const auto path = pathBase + iStr + ".png";
            const bool r = mScrubTerrainTexs.loadTexture(path);
            if(!r) std::printf("Failed to load %s\n", path.c_str());
        }
    }

    {
        const std::string pathBase{terrDir + "Zeus_Land3_00"};

        for(int i = 189; i < 195; i++) {
            const auto path = pathBase + std::to_string(i) + ".png";
            const bool r = mBeachTerrainTexs.loadTexture(path);
            if(!r) std::printf("Failed to load %s\n", path.c_str());
        }

        for(int i = 195; i < 207; i++) {
            const auto path = pathBase + std::to_string(i) + ".png";
            const bool r = mBeachToDryTerrainTexs.loadTexture(path);
            if(!r) std::printf("Failed to load %s\n", path.c_str());
        }
    }

    {
        const std::string pathBase{terrDir + "Zeus_Trees_00"};

        for(int i = 157; i < 165; i++) {
            const auto path = pathBase + std::to_string(i) + ".png";
            const bool r = mFertileTerrainTexs.loadTexture(path);
            if(!r) std::printf("Failed to load %s\n", path.c_str());
        }
        for(int i = 173; i < 181; i++) {
            const auto path = pathBase + std::to_string(i) + ".png";
            const bool r = mFertileToDryTerrainTexs.loadTexture(path);
            if(!r) std::printf("Failed to load %s\n", path.c_str());
        }
    }
}

void eGameWidget::paintEvent(ePainter& p) {
    const int tileW = 58;
    const int tileH = 30;
    const auto board = mLoop.requestBoard();
    const int w = board.width();
    const int h = board.height();
    const int nRows = w + h - 1;

    int minRow = -2*mDY/tileH;
    int maxRow = minRow + 2*height()/tileH - 2;
    minRow = std::clamp(minRow, 0, nRows);
    maxRow = std::clamp(maxRow, 0, nRows);

    const int minXYDiff = -2*mDX/tileW;
    const int maxXYDiff = minXYDiff + 2*width()/tileW - 1;

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
        const int pixX = (tx*tileW - ty*tileW)/2 - tileW/2;
        int pixY = (tx*tileH + ty*tileH)/2;
        const int alt = tile->altitude();
        if(alt > 0) {
            pixY -= alt*tileH/2;
        }

        switch(tile->terrain()) {
        case eTerrain::dry: {
            const int scrub = tile->scrubId(13) - 1;
            if(scrub == -1) { // zero scrub
                const int texId = tile->id() % mDryTerrainTexs.size();
                mDryTerrainTexs.draw(p, pixX, pixY, texId);
            } else if(scrub == 13) { // full scrub
                const int texId = tile->id() % mScrubTerrainTexs.size();
                mScrubTerrainTexs.draw(p, pixX, pixY, texId);
            } else { // partial scrub
                const int collId = tile->id() % mDryToScrubTerrainTexs.size();
                const auto& coll = mDryToScrubTerrainTexs[collId];
                coll.draw(p, pixX, pixY, scrub);
            }
        } break;
        case eTerrain::beach: {
            const auto id = eBeachToDry::get(tile);
            if(id == eBeachToDryId::none) {
                const int texId = tile->id() % mBeachTerrainTexs.size();
                mBeachTerrainTexs.draw(p, pixX, pixY, texId);
            } else {
                const int texId = static_cast<int>(id);
                mBeachToDryTerrainTexs.draw(p, pixX, pixY, texId);
            }
        } break;
        case eTerrain::river: {
            const auto id = eRiverToDry::get(tile);
            if(id == eRiverToDryId::none) {
                const int texId = tile->id() % mRiverTerrainTexs.size();
                mRiverTerrainTexs.draw(p, pixX, pixY, texId);
            } else {
                const int collId = static_cast<int>(id);
                const auto& texs = mRiverToDryTerrainTexs[collId];
                const int texId = tile->id() % texs.size();
                texs.draw(p, pixX, pixY, texId);
            }
        } break;
        case eTerrain::fertile: {
            const auto id = eFertileToDry::get(tile);
            switch(id) {
            case eFertileToDryId::none: {
                const int texId = tile->id() % mFertileTerrainTexs.size();
                mFertileTerrainTexs.draw(p, pixX, pixY, texId);
            } break;
            case eFertileToDryId::somewhere: {
                const int texId = tile->id() % mFertileToDryTerrainTexs.size();
                mFertileToDryTerrainTexs.draw(p, pixX, pixY, texId);
            } break;
            }
        } break;
        }



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
