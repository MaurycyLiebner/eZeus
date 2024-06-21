#include "ewritestream.h"

#include "engine/egameboard.h"
#include "characters/actions/echaracteraction.h"
#include "characters/actions/walkable/ewalkableobject.h"
#include "characters/actions/walkable/ehasresourceobject.h"
#include "characters/actions/egodaction.h"
#include "characters/actions/walkable/eobsticlehandler.h"
#include "characters/actions/epatrolmoveaction.h"
#include "spawners/ebanner.h"

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

void eWriteStream::writeCharActFunc(eCharacterActionFunction* const caf) {
    const bool hasFinish = caf != nullptr;
    *this << hasFinish;
    if(hasFinish) {
        *this << caf->type();
        caf->write(*this);
    }
}

void eWriteStream::writeGodAct(eGodAct* const ga) {
    const bool hasFinish = ga != nullptr;
    *this << hasFinish;
    if(hasFinish) {
        *this << ga->type();
        ga->write(*this);
    }
}

void eWriteStream::writeObsticleHandler(eObsticleHandler* const w) {
    *this << bool(w);
    if(w) {
        *this << w->type();
        w->write(*this);
    }
}

void eWriteStream::writeDirectionTimes(eDirectionTimes* const d) {
    *this << d->size();
    for(const auto& dt : *d) {
        writeTile(dt.first);
        dt.second.write(*this);
    }
}

void eWriteStream::writeCity(eWorldCity* const c) {
    const int cid = c ? c->ioID() : -1;
    *this << cid;
}

void eWriteStream::writeBanner(eBanner* const b) {
    const int bid = b ? b->ioID() : -1;
    *this << bid;
}

void eWriteStream::writeSoldierBanner(eSoldierBanner* const b) {
    const int bid = b ? b->ioID() : -1;
    *this << bid;
}

void eWriteStream::writeGameEvent(eGameEvent* const e) {
    const int eid = e ? e->ioID() : -1;
    *this << eid;
}
