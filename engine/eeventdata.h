#ifndef EEVENTDATA_H
#define EEVENTDATA_H

#include "edate.h"
#include "eresourcetype.h"
#include "emessageeventtype.h"

using eAction = std::function<void()>;

struct eEventData {
    eMessageEventType fType = eMessageEventType::common;
    eDate fDate;
    std::string fPlayerName;
    eTile* fTile = nullptr;
    int fBribe = 0;
    eAction fA0 = nullptr;
    std::string fA0Key;
    eAction fA1 = nullptr;
    std::string fA1Key;
    eAction fA2 = nullptr;
    std::string fA2Key;
    stdsptr<eWorldCity> fCity;
    eResourceType fResourceType;
    int fResourceCount = 0;
    int fSpaceCount = 0;
    int fTime = 0;
    std::string fReason;
};

#endif // EEVENTDATA_H
