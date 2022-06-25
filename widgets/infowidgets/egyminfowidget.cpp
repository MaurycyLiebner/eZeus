#include "egyminfowidget.h"

#include "elanguage.h"

eGymInfoWidget::eGymInfoWidget(eMainWindow* const window) :
    eEmployingBuildingInfoWidget(window, true, true) {}

void eGymInfoWidget::initialize() {
    const auto title = eLanguage::text("gymnasium");
    eInfoWidget::initialize(title);
}
