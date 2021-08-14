#ifndef ETHREADDATA_H
#define ETHREADDATA_H

#include <atomic>
#include <mutex>

#include "engine/thread/ethreadboard.h"
#include "engine/egameboard.h"

class eThreadData {
public:
    eThreadData() {}
    eThreadData(const eThreadData& s);

    void initialize(const int w, const int h);

    eThreadBoard& board() { return mBoard; }

    void scheduleUpdate(eGameBoard& board,
                        const int x, const int y,
                        const int w, const int h);

    void updateBoard();
private:
    eThreadBoard mBoard;
    std::vector<eThreadBoard> mUpdates;
    std::mutex mMutex;
};

#endif // ETHREADDATA_H
