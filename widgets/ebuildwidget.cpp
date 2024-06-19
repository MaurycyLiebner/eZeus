#include "ebuildwidget.h"

void eBuildWidget::initialize(const std::vector<eBuildButton*>& ws) {
    if(ws.empty()) return;
    const int dim = ws[0]->height();
    const int margin = dim/4;

    int y = 0;
    for(const auto w : ws) {
        addWidget(w);
        w->setY(y);
        y += dim + margin;
    }
    fitContent();
}

void eBuildWidget::exec(const int x, const int y,
                        eWidget* const w) {
    int gx = x;
    int gy = y;
    w->mapToGlobal(gx, gy);
    move(gx, gy);
    w->lastAncestor()->addWidget(this);
}
