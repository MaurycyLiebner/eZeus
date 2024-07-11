#ifndef EROSTEROFLEADERS_H
#define EROSTEROFLEADERS_H

#include "emainmenubase.h"

class eRosterOfLeaders : public eMainMenuBase {
public:
    using eMainMenuBase::eMainMenuBase;

    using eLeaderSelectedAction = std::function<void(std::string)>;
    void initialize();

    static std::vector<std::string> sLeaders();
private:
    eLeaderSelectedAction mAction;
};

#endif // EROSTEROFLEADERS_H
