#include "egyminfowidget.h"

#include "elanguage.h"

void eGymInfoWidget::initialize() {
    const auto title = eLanguage::text("gymnasium");
    eInfoWidget::initialize(title);
}
