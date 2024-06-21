#ifndef EGODMISSILE_H
#define EGODMISSILE_H

#include "emissile.h"

class eGodMissile : public eMissile {
public:
    eGodMissile(eGameBoard& board,
                const std::vector<ePathPoint>& path = {});

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;

    void setTexture(const eCharacterType ct,
                    const eCharacterActionType cat);

    void read(eReadStream& src);
    void write(eWriteStream& dst) const;
private:
    eCharacterType mCharType;
    eCharacterActionType mActionType;
};

#endif // EGODMISSILE_H
