#ifndef EBANNER_H
#define EBANNER_H

#include "engine/egameboard.h"

class eTile;

enum class eBannerTypeS {
    boar,
    deer,
    landInvasion,
    settler
};

class eBanner {
public:
    eBanner(const eBannerTypeS type,
            const int id,
            eTile* const tile,
            eGameBoard& board);
    virtual ~eBanner();

    eTile* tile() const { return mTile; }
    eGameBoard& board() { return mBoard; }

    int id() const { return mId; }

    void setIOID(const int id) { mIOID = id; }
    int ioID() const { return mIOID; }

    eBannerTypeS type() const { return mType; }

    virtual void read(eReadStream& src);;
    virtual void write(eWriteStream& dst) const;;

    static eBanner* sCreate(const int id, eTile* const tile,
                            eGameBoard& board,
                            const eBannerTypeS type);
private:
    const eBannerTypeS mType;
    const int mId;
    eTile* const mTile;
    eGameBoard& mBoard;
    int mIOID = -1;
};

#endif // EBANNER_H
