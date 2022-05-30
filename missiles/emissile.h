#ifndef EMISSILE_H
#define EMISSILE_H

#include <functional>

#include "pointers/estdselfref.h"
#include "textures/edestructiontextures.h"
#include "vec2.h"

class eTile;
enum class eTileSize : int;
class eGameBoard;

using eAction = std::function<void()>;

struct ePathPoint {
    double fX;
    double fY;
    double fHeight;
};

class eMissilePath {
public:
    eMissilePath(const std::vector<ePathPoint>& pts) :
        mPos(pts[0]), mPts(pts) {
        progress(0.011);
    }

    bool finished() const {
        return mPtId >= (int)mPts.size();
    }

    void progress(const double by) {
        if(by < 0.01) return;
        if(finished()) return;
        const auto& dst = mPts[mPtId];
        vec2d line{dst.fX - mPos.fX, dst.fY - mPos.fY};
        mAngle = line.angle();
        const double len = line.length();
        if(by > len) {
            mPos = dst;
            mPtId++;
            return progress(by - len);
        } else {
            const double inc = by/len;
            line *= inc;
            mPos.fX += line.x;
            mPos.fY += line.y;
            const double hline = dst.fHeight - mPos.fHeight;
            mPos.fHeight += inc*hline;
        }
    }

    const ePathPoint& pos() const { return mPos; }
    double angle() const { return mAngle; }
    double height() const { return mPos.fHeight; }
private:
    double mAngle;
    ePathPoint mPos;
    int mPtId = 0;
    std::vector<ePathPoint> mPts;
};

class eMissile : public eStdSelfRef {
public:
    eMissile(eGameBoard& board,
             const std::vector<ePathPoint>& path);
    ~eMissile();

    void incTime(const int by);

    virtual std::shared_ptr<eTexture>
        getTexture(const eTileSize size) const {
        (void)size;
        return nullptr;
    }

    double x() const;
    double y() const;

    void setFinishAction(const eAction& a);

    void setSpeed(const double s) { mSpeed = s; }
    double speed() const { return mSpeed; }

    double angle() const { return mPath.angle(); }
    double height() const { return mPath.height(); }
private:
    void changeTile(eTile* const t);

    eGameBoard& mBoard;
    eMissilePath mPath;

    double mSpeed = 1;

    eAction mFinish;

    eTile* mTile = nullptr;
};

#endif // EMISSILE_H
