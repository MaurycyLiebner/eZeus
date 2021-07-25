#ifndef EGAMEEVENTLOOP_H
#define EGAMEEVENTLOOP_H

#include "eeventloop.h"
#include "egameboard.h"

class eGameEventLoop : public eEventLoop {
public:
    eGameEventLoop();

    void initialize(const int w, const int h);

    eGameBoard requestBoard();
private:
    void loop();

    std::mutex mBoardMtx;
    eGameBoard mBoard;
};

#endif // EGAMEEVENTLOOP_H
