#include "egamewidget.h"

#include "eterraineditmenu.h"
#include "etilepainter.h"

#include "textures/egametextures.h"

#include "emainmenu.h"
#include "egamemenu.h"
#include "eminimap.h"

#include "characters/esheep.h"
#include "characters/egoat.h"
#include "characters/actions/eanimalaction.h"

#include "spawners/eboarspawner.h"
#include "spawners/edeerspawner.h"
#include "spawners/esettlerspawner.h"

#include "characters/esoldierbanner.h"
#include "characters/esoldier.h"

#include "echeckbox.h"

#include "esounds.h"

#include "engine/emapgenerator.h"

#include "infowidgets/estorageinfowidget.h"
#include "infowidgets/etradepostinfowidget.h"
#include "infowidgets/ecommonhouseinfowidget.h"
#include "infowidgets/eagorainfowidget.h"

#include "engine/boardData/eheatmaptask.h"
#include "engine/epathfinder.h"

#include "emainwindow.h"

#include "emessagebox.h"
#include "emessages.h"

#include "buildings/sanctuaries/esanctuaryblueprint.h"
#include "buildings/eagoraspace.h"
#include "buildings/esmallhouse.h"
#include "buildings/evendor.h"
#include "buildings/egymnasium.h"
#include "buildings/eanimalbuilding.h"
#include "buildings/eroad.h"
#include "buildings/ebuildingrenderer.h"
#include "buildings/sanctuaries/esanctbuilding.h"
#include "buildings/sanctuaries/esanctuary.h"
#include "buildings/epalace.h"
#include "buildings/epalacetile.h"
#include "buildings/ehorseranch.h"
#include "buildings/ehorseranchenclosure.h"

#include "widgets/eworldwidget.h"

#include "epathdatafindtask.h"

#include "eiteratesquare.h"

#include "elanguage.h"

eGameWidget::eGameWidget(eMainWindow* const window) :
    eWidget(window) {}


void eGameWidget::setBoard(eGameBoard* const board) {
    if(mBoard == board) return;
    mBoard = board;
    mBoard->setEventHandler([this](const eEvent e, eTile* const tile) {
        handleEvent(e, tile);
    });
    mBoard->setVisibilityChecker([this](eTile* const tile) {
        return tileVisible(tile);
    });
    mBoard->setButtonsVisUpdater([this]() {
        mGm->updateButtonsVisibility();
    });
    mBoard->setMessageShower([this](eTile* const t, const eMessageType& msg) {
        showMessage(t, msg);
    });
}

void eGameWidget::initialize() {
    mGm = new eGameMenu(window());
    mGm->initialize(mBoard);
    addWidget(mGm);
    mGm->align(eAlignment::right | eAlignment::top);
    mGm->setGameWidget(this);

    mGm->setViewTileHandler([this](eTile* const tile) {
        if(!tile) return;
        viewTile(tile);
    });

    const auto mm = mGm->miniMap();
    mm->setChangeAction([this, mm]() {
        double fx;
        double fy;
        mm->viewedFraction(fx, fy);
        viewFraction(fx, fy);
    });

    mAm = new eArmyMenu(window());
    mAm->initialize(*mBoard);
    addWidget(mAm);
    mAm->align(eAlignment::right | eAlignment::top);
    mAm->hide();

    const auto mma = mAm->miniMap();
    mma->setChangeAction([this, mma]() {
        double fx;
        double fy;
        mma->viewedFraction(fx, fy);
        viewFraction(fx, fy);
    });

    mTopBar = new eTopBarWidget(window());
    mTopBar->initialize();
    addWidget(mTopBar);
    mTopBar->align(eAlignment::top);
    const int gw = width() - mGm->width();
    mTopBar->setX(gw/2 - mTopBar->width()/2);
    mTopBar->setBoard(mBoard);

    mTem = new eTerrainEditMenu(window());
    mTem->initialize();
    addWidget(mTem);
    mTem->align(eAlignment::right | eAlignment::top);
    mTem->hide();


    mMenuSwitch = new eCheckBox(window());
    mMenuSwitch->move(mGm->x(), 0);
    mMenuSwitch->setCheckAction([this](const bool c) {
        mTem->setVisible(c);
        mGm->setVisible(!c);
    });
    addWidget(mMenuSwitch);

    const auto& setts = window()->settings();
    const auto sizes = setts.availableSizes();
    setTileSize(sizes.front());
}

void eGameWidget::pixToId(const int pixX, const int pixY,
                          int& idX, int& idY) const {
    const double w = mTileW;
    const double h = mTileH;
    idX = std::round((pixX - mDX)/w + (pixY - mDY)/h - 0.5);
    idY = std::round(-(pixX - mDX)/w + (pixY - mDY)/h - 0.5);

    for(int x = idX + 4; x >= idX - 4; x--) {
        for(int y = idY + 4; y >= idY - 4; y--) {
            const auto t = mBoard->tile(x, y);
            if(!t) continue;
            const int a = t->altitude();
            const int dx = 0;
            const int dy = -a*2 + 2;
            const int tpx = std::round(0.5 * (x - y + dx) * mTileW) + mDX;
            const int tpy = std::round(0.5 * (x + y + dy) * mTileH) + mDY;
            const int dist = std::sqrt((tpx - pixX)*(tpx - pixX) +
                                       (tpy - pixY)*(tpy - pixY));
            if(dist < mTileH) {
                idX = x;
                idY = y;
                return;
            }
        }
    }
}

