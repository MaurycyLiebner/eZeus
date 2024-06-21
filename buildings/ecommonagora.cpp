#include "ecommonagora.h"

int swCA(const eAgoraOrientation o) {
    switch(o) {
    case eAgoraOrientation::bottomLeft:
    case eAgoraOrientation::topRight:
        return 6;
    case eAgoraOrientation::bottomRight:
    case eAgoraOrientation::topLeft:
        return 3;
    }
}

int shCA(const eAgoraOrientation o) {
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
               swCA(o), shCA(o), 3), mO(o) {}

SDL_Point eCommonAgora::pt(const int id) const {
    const auto rect = tileRect();
    const int rx = rect.x;
    const int ry = rect.y;
    return eAgoraBase::pt(rx, ry, mO, id);
}
