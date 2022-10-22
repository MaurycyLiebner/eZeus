#include "egyminfowidget.h"

#include "elanguage.h"

#include "buildings/egymnasium.h"

eGymInfoWidget::eGymInfoWidget(eMainWindow* const window) :
    eEmployingBuildingInfoWidget(window, true, true) {}

void eGymInfoWidget::initialize(eGymnasium* const gym) {
    const auto title = eLanguage::text("gymnasium");
    eInfoWidget::initialize(title);
    addCentralWidget();
    addEmploymentWidget(gym);
}
