#include "ewritestream.h"

#include "engine/egameboard.h"
#include "characters/actions/echaracteraction.h"
#include "characters/actions/walkable/ewalkableobject.h"
#include "characters/actions/walkable/ehasresourceobject.h"

eWriteStream::eWriteStream(SDL_RWops* const dst) :
    mDst(dst) {

}

void eWriteStream::writeTile(eTile* const tile) {
    *this << bool(tile);
    if(tile) {
        *this << tile->x();
        *this << tile->y();
    }
}

void eWriteStream::writeBuilding(eBuilding* const b) {
    const int bid = b ? b->ioID() : -1;
    *this << bid;
}

void eWriteStream::writeCharacter(eCharacter* const c) {
    const int bid = c ? c->ioID() : -1;
    *this << bid;
}

void eWriteStream::writeCharacterAction(eCharacterAction* const ca) {
    const int bid = ca ? ca->ioID() : -1;
    *this << bid;
}

void eWriteStream::writeWalkable(eWalkableObject* const w) {
    *this << bool(w);
    if(w) {
        *this << w->type();
        w->write(*this);
    }
}

void eWriteStream::writeHasResource(eHasResourceObject* const hr) {
    *this << bool(hr);
    if(hr) {
        *this << hr->type();
        hr->write(*this);
    }
}