void eGameWidget::setViewMode(const eViewMode m) {
    mViewMode = m;
}

void eGameWidget::mapDimensions(int& mdx, int& mdy) const {
    const int w = mBoard->width();
    const int h = mBoard->height();
    mdx = mTileW*w;
    mdy = mTileH*h/2;
}

void eGameWidget::viewBoxSize(double& fx, double& fy) const {
    int mdx;
    int mdy;
    mapDimensions(mdx, mdy);
    fx = (width() - mGm->width())/double(mdx);
    fy = height()/double(mdy);
}

void eGameWidget::viewedFraction(double& fx, double& fy) const {
    int mdx;
    int mdy;
    mapDimensions(mdx, mdy);
    const int w = width() - mGm->width();
    fx = (0.5*w - mDX)/mdx;
    fy = (0.5*height() - mDY)/mdy;
}

void eGameWidget::tileViewFraction(eTile* const tile,
                                   double& xf, double& yf) const {
    int mdx;
    int mdy;
    mapDimensions(mdx, mdy);
    const int w = width() - mGm->width();
    const int tx = tile->dx()*mTileW;
    const int ty = tile->dy()*mTileH/2;
    xf = (0.5*w + tx)/mdx;
    yf = (0.5*height() + ty)/mdy;
}

void eGameWidget::viewFraction(const double fx, const double fy) {
    int mdx;
    int mdy;
    mapDimensions(mdx, mdy);

    const int w = width() - mGm->width();
    const int dx = -fx*mdx + w/2;
    const int dy = -fy*mdy + height()/2;
    setDX(dx);
    setDY(dy);
}

void eGameWidget::viewTile(eTile* const tile) {
    int mdx;
    int mdy;
    mapDimensions(mdx, mdy);
    const int tx = tile->dx()*mTileW;
    const int ty = tile->dy()*mTileH/2;
    const double x = double(tx)/mdx;
    const double y = double(ty)/mdy;
    viewFraction(x, y);
}

bool eGameWidget::tileVisible(eTile* const tile) const {
    if(!tile) return false;

    double fx;
    double fy;
    viewBoxSize(fx, fy);

    double ffx;
    double ffy;
    viewedFraction(ffx, ffy);

    double txf;
    double tyf;
    tileViewFraction(tile, txf, tyf);

    const double top = ffy - fy/2;
    const double left = ffx - fx/2;
    const double bottom = top + fy;
    const double right = left + fx;

    if(txf > right) return false;
    if(txf < left) return false;
    if(tyf > bottom) return false;
    if(tyf < top) return false;
    return true;
}

void eGameWidget::iterateOverVisibleTiles(const eTileAction& a) {
    const int minX = std::clamp(-mDX/mTileW - 5, 0, mBoard->width());
    const int visWidth = width() - mGm->width();
    const int maxX = std::clamp(minX + visWidth/mTileW + 10, 0, mBoard->width());

    const int minY = std::clamp(-2*mDY/mTileH - 10, 0, mBoard->height());
    const int maxY = std::clamp(minY + 2*height()/mTileH + 15, 0, mBoard->height());

    const bool play = Mix_Playing(-1) == 0 && (rand() % 250) == 0;
    if(play) {
        const int x = (minX + maxX)/2 + (rand() % 7 - 3);
        const int y = (minY + maxY)/2 + (rand() % 7 - 3);
        const auto t = mBoard->tile(x, y);
        if(t) eSounds::playSoundForTile(t);
    }

    for(int y = minY; y < maxY; y++) {
        for(int x = minX; x < maxX; x++) {
            const auto t = mBoard->dtile(x, y);
            a(t);
        }
    }
}

void buildTiles(int& minX, int& minY,
                int& maxX, int& maxY,
                const int tx, const int ty,
                const int sw, const int sh) {
    minX = tx;
    minY = ty;

    if(sw == 2 && sh == 2) {
        minY -= 1;
    } else if(sw == 3 && sh == 3) {
        minX -= 1;
        minY -= 1;
    } else if(sw == 4 || sh == 4) {
        minX -= 1;
        minY -= 2;
    } else if(sw == 5 || sh == 5) {
        minX -= 2;
        minY -= 2;
    }

    maxX = minX + sw;
    maxY = minY + sh;
}

bool eGameWidget::canBuildBase(const int minX, const int maxX,
                               const int minY, const int maxY,
                               const eSpecialRequirement& specReq) {
    for(int x = minX; x < maxX; x++) {
        for(int y = minY; y < maxY; y++) {
            const auto t = mBoard->tile(x, y);
            if(!t || t->underBuilding()) return false;
            if(specReq && !specReq(t)) return false;

            const auto ttt = t->terrain();
            const auto ttta = ttt & eTerrain::buildable;
            if(!static_cast<bool>(ttta)) return false;

            if(!t->walkableElev() && t->isElevationTile()) return false;
        }
    }
    return true;
}

