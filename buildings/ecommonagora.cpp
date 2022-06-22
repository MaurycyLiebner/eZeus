#include "ecommonagora.h"

int sw(const eAgoraOrientation o) {
    switch(o) {
    case eAgoraOrientation::bottomLeft:
    case eAgoraOrientation::topRight:
        return 6;
    case eAgoraOrientation::bottomRight:
    case eAgoraOrientation::topLeft:
        return 3;
    }
}

int sh(const eAgoraOrientation o) {
    switch(o) {
    case eAgoraOrientation::bottomLeft:
    case eAgoraOrientation::topRight:
        return 3;
    case eAgoraOrientation::bottomRight:
    case eAgoraOrientation::topLeft:
        return 6;
    }
}

eCommonAgora::eCommonAgora(const eAgoraOrientation o, eGameBoard& board) :
    eAgoraBase(board, eBuildingType::commonAgora,
               sw(o), sh(o), 3), mO(o) {}

SDL_Point eCommonAgora::pt(const int id) const {
    const auto rect = tileRect();
    const int rx = rect.x;
    const int ry = rect.y;
    int dx;
    int dy;
    int ddx;
    int ddy;
    switch(mO) {
    case eAgoraOrientation::bottomLeft:
        dx = 0;
        dy = 2;
        ddx = 2;
        ddy = 0;
        break;
    case eAgoraOrientation::topRight:
        dx = 0;
        dy = 1;
        ddx = 2;
        ddy = 0;
        break;
    case eAgoraOrientation::bottomRight:
        dx = 1;
        dy = 1;
        ddx = 0;
        ddy = 2;
        break;
    case eAgoraOrientation::topLeft:
        dx = 0;
        dy = 1;
        ddx = 0;
        ddy = 2;
        break;
    }

    const int tx = rx + dx + id*ddx;
    const int ty = ry + dy + id*ddy;
    return {tx, ty};
}
