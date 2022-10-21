#include "ewritestream.h"

#include "engine/egameboard.h"

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
