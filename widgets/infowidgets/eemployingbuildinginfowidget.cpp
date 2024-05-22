#include "eemployingbuildinginfowidget.h"

#include "buildings/eemployingbuilding.h"

#include "widgets/elabel.h"

#include "elanguage.h"

void eEmployingBuildingInfoWidget::initialize(
        const std::string& title,
        eEmployingBuilding* const b) {
    eInfoWidget::initialize(title);
    addCentralWidget();
    addEmploymentWidget(b);
}

void eEmployingBuildingInfoWidget::initialize(
        const std::string& title,
        const std::string& info,
        const std::string& text,
        eEmployingBuilding* const b,
        const std::string& subText) {
    eInfoWidget::initialize(title);
    if(!info.empty()) addText(info);
    if(!text.empty()) addText(text);
    addEmploymentWidget(b);
    if(!subText.empty()) addText(subText);
}

void eEmployingBuildingInfoWidget::addEmploymentWidget(eEmployingBuilding* const b) {
    const int p = padding();

    const auto wid = addFramedWidget(8*p);
    const int e = b->employed();
    const int me = b->maxEmployees();
    const auto estr = std::to_string(e);
    const auto mestr = std::to_string(me);
    const auto emplstr = eLanguage::zeusText(8, 13);
    const auto memplstr = eLanguage::zeusText(69, 0);
    const auto str = estr + " " + emplstr +
                     "  (" + mestr + " " + memplstr;
    const auto empl = new eLabel(str, window());
    empl->setSmallFontSize();
    empl->setSmallPadding();
    empl->fitContent();
    wid->addWidget(empl);
    empl->align(eAlignment::hcenter);
}
