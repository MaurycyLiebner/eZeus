#include "eobject.h"

#include "engine/egameboard.h"

eObject::eObject(eGameBoard& board) :
    mBoard(board) {

}

void eObject::deleteLater() {
    if(mDeleteLater) return;
    mDeleteLater = true;
    mBoard.addRubbish(ref<eObject>());
}
