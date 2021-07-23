#ifndef ECOMBOBOX_H
#define ECOMBOBOX_H

#include "ebutton.h"

class eComboBox : public eButton {
public:
    eComboBox(SDL_Renderer* const renderer);

    using eCurrentAction = std::function<void(const std::string&)>;
    void setCurrentChangedAction(const eCurrentAction& a);

    bool setCurrentIndex(const int id);
    void addAction(const std::string& a);
private:
    eCurrentAction mCurrentAction;
    std::vector<std::string> mActions;
};

#endif // ECOMBOBOX_H