bool eGameWidget::canBuild(const int tx, const int ty,
                           const int sw, const int sh,
                           const eSpecialRequirement& specReq) {
    int minX;
    int minY;
    int maxX;
    int maxY;
    buildTiles(minX, minY, maxX, maxY, tx, ty, sw, sh);
    return canBuildBase(minX, maxX, minY, maxY, specReq);
}

bool eGameWidget::canBuildVendor(const int tx, const int ty,
                                 const eResourceType resType) {
    const auto t = mBoard->tile(tx, ty);
    if(!t) return false;
    const auto b = t->underBuilding();
    if(!b) return false;
    const auto bt = b->type();
    if(bt != eBuildingType::agoraSpace) return false;
    const auto space = static_cast<eAgoraSpace*>(b);
    const auto agora = space->agora();
    if(agora->vendor(resType)) return false;
    const auto ct = b->centerTile();
    if(!ct) return false;
    return ct->x() == tx && ct->y() == ty;
}

bool tileDry(eTile* const t) {
    if(!t) return false;
    return t->terrain() == eTerrain::dry ||
           t->terrain() == eTerrain::fertile;
}

bool tileWater(eTile* const t) {
    if(!t) return false;
    return t->terrain() == eTerrain::water;
}

bool canBuildFisheryTR(eTile* const t) {
    if(!t) return false;
    if(!tileDry(t)) return false;

    const auto tr = t->topRight<eTile>();
    if(!tr) return false;
    if(!tileWater(tr)) return false;

    const auto trtr = tr->topRight<eTile>();
    if(!trtr) return false;
    if(!tileWater(trtr)) return false;
    if(trtr->isShoreTile()) return false;

    const auto trtl = tr->topLeft<eTile>();
    if(!trtl) return false;
    if(!tileWater(trtl)) return false;

    const auto trbr = tr->bottomRight<eTile>();
    if(!trbr) return false;
    if(!tileWater(trbr)) return false;

    const auto trbrtr = trbr->topRight<eTile>();
    if(!trbrtr) return false;
    if(!tileWater(trbrtr)) return false;
    if(trbrtr->isShoreTile()) return false;

    const auto trbrbr = trbr->bottomRight<eTile>();
    if(!trbrbr) return false;
    if(!tileWater(trbrbr)) return false;

    const auto br = t->bottomRight<eTile>();
    if(!br) return false;
    if(!tileDry(br)) return false;

    return true;
}

bool canBuildFisheryBR(eTile* const t) {
    if(!t) return false;
    if(!tileDry(t)) return false;

    const auto tr = t->topRight<eTile>();
    if(!tr) return false;
    if(!tileDry(tr)) return false;

    const auto trbr = tr->bottomRight<eTile>();
    if(!trbr) return false;
    if(!tileWater(trbr)) return false;

    const auto trbrbr = trbr->bottomRight<eTile>();
    if(!trbrbr) return false;
    if(!tileWater(trbrbr)) return false;
    if(trbrbr->isShoreTile()) return false;

    const auto trbrtr = trbr->topRight<eTile>();
    if(!trbrtr) return false;
    if(!tileWater(trbrtr)) return false;

    const auto br = t->bottomRight<eTile>();
    if(!br) return false;
    if(!tileWater(br)) return false;

    const auto brbr = br->bottomRight<eTile>();
    if(!brbr) return false;
    if(!tileWater(brbr)) return false;
    if(brbr->isShoreTile()) return false;

    const auto brbl = br->bottomLeft<eTile>();
    if(!brbl) return false;
    if(!tileWater(brbl)) return false;

    return true;
}

bool canBuildFisheryBL(eTile* const t) {
    if(!t) return false;
    if(!tileWater(t)) return false;

    const auto bl = t->bottomLeft<eTile>();
    if(!bl) return false;
    if(!tileWater(bl)) return false;
    if(bl->isShoreTile()) return false;

    const auto tl = t->topLeft<eTile>();
    if(!tl) return false;
    if(!tileWater(tl)) return false;

    const auto tr = t->topRight<eTile>();
    if(!tr) return false;
    if(!tileDry(tr)) return false;

    const auto trbr = tr->bottomRight<eTile>();
    if(!trbr) return false;
    if(!tileDry(trbr)) return false;

    const auto br = t->bottomRight<eTile>();
    if(!br) return false;
    if(!tileWater(br)) return false;

    const auto brbl = br->bottomLeft<eTile>();
    if(!brbl) return false;
    if(!tileWater(brbl)) return false;
    if(brbl->isShoreTile()) return false;

    const auto brbr = br->bottomRight<eTile>();
    if(!brbr) return false;
    if(!tileWater(brbr)) return false;

    return true;
}

