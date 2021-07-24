#ifndef ESETTINGSMENU_H
#define ESETTINGSMENU_H

#include "ewidget.h"
#include "eresolution.h"

struct eSettings {
    int width() const {
        return fRes.width();
    }

    int height() const {
        return fRes.height();
    }

    eResolution fRes;
};

inline bool operator==(const eSettings& s0, const eSettings& s1) {
    if(s0.width() != s1.width()) return false;
    if(s0.height() != s1.height()) return false;
    return true;
}

class eSettingsMenu : public eWidget {
public:
    eSettingsMenu(const eSettings& iniSettings,
                  SDL_Renderer* const renderer);

    using eApplyAction = std::function<void(const eSettings&)>;
    void initialize(const eAction& backA,
                    const eApplyAction& settingsA);

private:
    const eSettings mIniSettings;
    eSettings mSettings;
};

#endif // ESETTINGSMENU_H
