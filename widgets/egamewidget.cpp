#include "egamewidget.h"

#include "eterraineditmenu.h"

#include "engine/ebeachtodry.h"
#include "engine/ewatertodry.h"
#include "engine/efertiletodry.h"
#include "engine/eforesttodry.h"
#include "engine/ewatertobeach.h"
#include "engine/ewatercorner.h"

eGameWidget::eGameWidget(eMainWindow* const window) :
    eWidget(window),
    mDryTerrainTexs(renderer()),
    mBeachTerrainTexs(renderer()),
    mBeachToDryTerrainTexs(renderer()),
    mWaterTerrainTexs(renderer()),
    mFertileTerrainTexs(renderer()),
    mFertileToDryTerrainTexs(renderer()),
    mScrubTerrainTexs(renderer()),
    mForestToScrubTerrainTexs(renderer()),
    mForestTerrainTexs(renderer()),
    mWaterToBeachToDryTerrainTexs(renderer()) {
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

void loadTex(const std::string& pathBase, const int i,
             eTextureCollection& coll) {
    const auto path = pathBase + addZeroes(std::to_string(i)) + ".png";
    const bool r = coll.loadTexture(path);
    if(!r) std::printf("Failed to load %s\n", path.c_str());
}

void eGameWidget::loadWaterToX(int i0, const std::string& pathBase,
                               std::vector<eTextureCollection>& result) const {
    int i = i0;
    for(; i < i0 + 32;) {
        eTextureCollection coll(renderer());
        for(int j = 0; j < 4; j++, i++) {
            loadTex(pathBase, i, coll);
        }
        result.push_back(coll);
    }

    for(; i < i0 + 36;) {
        eTextureCollection coll(renderer());
        for(int j = 0; j < 2; j++, i++) {
            loadTex(pathBase, i, coll);
        }
        result.push_back(coll);
    }

    for(; i < i0 + 72; i++) {
        eTextureCollection coll(renderer());
        loadTex(pathBase, i, coll);
        result.push_back(coll);
    }
}

void eGameWidget::initialize(const int w, const int h) {
    mTem = new eTerrainEditMenu(window());
    addWidget(mTem);
    mTem->align(eAlignment::hcenter | eAlignment::bottom);

    mBoard.initialize(w, h);

    std::string terrDir{"../ZeusTextures/Zeus_Terrain/"};
    if(mTileW == 58) {
        terrDir += "58/";
    } else if(mTileW == 116) {
        terrDir += "116/";
    }

    {
        const std::string pathBase{terrDir + "Zeus_land1_00"};

        for(int i = 2; i < 38;) {
            eTextureCollection coll(renderer());
            for(int j = 0; j < 12; j++, i++) {
                loadTex(pathBase, i, coll);
            }
            mDryToScrubTerrainTexs.push_back(coll);
        }

        for(int i = 38; i < 50; i++) {
            loadTex(pathBase, i, mScrubTerrainTexs);
        }

        for(int i = 62; i < 74; i++) {
            loadTex(pathBase, i, mScrubTerrainTexs);
        }

        {
            eTextureCollection coll(renderer());
            for(int i = 74; i < 86; i++) {
                loadTex(pathBase, i, coll);
            }
            mForestToDryTerrainTexs.push_back(coll);
        }

        for(int i = 86; i < 106; i++) {
            loadTex(pathBase, i, mForestTerrainTexs);
        }

        for(int i = 106; i < 164; i++) {
            loadTex(pathBase, i, mDryTerrainTexs);
        }

        for(int i = 164; i < 172; i++) {
            loadTex(pathBase, i, mWaterTerrainTexs);
        }

        loadWaterToX(172, pathBase, mWaterToDryTerrainTexs);
    }

    {
        const std::string pathBase{terrDir + "Zeus_Land3_00"};

        mSelectedTex.load(renderer(), pathBase + "007.png");

        loadWaterToX(9, pathBase, mWaterToBeachTerrainTexs);

        for(int i = 189; i < 195; i++) {
            loadTex(pathBase, i, mBeachTerrainTexs);
        }

        for(int i = 195; i < 207; i++) {
            loadTex(pathBase, i, mBeachToDryTerrainTexs);
        }

        for(int i = 207; i < 231; i++) {
            loadTex(pathBase, i, mWaterToBeachToDryTerrainTexs);
        }
    }

    {
        const std::string pathBase{terrDir + "Zeus_Trees_00"};

        {
            eTextureCollection coll(renderer());
            for(int i = 1; i < 13; i++) {
                loadTex(pathBase, i, coll);
            }
            mForestToDryTerrainTexs.push_back(coll);
        }

        for(int i = 13; i < 33; i++) {
            loadTex(pathBase, i, mForestTerrainTexs);
        }

        for(int i = 33; i < 45; i++) {
            loadTex(pathBase, i, mForestToScrubTerrainTexs);
        }

        for(int i = 45; i < 97; i++) {
            loadTex(pathBase, i, mForestTerrainTexs);
        }

        for(int i = 121; i < 157;) {
            eTextureCollection coll(renderer());
            for(int j = 0; j < 12; j++, i++) {
                loadTex(pathBase, i, coll);
            }
            mFertileToScrubTerrainTexs.push_back(coll);
        }

        for(int i = 157; i < 165; i++) {
            loadTex(pathBase, i, mFertileTerrainTexs);
        }
        for(int i = 173; i < 181; i++) {
            loadTex(pathBase, i, mFertileToDryTerrainTexs);
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
int gPressedX = -1;
int gPressedY = -1;

void eGameWidget::paintEvent(ePainter& p) {
    const int w = mBoard.width();
    const int h = mBoard.height();
    const int nRows = w + h - 1;

    int minRow = -2*mDY/mTileH + 2;
    int maxRow = minRow + 2*height()/mTileH - 2;
    minRow = std::clamp(minRow, 0, nRows);
    maxRow = std::clamp(maxRow, 0, nRows);

    const int minXYDiff = -2*mDX/mTileW;
    const int maxXYDiff = minXYDiff + 2*width()/mTileW - 1;

    p.setFont(eFonts::defaultFont(resolution()));
    p.translate(mDX, mDY);
    const auto iniIt = eGameBoardDiagonalIterator(minRow, 0, &mBoard);
    for(auto it = iniIt; it != mBoard.dEnd(); ++it) {
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
            const int scrubCount = mDryToScrubTerrainTexs.size();
            const int scrub = tile->scrubId(scrubCount) - 1;
            if(scrub == -1) { // zero scrub
                const int texId = tileId % mDryTerrainTexs.size();
                mDryTerrainTexs.draw(p, pixX, pixY, texId, eAlignment::top);
            } else if(scrubCount == 12) { // full scrub
                const int texId = tileId % mScrubTerrainTexs.size();
                mScrubTerrainTexs.draw(p, pixX, pixY, texId, eAlignment::top);
            } else { // partial scrub
                const int collId = tileId % mDryToScrubTerrainTexs.size();
                const auto& coll = mDryToScrubTerrainTexs[collId];
                coll.draw(p, pixX, pixY, scrub, eAlignment::top);
            }
        } break;
        case eTerrain::beach: {
            std::vector<eTerrain> neighTypes;
            neighTypes.push_back(tile->terrain());
            tile->neighbourTerrainTypes(neighTypes);
            if(neighTypes.size() == 1) {
                const int texId = tileId % mBeachTerrainTexs.size();
                mBeachTerrainTexs.draw(p, pixX, pixY, texId, eAlignment::top);
            } else {
                const auto neighType = neighTypes[1];
                if(neighType == eTerrain::water) {
                    const int texId = tileId % mBeachTerrainTexs.size();
                    mBeachTerrainTexs.draw(p, pixX, pixY, texId, eAlignment::top);
                } else { // if(neighType == eTerrain::dry) {
                    const auto id = eBeachToDry::get(tile);
                    if(id == eBeachToDryId::none) {
                        const int texId = tileId % mBeachTerrainTexs.size();
                        mBeachTerrainTexs.draw(p, pixX, pixY, texId, eAlignment::top);
                    } else {
                        const int texId = static_cast<int>(id);
                        mBeachToDryTerrainTexs.draw(p, pixX, pixY, texId, eAlignment::top);
                    }
                }
            }
        } break;
        case eTerrain::water: {
            if(eWaterCorner::detect(tile)) {
                const int id = eWaterCorner::get(tile);
                mWaterToBeachToDryTerrainTexs.draw(p, pixX, pixY, id, eAlignment::top);
            } else {
                std::vector<eTerrain> neighTypes;
                neighTypes.push_back(tile->terrain());
                tile->neighbourTerrainTypes(neighTypes);
                if(neighTypes.size() == 1) {
                    const int texId = tileId % mWaterTerrainTexs.size();
                    mWaterTerrainTexs.draw(p, pixX, pixY, texId, eAlignment::top);
                } else {
                    const auto it = std::find(neighTypes.begin(), neighTypes.end(), eTerrain::beach);
                    const bool hasBeach = it != neighTypes.end();
                    if(hasBeach) {
                        const auto id = eWaterToBeach::get(tile);
                        if(id == eWaterToDryId::none) {
                            const int texId = tileId % mWaterTerrainTexs.size();
                            mWaterTerrainTexs.draw(p, pixX, pixY, texId, eAlignment::top);
                        } else {
                            const int collId = static_cast<int>(id);
                            const auto& texs = mWaterToBeachTerrainTexs[collId];
                            const int texId = tileId % texs.size();
                            texs.draw(p, pixX, pixY, texId, eAlignment::top);
                        }
                    } else { // if(neighType == eTerrain::dry) {
                        const auto id = eWaterToDry::get(tile);
                        if(id == eWaterToDryId::none) {
                            const int texId = tileId % mWaterTerrainTexs.size();
                            mWaterTerrainTexs.draw(p, pixX, pixY, texId, eAlignment::top);
                        } else {
                            const int collId = static_cast<int>(id);
                            const auto& texs = mWaterToDryTerrainTexs[collId];
                            const int texId = tileId % texs.size();
                            texs.draw(p, pixX, pixY, texId, eAlignment::top);
                        }
                    }
                }
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
                    const int collId = tileId % 2;
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
            p.drawTexture(pixX, pixY, mSelectedTex, eAlignment::top);
        }

        if(gPressedX >= 0 && gPressedY >= 0) {
            const int minX = std::min(gPressedX, gHoverX);
            const int minY = std::min(gPressedY, gHoverY);
            const int maxX = std::max(gPressedX, gHoverX);
            const int maxY = std::max(gPressedY, gHoverY);
            if(tile->x() >= minX && tile->x() <= maxX &&
               tile->y() >= minY && tile->y() <= maxY) {
                p.drawTexture(pixX, pixY, mSelectedTex, eAlignment::top);
            }
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
    case eMouseButton::left:
        pixToId(e.x(), e.y(), gPressedX, gPressedY);
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

bool eGameWidget::mouseReleaseEvent(const eMouseEvent& e) {
    switch(e.button()) {
    case eMouseButton::left: {
        std::function<void(eTile* const)> apply;
        switch(mTem->mode()) {
        case eTerrainEditMode::scrub: {
            apply = [](eTile* const tile) {
                tile->incScrub(0.1);
            };
        } break;
        case eTerrainEditMode::forest: {
            apply = [](eTile* const tile) {
                tile->setTerrain(eTerrain::forest);
            };
        } break;
        case eTerrainEditMode::dry: {
            apply = [](eTile* const tile) {
                tile->setTerrain(eTerrain::dry);
            };
        } break;
        case eTerrainEditMode::beach: {
            apply = [](eTile* const tile) {
                tile->setTerrain(eTerrain::beach);
            };
        } break;
        case eTerrainEditMode::water: {
            apply = [](eTile* const tile) {
                tile->setTerrain(eTerrain::water);
            };
        } break;
        case eTerrainEditMode::fertile: {
            apply = [](eTile* const tile) {
                tile->setTerrain(eTerrain::fertile);
            };
        } break;
        }

        actionOnSelectedTiles(apply);

        gPressedX = -1;
        gPressedY = -1;
    } break;
    default: return false;
    }

    return true;
}

void eGameWidget::actionOnSelectedTiles(const eTileAction& apply) {
    const int minX = std::min(gPressedX, gHoverX);
    const int minY = std::min(gPressedY, gHoverY);
    const int maxX = std::max(gPressedX, gHoverX);
    const int maxY = std::max(gPressedY, gHoverY);

    for(int x = minX; x <= maxX; x++) {
        for(int y = minY; y <= maxY; y++) {
            const auto tile = mBoard.tile(x, y);
            if(!tile) continue;
            apply(tile);
        }
    }
}
