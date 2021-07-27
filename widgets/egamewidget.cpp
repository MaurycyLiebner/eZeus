#include "egamewidget.h"

#include "eterraineditmenu.h"

#include "engine/ebeachtodry.h"
#include "engine/erivertodry.h"
#include "engine/efertiletodry.h"
#include "engine/eforesttodry.h"

eGameWidget::eGameWidget(eMainWindow* const window) :
    eWidget(window),
    mDryTerrainTexs(renderer()),
    mBeachTerrainTexs(renderer()),
    mBeachToDryTerrainTexs(renderer()),
    mRiverTerrainTexs(renderer()),
    mFertileTerrainTexs(renderer()),
    mFertileToDryTerrainTexs(renderer()),
    mScrubTerrainTexs(renderer()),
    mForestToScrubTerrainTexs(renderer()),
    mForestTerrainTexs(renderer()) {
    mLoopThread = std::thread(std::bind(&eGameEventLoop::exec, &mLoop));}

eGameWidget::~eGameWidget() {
    mLoop.quit();
    mLoopThread.join();
}

std::string addZeroes(const std::string& str) {
    std::string result = str;
    while(result.size() < 3) {
        result.insert(0, "0");
    }
    return result;
}

void eGameWidget::initialize(const int w, const int h) {
    const auto tem = new eTerrainEditMenu(window());
    addWidget(tem);
    tem->align(eAlignment::hcenter | eAlignment::bottom);

    mLoop.initialize(w, h);

    const std::string terrDir{"../ZeusTextures/Zeus_Terrain/"};

    {
        const std::string pathBase{terrDir + "Zeus_land1_00"};

        {
            eTextureCollection coll(renderer());
            for(int i = 74; i < 86; i++) {
                const auto iStr = addZeroes(std::to_string(i));
                const auto path = pathBase + iStr + ".png";
                const bool r = coll.loadTexture(path);
                if(!r) std::printf("Failed to load %s\n", path.c_str());
            }
            mForestToDryTerrainTexs.push_back(coll);
        }

        for(int i = 86; i < 106; i++) {
            const auto iStr = addZeroes(std::to_string(i));
            const auto path = pathBase + iStr + ".png";
            const bool r = mForestTerrainTexs.loadTexture(path);
            if(!r) std::printf("Failed to load %s\n", path.c_str());
        }

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
                const auto iStr = addZeroes(std::to_string(i));
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

        {
            eTextureCollection coll(renderer());
            for(int i = 1; i < 13; i++) {
                const auto iStr = addZeroes(std::to_string(i));
                const auto path = pathBase + iStr + ".png";
                const bool r = coll.loadTexture(path);
                if(!r) std::printf("Failed to load %s\n", path.c_str());
            }
            mForestToDryTerrainTexs.push_back(coll);
        }

        for(int i = 13; i < 33; i++) {
            const auto iStr = addZeroes(std::to_string(i));
            const auto path = pathBase + iStr + ".png";
            const bool r = mForestTerrainTexs.loadTexture(path);
            if(!r) std::printf("Failed to load %s\n", path.c_str());
        }

        for(int i = 33; i < 45; i++) {
            const auto iStr = addZeroes(std::to_string(i));
            const auto path = pathBase + iStr + ".png";
            const bool r = mForestToScrubTerrainTexs.loadTexture(path);
            if(!r) std::printf("Failed to load %s\n", path.c_str());
        }

        for(int i = 45; i < 97; i++) {
            const auto iStr = addZeroes(std::to_string(i));
            const auto path = pathBase + iStr + ".png";
            const bool r = mForestTerrainTexs.loadTexture(path);
            if(!r) std::printf("Failed to load %s\n", path.c_str());
        }

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

        for(int i = 121; i < 157;) {
            eTextureCollection coll(renderer());
            for(int j = 0; j < 12; j++, i++) {
                const auto path = pathBase + std::to_string(i) + ".png";
                const bool r = coll.loadTexture(path);
                if(!r) std::printf("Failed to load %s\n", path.c_str());
            }
            mFertileToScrubTerrainTexs.push_back(coll);
        }
    }
}

void eGameWidget::pixToId(const int pixX, const int pixY,
                          int& idX, int& idY) const {
    const double w = mTileW;
    const double h = mTileH;
    idX = std::round((pixX - mDX)/w + (pixY - mDY)/h + 0.5);
    idY = std::round(-(pixX - mDX)/w + (pixY - mDY)/h + 0.5);
}

int gHoverX = -1;
int gHoverY = -1;