bool canBuildFisheryTL(eTile* const t) {
    if(!t) return false;
    if(!tileWater(t)) return false;

    const auto tl = t->topLeft<eTile>();
    if(!tl) return false;
    if(!tileWater(tl)) return false;
    if(tl->isShoreTile()) return false;

    const auto bl = t->bottomLeft<eTile>();
    if(!bl) return false;
    if(!tileWater(bl)) return false;

    const auto tr = t->topRight<eTile>();
    if(!tr) return false;
    if(!tileWater(tr)) return false;

    const auto trtl = tr->topLeft<eTile>();
    if(!trtl) return false;
    if(!tileWater(trtl)) return false;
    if(trtl->isShoreTile()) return false;

    const auto trtr = tr->topRight<eTile>();
    if(!trtr) return false;
    if(!tileWater(trtr)) return false;

    const auto trbr = tr->bottomRight<eTile>();
    if(!trbr) return false;
    if(!tileDry(trbr)) return false;

    const auto br = t->bottomRight<eTile>();
    if(!br) return false;
    if(!tileDry(br)) return false;

    return true;
}

bool eGameWidget::canBuildFishery(const int tx, const int ty,
                                  eOrientation& o) {
    const auto t = mBoard->tile(tx, ty);
    if(!t) return false;
    const bool tr = canBuildFisheryTR(t);
    if(tr) {
        o = eOrientation::topRight;
        return true;
    }
    const bool br = canBuildFisheryBR(t);
    if(br) {
        o = eOrientation::bottomRight;
        return true;
    }
    const bool bl = canBuildFisheryBL(t);
    if(bl) {
        o = eOrientation::bottomLeft;
        return true;
    }
    const bool tl = canBuildFisheryTL(t);
    if(tl) {
        o = eOrientation::topLeft;
        return true;
    }
    return false;
}

bool eGameWidget::canBuildPier(const int tx, const int ty,
                               eOrientation& o) {
    const bool r = canBuildFishery(tx, ty, o);
    if(!r) return false;
    switch(o) {
    case eOrientation::topRight: {
        const int minX = tx - 1;
        const int minY = ty + 1;
        return canBuildBase(minX, minX + 4, minY, minY + 4);
    } break;
    case eOrientation::bottomRight: {
        const int minX = tx - 4;
        const int minY = ty - 2;
        return canBuildBase(minX, minX + 4, minY, minY + 4);
    } break;
    case eOrientation::bottomLeft: {
        const int minX = tx - 1;
        const int minY = ty - 5;
        return canBuildBase(minX, minX + 4, minY, minY + 4);
    } break;
    default:
    case eOrientation::topLeft: {
        const int minX = tx + 2;
        const int minY = ty - 2;
        return canBuildBase(minX, minX + 4, minY, minY + 4);
    } break;
    }
}

std::vector<ePatrolGuide>::iterator
    eGameWidget::findGuide(const int tx, const int ty) {
    const auto pgs = mPatrolBuilding->patrolGuides();
    const int iMax = pgs->size();
    for(int i = 0; i < iMax; i++) {
        auto& pg = (*pgs)[i];
        if(pg.fX == tx && pg.fY == ty) {
            return pgs->begin() + i;
        }
    }
    return pgs->end();
}

void eGameWidget::updateMinimap() {
    double fx;
    double fy;
    viewedFraction(fx, fy);
    const auto mm = mGm->miniMap();
    mm->viewFraction(fx, fy);
    const auto mma = mAm->miniMap();
    mma->viewFraction(fx, fy);
}

int eGameWidget::waterParkId() const {
    return mTime/(mSpeed*150);
}

void eGameWidget::showMessage(eTile* const tile, const eMessageType& msg) {
    showMessage(tile, msg.fFull);
}

void eGameWidget::showMessage(eTile* const tile, const eMessage& msg) {
    const auto msgb = new eMessageBox(window());
    msgb->setHeight(height()/3);
    msgb->setWidth(width()/2);
    eAction a;
    if(tile) {
        a = [this, tile]() {
            viewTile(tile);
        };
    }
    const auto& d = mBoard->date();
    msgb->initialize(a, d, msg, mBoard->playerName());
    addWidget(msgb);
    msgb->align(eAlignment::bottom | eAlignment::hcenter);
    msgb->setY(msgb->y() - mGm->width()/10);
    msgb->setX(msgb->x() - mGm->width()/2);
}

bool eGameWidget::roadPath(std::vector<eOrientation>& path) {
    ePathFinder p([](eTileBase* const t) {
        const auto terr = t->terrain();
        const bool tr = static_cast<bool>(eTerrain::buildable & terr);
        if(!tr) return false;
        const auto bt = t->underBuildingType();
        const bool r = bt == eBuildingType::road ||
                       bt == eBuildingType::none;
        if(!r) return false;
        if(!t->walkableElev() && t->isElevationTile()) return false;
        return true;
    }, [&](eTileBase* const t) {
        return t->x() == mPressedTX && t->y() == mPressedTY;
    });
    const auto startTile = mBoard->tile(mHoverTX, mHoverTY);
    const int w = mBoard->width();
    const int h = mBoard->height();
    const bool r = p.findPath(startTile, 100, true, w, h);
    if(!r) return false;
    return p.extractPath(path);
}

