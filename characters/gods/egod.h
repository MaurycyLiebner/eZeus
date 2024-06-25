#ifndef EGOD_H
#define EGOD_H

#include "characters/echaracter.h"

#include "textures/egametextures.h"

enum class eGodType {
    aphrodite,
    apollo,
    ares,
    artemis,
    athena,
    atlas,
    demeter,
    dionysus,
    hades,
    hephaestus,
    hera,
    hermes,
    poseidon,
    zeus
};

enum class eGodQuestId {
    godQuest1,
    godQuest2
};

enum class eGodAttitude {
    friendly,
    hostile,
    worshipped
};

class eGod : public eCharacter {
public:
    eGod(eGameBoard& board, const eGodType gt);

    static eGodType sCharacterToGodType(const eCharacterType type,
                                        bool* const valid = nullptr);
    static eCharacterType sGodToCharacterType(const eGodType type);
    static stdsptr<eGod> sCreateGod(const eGodType type, eGameBoard& board);

    using eTexPtr = eTextureCollection eDestructionTextures::*;
    static eTexPtr sGodMissile(const eGodType gt);

    static eGodType sFightWinner(const eGodType g1, const eGodType g2);
    static std::string sFightResultString(const eGodType g1, const eGodType g2);

    static int sGodAttackTime(const eGodType gt);
    static int sGodBlessTime(const eGodType gt);
    static int sGodAppearTime(const eGodType gt);

    static bool sTarget(const eGodType gt, const eBuildingType bt);

    static std::string sGodName(const eGodType gt);

    static void sGodStrings(std::vector<eGodType>& gods,
                            std::vector<std::string>& godNames);

    eGodType type() const { return mType; }

    eGodAttitude attitude() const { return mAttitude; }
    void setAttitude(const eGodAttitude attitude) { mAttitude = attitude; }

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
private:
    const eGodType mType;
    eGodAttitude mAttitude = eGodAttitude::friendly;
};

#endif // EGOD_H
