#ifndef EFRAMEDBUTTONWITHICON_H
#define EFRAMEDBUTTONWITHICON_H

#include "eframedbutton.h"

enum class eResourceType;

class eFramedButtonWithIcon : public eFramedButton {
public:
    using eFramedButton::eFramedButton;

    void initialize(const std::shared_ptr<eTexture>& icon,
                    const std::string& text);

    void initialize(const eResourceType type,
                    const std::string& text);
};

#endif // EFRAMEDBUTTONWITHICON_H