bool eGameWidget::inErase(const int tx, const int ty) {
    const auto mode = mGm->mode();
    const bool e = mode == eBuildingMode::erase;
    const bool high = mTem->visible() || e;
    if(!high) return false;

    const int sMinX = std::min(mPressedTX, mHoverTX);
    const int sMinY = std::min(mPressedTY, mHoverTY);
    const int sMaxX = std::max(mPressedTX, mHoverTX);
    const int sMaxY = std::max(mPressedTY, mHoverTY);

    bool s = false;
    if(mLeftPressed &&
       tx >= sMinX && tx <= sMaxX &&
       ty >= sMinY && ty <= sMaxY) {
        s = true;
    }
    const bool h = tx == mHoverTX && ty == mHoverTY;
    return h || s;
}

bool eGameWidget::inErase(const SDL_Rect& rect) {
    for(int x = rect.x; x < rect.x + rect.w; x++) {
        for(int y = rect.y; y < rect.y + rect.h; y++) {
            const bool r = inErase(x, y);
            if(r) return true;
        }
    }
    return false;
}

bool eGameWidget::inErase(eAgoraBase* const a) {
    const auto rr = a->tileRect();
    for(int x = rr.x; x < rr.x + rr.w; x++) {
        for(int y = rr.y; y < rr.y + rr.h; y++) {
            if(!inErase(x, y)) continue;
            const auto t = mBoard->tile(x, y);
            if(!t) continue;
            const auto ub = t->underBuilding();
            if(!ub) continue;
            const auto v = dynamic_cast<eVendor*>(ub);
            if(!v) return true;
        }
    }
    return false;
}

bool eGameWidget::inErase(eBuilding* const b) {
    if(!b) return false;
    const auto mode = mGm->mode();
    const bool e = mode == eBuildingMode::erase;
    const bool high = mTem->visible() || e;
    if(!high) return false;

    SDL_Rect rect;
    if(const auto sb = dynamic_cast<eSanctBuilding*>(b)) {
        const auto s = sb->sanctuary();
        rect = s->tileRect();
    } else if(const auto v = dynamic_cast<eVendor*>(b)) {
        if(inErase(b->tileRect())) return true;
        const auto a = v->agora();
        return inErase(a);
    } else if(const auto as = dynamic_cast<eAgoraSpace*>(b)) {
        const auto a = as->agora();
        return inErase(a);
    } else if(const auto r = dynamic_cast<eRoad*>(b)) {
        const auto a = r->underAgora();
        if(a) return inErase(a);
        else rect = b->tileRect();
    } else if(const auto a = dynamic_cast<eAgoraBase*>(b)) {
        return inErase(a);
    } else if(const auto p = dynamic_cast<ePalace*>(b)) {
        const auto& ts = p->tiles();
        for(const auto& t : ts) {
            const auto tt = t->centerTile();
            const int tx = tt->x();
            const int ty = tt->y();
            if(inErase(tx, ty)) return true;
        }
        rect = p->tileRect();
    } else if(const auto p = dynamic_cast<ePalaceTile*>(b)) {
        return inErase(p->palace());
    } else if(const auto hr = dynamic_cast<eHorseRanch*>(b)) {
        const bool e1 = inErase(hr->tileRect());
        if(e1) return true;
        const auto hre = hr->enclosure();
        rect = hre->tileRect();
    } else if(const auto hr = dynamic_cast<eHorseRanchEnclosure*>(b)) {
        const bool e1 = inErase(hr->tileRect());
        if(e1) return true;
        const auto hre = hr->ranch();
        rect = hre->tileRect();
    } else {
        rect = b->tileRect();
    }
    return inErase(rect);
}

bool eGameWidget::build(const int tx, const int ty,
                        const int sw, const int sh,
                        const eBuildingCreator& bc,
                        const eSpecialRequirement& specReq,
                        const eRendererCreator& rc) {
    if(!bc) return false;
    const auto tile = mBoard->tile(tx, ty);
    if(!tile) return false;
    const bool cb = canBuild(tx, ty, sw, sh, specReq);
    if(!cb) return false;
    const auto b = bc();
    if(!b) return false;
    const bool isRoad = b->type() == eBuildingType::road;
    if(!isRoad && tile->isElevationTile()) return false;
    const auto rend = rc ? rc() : e::make_shared<eBuildingRenderer>(b);
    tile->setBuilding(rend);
    b->setCenterTile(tile);
    int minX;
    int minY;
    int maxX;
    int maxY;
    buildTiles(minX, minY, maxX, maxY,
               tx, ty, sw, sh);
    b->setTileRect({minX, minY, sw, sh});
    for(int x = minX; x < maxX; x++) {
        for(int y = minY; y < maxY; y++) {
            const auto t = mBoard->tile(x, y);
            if(t) {
                t->setUnderBuilding(b);
                b->addUnderBuilding(t);
            }
        }
    }

    const auto diff = mBoard->difficulty();
    const int cost = eDifficultyHelpers::buildingCost(diff, b->type());
    mBoard->incDrachmas(-cost);
    return true;
}

bool eGameWidget::sTileFertile(eTile* const tile) {
    return tile->terrain() == eTerrain::fertile;
}

