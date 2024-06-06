#ifndef ECATTLE_H
#define ECATTLE_H

#include "echaracter.h"

class eCattle : public eCharacter {
public:
    eCattle(eGameBoard& board, const eCharacterType type);

    std::shared_ptr<eTexture>
    getTexture(const eTileSize size) const override;

    void incTime(const int by) override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
private:
    bool mature();

    int mMatureWait = 0;
};

#endif // ECATTLE_H
