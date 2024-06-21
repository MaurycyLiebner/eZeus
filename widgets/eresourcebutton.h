#ifndef ERESOURCEBUTTON_H
#define ERESOURCEBUTTON_H

#include "eframedbutton.h"

#include "engine/eresourcetype.h"

class eResourceButton : public eFramedButton {
public:
    using eFramedButton::eFramedButton;

    using eResourceAction = std::function<void(const eResourceType)>;
    void initialize(const eResourceAction& ract,
                    const bool drachmas = false);

    eResourceType resource() const { return mRes; }
    void setResource(const eResourceType res);
private:
    eResourceType mRes;
};

#endif // ERESOURCEBUTTON_H