void eGameWidget::buildAnimal(eTile* const tile,
                              const eBuildingType type,
                              const eAnimalCreator& creator) {
    const int tx = tile->x();
    const int ty = tile->y();
    const bool cb = canBuild(tx, ty, 1, 2, sTileFertile);
    if(!cb) return;
    const auto sh = creator(*mBoard);
    sh->changeTile(tile);
    const auto e = []() {};
    sh->setAction(e::make_shared<eAnimalAction>(
                     sh.get(), e, e, tx, ty,
                     eMoveAroundAction::sFertileWalkable));

    const auto diff = mBoard->difficulty();
    const int cost = eDifficultyHelpers::buildingCost(
                         diff, type);
    mBoard->incDrachmas(-cost);

    build(tx, ty, 1, 2, [this, sh, type]() {
        return e::make_shared<eAnimalBuilding>(
                    *mBoard, sh.get(), type);
    }, sTileFertile);
}

bool eGameWidget::keyPressEvent(const eKeyPressEvent& e) {
    if(mLocked) return true;
    const auto k = e.key();
    if(k == SDL_Scancode::SDL_SCANCODE_KP_PLUS ||
       k == SDL_Scancode::SDL_SCANCODE_RIGHTBRACKET) {
        mSpeedId = std::clamp(mSpeedId + 1, 0, 4);
        mSpeed = sSpeeds[mSpeedId];
    } else if(k == SDL_Scancode::SDL_SCANCODE_KP_MINUS ||
              k == SDL_Scancode::SDL_SCANCODE_LEFTBRACKET) {
        mSpeedId = std::clamp(mSpeedId - 1, 0, 4);
        mSpeed = sSpeeds[mSpeedId];
    } else if(k == SDL_Scancode::SDL_SCANCODE_R) {
        mRotate = !mRotate;
        mRotateId++;
        if(mRotateId > 3) mRotateId = 0;
    } else if(k == SDL_Scancode::SDL_SCANCODE_P) {
        mPaused = !mPaused;
        if(mPaused && !mPausedLabel) {
            const auto str = eLanguage::text("paused");
            const auto space = "     ";
            mPausedLabel = new eFramedLabel(space + str + space, window());
            mPausedLabel->setType(eFrameType::message);
            mPausedLabel->setSmallFontSize();
            mPausedLabel->setHugePadding();
            mPausedLabel->fitContent();
            addWidget(mPausedLabel);
            const int vw = width() - mGm->width();
            const int w = mPausedLabel->width();
            mPausedLabel->setX((vw - w)/2);
            const int p = mPausedLabel->padding();
            mPausedLabel->setY(mTopBar->height() + 2*p);
        } else if(mPausedLabel) {
            mPausedLabel->deleteLater();
            mPausedLabel = nullptr;
        }
    } else if(k == SDL_Scancode::SDL_SCANCODE_LEFT) {
        setDX(mDX + 35);
    } else if(k == SDL_Scancode::SDL_SCANCODE_RIGHT) {
        setDX(mDX - 35);
    } else if(k == SDL_Scancode::SDL_SCANCODE_UP) {
        setDY(mDY + 35);
    } else if(k == SDL_Scancode::SDL_SCANCODE_DOWN) {
        setDY(mDY - 35);
    } else if(k == SDL_Scancode::SDL_SCANCODE_ESCAPE) {
        if(mMenu) {
            mMenu->deleteLater();
            mMenu = nullptr;
        } else {
            mMenu = new eGameMainMenu(window());
            mMenu->resize(width()/4, height()/2);
            const auto w = window();
            mMenu->initialize([w]() {
                w->closeGame();
            }, mBoard);
            addWidget(mMenu);
            mMenu->align(eAlignment::center);
        }
    }
    return true;
}

