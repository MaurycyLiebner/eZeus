#ifndef EWAITACTION_H
#define EWAITACTION_H

#include "echaracteraction.h"

#include "elimits.h"

class eWaitAction : public eCharacterAction {
public:
    eWaitAction(eCharacter* const c);

    void increment(const int by) override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;

    void setTime(const int t);
private:
    int mRemTime{__INT_MAX__};
};

#endif // EWAITACTION_H
