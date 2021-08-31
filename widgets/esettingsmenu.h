#ifndef ESETTINGSMENU_H
#define ESETTINGSMENU_H

#include "emainmenubase.h"
#include "eresolution.h"

struct eSettings {
    int width() const {
        return eResolution::width(fRes);
    }

    int height() const {
        return eResolution::height(fRes);
    }

    bool fFullscreen;
    eRes fRes;
};

inline bool operator==(const eSettings& s0, const eSettings& s1) {
    if(s0.width() != s1.width()) return false;
    if(s0.height() != s1.height()) return false;
    if(s0.fFullscreen != s1.fFullscreen) return false;
    return true;
}

class eSettingsMenu : public eMainMenuBase {
public:
    eSettingsMenu(const eSettings& iniSettings,
                  eMainWindow* const window);

    using eApplyAction = std::function<void(const eSettings&)>;
    void initialize(const eAction& backA,
                    const eApplyAction& settingsA);

private:
    const eSettings mIniSettings;
    eSettings mSettings;
};

#endif // ESETTINGSMENU_H
