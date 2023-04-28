#ifndef ECITYBUTTON_H
#define ECITYBUTTON_H

#include "eframedbutton.h"

#include "engine/eworldcity.h"

class eGameBoard;

class eCityButton : public eFramedButton {
public:
    using eFramedButton::eFramedButton;

    using eCityAction = std::function<void(const stdsptr<eWorldCity>&)>;
    void initialize(eGameBoard& board, const eCityAction& cact);

    const stdsptr<eWorldCity>& city() const { return mCity; }
    void setCity(const stdsptr<eWorldCity>& c);
private:
    stdsptr<eWorldCity> mCity;
};

#endif // ECITYBUTTON_H