bool eGameWidget::mousePressEvent(const eMouseEvent& e) {
    if(mLocked) return true;
    mGm->closeBuildWidget();
    mMovedSincePress = false;
    const auto b = e.button();
    if(b != eMouseButton::middle) {
        eSounds::playButtonSound();
    }
    switch(b) {
    case eMouseButton::middle:
        mLastX = e.x();
        mLastY = e.y();
        return true;
    case eMouseButton::left:
        mLeftPressed = true;
        int tx;
        int ty;
        pixToId(e.x(), e.y(), tx, ty);
        mPressedTX = tx;
        mPressedTY = ty;
        mPressedX = e.x();
        mPressedY = e.y();
        if(mPatrolBuilding) {
            const auto tile = mBoard->tile(tx, ty);
            if(!tile) return true;
            if(tile->underBuilding() == mPatrolBuilding) {
                const auto pgs = mPatrolBuilding->patrolGuides();
                pgs->clear();
            } else {
                const auto pgs = mPatrolBuilding->patrolGuides();
                const auto it = findGuide(tx, ty);
                if(it != pgs->end()) {
                    pgs->erase(it);
                } else {
                    if(tile->hasRoad()) pgs->push_back({tx, ty});
                }
            }
        }
        return true;
    case eMouseButton::right: {
        const auto& solds = mBoard->selectedSoldiers();
        if(mGm->mode() != eBuildingMode::none) {
            mGm->clearMode();
            return true;
        }
        if(!solds.empty()) return true;
        int tx;
        int ty;
        pixToId(e.x(), e.y(), tx, ty);
        if(mPatrolBuilding) {
            setViewMode(eViewMode::defaultView);
            mPatrolBuilding = nullptr;
        }
        const auto tile = mBoard->tile(tx, ty);
        if(!tile) return true;
        const auto b = tile->underBuilding();
        if(!b) return true;
        eInfoWidget* wid = nullptr;
        eAction closeAct;
        if(const auto gym = dynamic_cast<eGymnasium*>(b)) {
            const auto gymWid = new eGymInfoWidget(window());
            gymWid->initialize();
            wid = gymWid;
        } else if(const auto house = dynamic_cast<eHouseBase*>(b)) {
            const auto w = new eCommonHouseInfoWidget(window());
            w->initialize(house);
            wid = w;
        } else if(const auto stor = dynamic_cast<eTradePost*>(b)) {
            const auto storWid = new eTradePostInfoWidget(window());
            storWid->initialize(stor);
            wid = storWid;
            const stdptr<eTradePost> storptr(stor);
            closeAct = [storptr, storWid]() {
                if(storptr) {
                    std::map<eResourceType, int> maxCount;
                    eResourceType imports;
                    eResourceType exports;
                    storWid->get(imports, exports, maxCount);
                    storptr->setOrders(imports, exports);
                    storptr->setMaxCount(maxCount);
                }
            };
        } else if(const auto stor = dynamic_cast<eStorageBuilding*>(b)) {
            const auto storWid = new eStorageInfoWidget(window());
            storWid->initialize(stor);
            wid = storWid;
            const stdptr<eStorageBuilding> storptr(stor);
            closeAct = [storptr, storWid]() {
                if(!storptr) return;
                std::map<eResourceType, int> maxCount;
                eResourceType get;
                eResourceType empty;
                eResourceType accept;
                eResourceType dontaccept;
                storWid->get(get, empty, accept, dontaccept, maxCount);
                storptr->setOrders(get, empty, accept);
                storptr->setMaxCount(maxCount);
            };
        }
        eAgoraBase* a = nullptr;
        if(const auto aa = dynamic_cast<eAgoraBase*>(b)) {
            a = aa;
        } else if(const auto v = dynamic_cast<eVendor*>(b)) {
            a  = v->agora();
        } else if(const auto v = dynamic_cast<eAgoraSpace*>(b)) {
            a  = v->agora();
        } else if(const auto v = dynamic_cast<eRoad*>(b)) {
            a  = v->underAgora();
        }
        if(a) {
            const auto aWid = new eAgoraInfoWidget(window());
            aWid->initialize(a);
            wid = aWid;
            const stdptr<eAgoraBase> aptr(a);
            closeAct = [aptr, aWid]() {
                if(!aptr) return;

            };
        }
        if(wid) {
            addWidget(wid);
            wid->setX((width() - mGm->width() - wid->width())/2);
            wid->align(eAlignment::vcenter);
            wid->setCloseAction([this, wid, closeAct]() {
                if(closeAct) closeAct();
                removeWidget(wid);
                wid->deleteLater();
            });
        }
    } break;
    default: return true;
    }
    return true;
}

bool eGameWidget::mouseMoveEvent(const eMouseEvent& e) {
    if(mLocked) return true;
    mMovedSincePress = true;
    if(static_cast<bool>(e.buttons() & eMouseButton::middle)) {
        const int dx = e.x() - mLastX;
        const int dy = e.y() - mLastY;
        setDX(mDX + dx);
        setDY(mDY + dy);
        updateMinimap();
        mLastX = e.x();
        mLastY = e.y();
    } else {
        mHoverX = e.x();
        mHoverY = e.y();
        pixToId(e.x(), e.y(), mHoverTX, mHoverTY);
    }
    return true;
}

