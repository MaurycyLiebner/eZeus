#ifndef EINVASIONWARNINGEVENT_H
#define EINVASIONWARNINGEVENT_H

#include "egameevent.h"

enum class eInvasionWarningType {
    warning36,
    warning24,
    warning12,
    warning6,
    warning1
};

class eInvasionWarningEvent : public eGameEvent {
public:
    eInvasionWarningEvent(eGameBoard& board);

    void initialize(const eInvasionWarningType type,
                    const stdsptr<eWorldCity>& city);

    void trigger() override;
    std::string longName() const override;

    void write(eWriteStream& dst) const override ;
    void read(eReadStream& src) override;

    const stdsptr<eWorldCity>& city() const { return mCity; }
    void setCity(const stdsptr<eWorldCity>& c);
private:
    eInvasionWarningType mType;
    stdsptr<eWorldCity> mCity;
};

#endif // EINVASIONWARNINGEVENT_H
