#ifndef EREGROWFORESTACTION_H
#define EREGROWFORESTACTION_H

#include "eplannedaction.h"

class eTile;

class eRegrowForestAction : public ePlannedAction {
public:
    eRegrowForestAction(eTile* const tile);
    eRegrowForestAction();

    void trigger(eGameBoard& board) override;

    void read(eReadStream& src, eGameBoard& board) override;
    void write(eWriteStream& dst) const override;
private:
    eTile* mTile = nullptr;
};

#endif // EREGROWFORESTACTION_H
