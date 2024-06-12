#ifndef ECITYBUTTON_H
#define ECITYBUTTON_H

#include "eframedbutton.h"

#include "engine/eworldcity.h"

class eGameBoard;

class eCityButton : public eFramedButton {
public:
    using eFramedButton::eFramedButton;

    using eCityAction = std::function<void(const stdsptr<eWorldCity>&)>;
    void initialize(eWorldBoard* const board, const eCityAction& cact);

    using eCityValidator = std::function<bool(const stdsptr<eWorldCity>&)>;
    void setValidator(const eCityValidator& v);

    const stdsptr<eWorldCity>& city() const { return mCity; }
    void setCity(const stdsptr<eWorldCity>& c);
private:
    stdsptr<eWorldCity> mCity;
    eCityValidator mValidator;
};

#endif // ECITYBUTTON_H
