#ifndef ESETTINGSMENU_H
#define ESETTINGSMENU_H

#include "ewidget.h"

class eSettingsMenu : public eWidget {
public:
    eSettingsMenu(SDL_Renderer* const renderer);

    void initialize();
};

#endif // ESETTINGSMENU_H
