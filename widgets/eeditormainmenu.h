#ifndef EEDITORMAINMENU_H
#define EEDITORMAINMENU_H

#include "emainmenubase.h"

#include "engine/ecampaign.h"

class eEditorMainMenu : public eMainMenuBase {
public:
    using eMainMenuBase::eMainMenuBase;
    void initialize(const stdsptr<eCampaign>& campaign);
private:
    void addGoBackButton(eWidget* const to);

    stdsptr<eCampaign> mCampaign;
};

#endif // EEDITORMAINMENU_H