void eGameWidget::paintEvent(ePainter& p) {
    const auto board = mLoop.requestBoard();
    const int w = board.width();
    const int h = board.height();
    const int nRows = w + h - 1;

    int minRow = -2*mDY/mTileH + 2;
    int maxRow = minRow + 2*height()/mTileH - 2;
    minRow = std::clamp(minRow, 0, nRows);
    maxRow = std::clamp(maxRow, 0, nRows);

    const int minXYDiff = -2*mDX/mTileW;
    const int maxXYDiff = minXYDiff + 2*width()/mTileW - 1;

    p.setFont(eFonts::defaultFont(resolution()));
    p.translate(mDX, mDY);
    const auto iniIt = eGameBoardDiagonalIterator(minRow, 0, &board);
    for(auto it = iniIt; it != board.dEnd(); ++it) {
        if(it.row() > maxRow) break;
        const auto tile = *it;
        const int tileId = tile->id();
        const int tx = tile->x();
        const int ty = tile->y();
        const int xmy = tx - ty;
        if(xmy < minXYDiff) continue;
        if(xmy > maxXYDiff) continue;
        const int pixX = (tx*mTileW - ty*mTileW)/2 - mTileW/2;
        int pixY = (tx*mTileH + ty*mTileH)/2;
        const int alt = tile->altitude();
        if(alt > 0) {
            pixY -= alt*mTileH/2;
        }

        switch(tile->terrain()) {
        case eTerrain::dry: {
            const int scrub = tile->scrubId(13) - 1;
            if(scrub == -1) { // zero scrub
                const int texId = tileId % mDryTerrainTexs.size();
                mDryTerrainTexs.draw(p, pixX, pixY, texId, eAlignment::top);
            } else if(scrub == 13) { // full scrub
                const int texId = tileId % mScrubTerrainTexs.size();
                mScrubTerrainTexs.draw(p, pixX, pixY, texId, eAlignment::top);
            } else { // partial scrub
                const int collId = tileId % mDryToScrubTerrainTexs.size();
                const auto& coll = mDryToScrubTerrainTexs[collId];
                coll.draw(p, pixX, pixY, scrub, eAlignment::top);
            }
        } break;
        case eTerrain::beach: {
            const auto id = eBeachToDry::get(tile);
            if(id == eBeachToDryId::none) {
                const int texId = tileId % mBeachTerrainTexs.size();
                mBeachTerrainTexs.draw(p, pixX, pixY, texId, eAlignment::top);
            } else {
                const int texId = static_cast<int>(id);
                mBeachToDryTerrainTexs.draw(p, pixX, pixY, texId, eAlignment::top);
            }
        } break;
        case eTerrain::river: {
            const auto id = eRiverToDry::get(tile);
            if(id == eRiverToDryId::none) {
                const int texId = tileId % mRiverTerrainTexs.size();
                mRiverTerrainTexs.draw(p, pixX, pixY, texId, eAlignment::top);
            } else {
                const int collId = static_cast<int>(id);
                const auto& texs = mRiverToDryTerrainTexs[collId];
                const int texId = tileId % texs.size();
                texs.draw(p, pixX, pixY, texId, eAlignment::top);
            }
        } break;
        case eTerrain::fertile: {
            const auto id = eFertileToDry::get(tile);
            const int scrub = tile->scrubId(13) - 1;
            switch(id) {
            case eFertileToDryId::none: {
                if(scrub == -1) {
                    const int texId = tileId % mFertileTerrainTexs.size();
                    mFertileTerrainTexs.draw(p, pixX, pixY, texId, eAlignment::top);
                } else {
                    const auto& coll = mFertileToScrubTerrainTexs[2];
                    coll.draw(p, pixX, pixY, scrub, eAlignment::top);
                }
            } break;
            case eFertileToDryId::somewhere: {
                if(scrub == -1) {
                    const int texId = tileId % mFertileToDryTerrainTexs.size();
                    mFertileToDryTerrainTexs.draw(p, pixX, pixY, texId, eAlignment::top);
                } else {
                    const int collId = rand() % 2;
                    const auto& coll = mFertileToScrubTerrainTexs[collId];
                    coll.draw(p, pixX, pixY, scrub, eAlignment::top);
                }
            } break;
            }
        } break;
        case eTerrain::forest: {
            const auto id = eForestToDry::get(tile);
            switch(id) {
            case eForestToDryId::none: {
                const int texId = tileId % mForestTerrainTexs.size();
                mForestTerrainTexs.draw(p, pixX, pixY, texId, eAlignment::top);
            } break;
            case eForestToDryId::somewhere: {
                const int scrub = tile->scrubId(13) - 1;
                if(scrub == -1) {
                    const int collId = tileId % mForestToDryTerrainTexs.size();
                    const auto& coll = mForestToDryTerrainTexs[collId];
                    const int texId = tileId % coll.size();
                    coll.draw(p, pixX, pixY, texId, eAlignment::top);
                } else {
                    mForestToScrubTerrainTexs.draw(p, pixX, pixY, scrub, eAlignment::top);
                }
            } break;
            }
        } break;
        }


        if(tile->x() == gHoverX && tile->y() == gHoverY) {
            std::vector<SDL_Point> pts;
            pts.push_back({pixX + mTileW/2, pixY - mTileH});
            pts.push_back({pixX + mTileW, pixY - mTileH/2});
            pts.push_back({pixX + mTileW/2, pixY});
            pts.push_back({pixX, pixY - mTileH/2});
            pts.push_back({pixX + mTileW/2, pixY - mTileH});
            p.drawPolygon(pts, {0, 0, 0, 255});
    //        p.drawText({pixX - tileW/2, pixY, tileW, tileH},
    //                   std::to_string(tx) + " " + std::to_string(ty),
    //                   {0, 0, 0, 255}, eAlignment::center);
        }
    }
}

int gLastX = 0;
int gLastY = 0;

bool eGameWidget::mousePressEvent(const eMouseEvent& e) {
    switch(e.button()) {
    case eMouseButton::middle:
        gLastX = e.x();
        gLastY = e.y();
        return true;
    default: return false;
    }
}

bool eGameWidget::mouseMoveEvent(const eMouseEvent& e) {
    if(static_cast<bool>(e.buttons() & eMouseButton::middle)) {
        const int dx = e.x() - gLastX;
        const int dy = e.y() - gLastY;
        mDX += dx;
        mDY += dy;
        gLastX = e.x();
        gLastY = e.y();
        return true;
    } else {
        pixToId(e.x(), e.y(), gHoverX, gHoverY);
        return true;
    }
    return false;
}
