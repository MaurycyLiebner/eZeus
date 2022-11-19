#ifndef EHUNTER_H
#define EHUNTER_H

#include "eresourcecollector.h"

class eHunter : public eResourceCollector {
public:
    eHunter(eGameBoard& board);

    bool deerHunter() const { return mDeerHunter; }
    void setDeerHunter(const bool h);

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
private:
    bool mDeerHunter{false};
};

#endif // EHUNTER_H
