#include "eemployingbuildinginfowidget.h"

#include "buildings/eemployingbuilding.h"

#include "widgets/elabel.h"

#include "elanguage.h"

void eEmployingBuildingInfoWidget::initialize(const std::string& title,
                                              eEmployingBuilding* const b) {
    eInfoWidget::initialize(title);

    const auto cw = centralWidget();
    const auto p = padding();

    const int h = 8*p;

    cw->setHeight(cw->height() - h - p);

    const auto wid = new eFramedWidget(window());
    wid->setType(eFrameType::inner);
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
    wid->fitContent();
    addWidget(wid);
    wid->resize(cw->width(), h);
    wid->move(cw->x(), cw->y() + cw->height() + p);
    empl->align(eAlignment::hcenter);
    empl->setY(p);
}
