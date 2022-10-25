#ifndef EGODATTACKEVENT_H
#define EGODATTACKEVENT_H

#include "egameevent.h"
#include "characters/gods/egod.h"

class eGodAttackEvent : public eGameEvent {
public:
    eGodAttackEvent(eGameBoard& board);

    const std::vector<eGodType>& types() const { return mTypes; }
    void setTypes(const std::vector<eGodType>& types);

    void trigger() override;

    void write(eWriteStream& dst) const override ;
    void read(eReadStream& src) override;
private:
    std::vector<eGodType> mTypes;
};


#endif // EGODATTACKEVENT_H
