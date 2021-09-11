#include "eobject.h"

#include "engine/egameboard.h"

eObject::eObject(eGameBoard& board) :
    mBoard(board) {

}

void eObject::deleteLater() {
    mBoard.addRubbish(ref<eObject>());
}