bool eGameWidget::mouseReleaseEvent(const eMouseEvent& e) {
    if(mLocked) return true;
    switch(e.button()) {
    case eMouseButton::left: {
        mBoard->clearSoldierSelection();
        mLeftPressed = false;
        const bool r = buildMouseRelease();
        if(!r) {
            if(mMovedSincePress) {
                const int x0 = mPressedX > mHoverX ? mHoverX : mPressedX;
                const int y0 = mPressedY > mHoverY ? mHoverY : mPressedY;
                const int x1 = mPressedX > mHoverX ? mPressedX : mHoverX;
                const int y1 = mPressedY > mHoverY ? mPressedY : mHoverY;
                int t0x;
                int t0y;
                int t1x;
                int t1y;
                pixToId(x0, y0, t0x, t0y);
                pixToId(x1, y1, t1x, t1y);

                for(int x = t0x; x < t1x; x++) {
                    for(int y = t0y; y < t1y; y++) {
                        const auto tile = mBoard->tile(x, y);
                        if(!tile) continue;
                        const auto b = tile->banner();
                        if(b) {
                            if(!b->selected()) mBoard->selectSoldier(b);
                        }
                    }
                }
            } else {
                const auto tile = mBoard->tile(mHoverTX, mHoverTY);
                if(!mPatrolBuilding && tile) {
                    if(const auto b = tile->underBuilding()) {
                        if(const auto pb = dynamic_cast<ePatrolBuilding*>(b)) {
                            setViewMode(eViewMode::patrolBuilding);
                            mPatrolBuilding = pb;
                        }
                    }
                }
            }
        }
        mPressedTX = -1;
        mPressedTY = -1;
    } break;
    case eMouseButton::right: {
        const int hx = mHoverTX;
        const int hy = mHoverTY;
        const auto& solds = mBoard->selectedSoldiers();

        int isld = 0;
        const int slds = solds.size();
        const int dist = 5;

        const auto prcsTile = [&](const int i, const int j) {
            if(isld >= slds) return false;
            const int tx = hx + i;
            const int ty = hy + j;
            const auto tt = mBoard->tile(tx, ty);
            if(!tt) return false;
            if(!tt->walkable()) return false;
            if(tt->banner()) return false;

            const auto s = solds[isld++];
            s->moveTo(tx, ty);
            return false;
        };

        const int kinc = slds == 1 ? 1 : dist;
        for(int k = 0; isld < slds; k += kinc) {
            eIterateSquare::iterateSquare(k, prcsTile, dist);
        }
    } break;
    default: return false;
    }

    return true;
}

bool eGameWidget::mouseWheelEvent(const eMouseWheelEvent& e) {
    if(mLocked) return true;
    const bool wheel = std::abs(mWheel) > 3;
    if(!wheel) {
        mWheel += e.dy();
        return true;
    }
    mWheel = 0;
    const auto& sett = window()->settings();
    std::vector<eTileSize> sizes;
    int currSize = 0;
    if(sett.fTinyTextures) {
        sizes.push_back(eTileSize::s15);
        if(mTileSize == eTileSize::s15) {
            currSize = sizes.size() - 1;
        }
    }
    if(sett.fSmallTextures) {
        sizes.push_back(eTileSize::s30);
        if(mTileSize == eTileSize::s30) {
            currSize = sizes.size() - 1;
        }
    }
    if(sett.fMediumTextures) {
        sizes.push_back(eTileSize::s45);
        if(mTileSize == eTileSize::s45) {
            currSize = sizes.size() - 1;
        }
    }
    if(sett.fLargeTextures) {
        sizes.push_back(eTileSize::s60);
        if(mTileSize == eTileSize::s60) {
            currSize = sizes.size() - 1;
        }
    }
    const int sizesC = sizes.size();
    if(e.dy() > 0) {
        const int newSize = currSize + 1;
        if(newSize < sizesC) {
            setTileSize(sizes[newSize]);
        }
    } else {
        const int newSize = currSize - 1;
        if(newSize >= 0) {
            setTileSize(sizes[newSize]);
        }
    }
    return true;
}

void eGameWidget::setDX(const int dx) {
    mDX = dx;
    clampViewBox();
    updateMinimap();
}

void eGameWidget::setDY(const int dy) {
    mDY = dy;
    clampViewBox();
    updateMinimap();
}

void eGameWidget::clampViewBox() {
    if(mTem->visible()) return;
    const int w = mBoard->width();
    const int ww = width() - mGm->width();
    mDX = std::min(0, mDX);
    mDX = std::max(-w*mTileW + ww + mTileW/2, mDX);

    const int h = mBoard->height();
    const int hh = height();
    mDY = std::min(-mTileH/2, mDY);
    mDY = std::max(-h*mTileH/2 + hh, mDY);
}

void eGameWidget::setTileSize(const eTileSize size) {
    mTileSize = size;
    const int tid = static_cast<int>(mTileSize);
    const auto& trrTexs = eGameTextures::terrain().at(tid);
    const int newW = trrTexs.fTileW;
    const int newH = trrTexs.fTileH;

    const double dnewW = newW;
    const double dnewH = newH;

    const int dx = std::round((mDX - width()/2) * dnewW/mTileW + width()/2);
    const int dy = std::round((mDY - height()/2) * dnewH/mTileH + height()/2);

    mTileW = newW;
    mTileH = newH;

    setDX(dx);
    setDY(dy);

    {
        double fx;
        double fy;
        viewBoxSize(fx, fy);
        const auto mm = mGm->miniMap();
        mm->setViewBoxSize(fx, fy);
        const auto mma = mAm->miniMap();
        mma->setViewBoxSize(fx, fy);
    }

    clampViewBox();

    updateTerrainTextures();
}

void eGameWidget::actionOnSelectedTiles(const eTileAction& apply) {
    if(!apply) return;
    const int minX = std::min(mPressedTX, mHoverTX);
    const int minY = std::min(mPressedTY, mHoverTY);
    const int maxX = std::max(mPressedTX, mHoverTX);
    const int maxY = std::max(mPressedTY, mHoverTY);

    for(int x = minX; x <= maxX; x++) {
        for(int y = minY; y <= maxY; y++) {
            const auto tile = mBoard->tile(x, y);
            if(!tile) continue;
            apply(tile);
        }
    }
}
