#include "esciencedatawidget.h"

void eScienceDataWidget::initialize() {

}

void eScienceDataWidget::updateCoverage() {

}

void eScienceDataWidget::paintEvent(ePainter& p) {
    const bool update = ((mTime++) % 20) == 0;
    if(update) {
        updateCoverage();
    }
    eWidget::paintEvent(p);
}
