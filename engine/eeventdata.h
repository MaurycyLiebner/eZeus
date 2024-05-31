#ifndef EEVENTDATA_H
#define EEVENTDATA_H

#include "edate.h"
#include "eresourcetype.h"
#include "emessageeventtype.h"

using eAction = std::function<void()>;
using eCloseOnAction = std::function<void(const eAction&)>;

enum class eGodType;
enum class eHeroType;
enum class eGodQuestId;
enum class eMonsterType;

struct eEventData {
    eMessageEventType fType = eMessageEventType::common;
    eDate fDate;
    std::string fPlayerName;
    eTile* fTile = nullptr;
    stdptr<eCharacter> fChar;
    int fBribe = 0;
    eCloseOnAction fCA0 = nullptr;
    eAction fA0 = nullptr;
    std::string fA0Key;
    eAction fA1 = nullptr;
    std::string fA1Key;
    eAction fA2 = nullptr;
    std::string fA2Key;
    stdsptr<eWorldCity> fCity;
    stdsptr<eWorldCity> fRivalCity;
    eResourceType fResourceType = eResourceType::drachmas;
    int fResourceCount = 0;
    int fSpaceCount = 0;
    int fTime = 0;
    std::string fReason;
    eGodType fGod;
    eGodQuestId fQuestId;
    eHeroType fHero;
    eMonsterType fMonster;
};

#endif // EEVENTDATA_H
