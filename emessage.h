#ifndef EMESSAGE_H
#define EMESSAGE_H

#include <memory>
#include <string>

struct eMessage {
    std::string fTitle;
    std::string fText;
};

struct eMessageType {
    eMessage fFull;
    eMessage fCondensed;
};

struct eEventMessageType : public eMessageType {
    std::string fReason;
    std::string fNoReason;
};

struct eConsequenceMessageType : public eMessageType {
    std::string fNoReason;
};

struct eGameMessages {
    eMessageType fBegin;
    eMessageType fNoPart;
    eMessageType fWon;
    eMessageType fLost;
    eMessageType fSecond;
};

#endif // EMESSAGE_H
