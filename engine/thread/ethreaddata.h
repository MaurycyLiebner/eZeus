#ifndef ETHREADDATA_H
#define ETHREADDATA_H

#include <atomic>
#include <mutex>

#include "engine/thread/ethreadboard.h"

class eThreadData {
public:
    void initialize(const int w, const int h);

    void updateBoard();
    eThreadBoard& board() { return mBoard; }
private:
    std::vector<std::vector<eThreadBoard>> mData;
    eThreadBoard mBoard;
    std::mutex mDataMutex;
};

#endif // ETHREADDATA_H
