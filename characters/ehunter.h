#ifndef EHUNTER_H
#define EHUNTER_H

#include "eresourcecollector.h"

class eHunter : public eResourceCollector {
public:
    eHunter(eGameBoard& board);

    bool deerHunter() const { return mDeerHunter; }
    void setDeerHunter(const bool h);
private:
    bool mDeerHunter{false};
};

#endif // EHUNTER_H
