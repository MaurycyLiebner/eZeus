#include "egameobject.h"

eGameObject::eGameObject(const int type, eGameBoard* board) :
    mBoard(board), mType(type) {

}

void eGameObject::moveTo(const int x, const int y) {
    mX = x;
    mY = y;
}

void eGameObject::moveBy(const int dx, const int dy) {
    moveTo(mX + dx, mY + dy);
}
