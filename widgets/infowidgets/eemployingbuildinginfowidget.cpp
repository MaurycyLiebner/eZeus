#include "eemployingbuildinginfowidget.h"

#include "buildings/eemployingbuilding.h"

#include "widgets/elabel.h"

#include "elanguage.h"

void eEmployingBuildingInfoWidget::initialize(const std::string& title,
                                              eEmployingBuilding* const b) {
    eInfoWidget::initialize(title);

    const auto p = padding();

    const auto wid = addFramedWidget(8*p);
    const int e = b->employed();
    const int me = b->maxEmployees();
    const auto estr = std::to_string(e);
    const auto mestr = std::to_string(me);
    const auto emplstr = eLanguage::text("employees");
    const auto memplstr = eLanguage::text("needed");
    const auto str = estr + " " + emplstr +
                     "  (" + mestr + " " + memplstr +  ")";
    const auto empl = new eLabel(str, window());
    empl->setSmallFontSize();
    empl->fitContent();
    wid->addWidget(empl);
    empl->align(eAlignment::hcenter);
    empl->setY(p);
}
