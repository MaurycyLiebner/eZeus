#ifndef EEARTQUAKEEVENTWIDGET_H
#define EEARTQUAKEEVENTWIDGET_H

#include "../ewidget.h"

class eEarthquakeEvent;

class eEartquakeEventWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize(eEarthquakeEvent* const e);
};

#endif // EEARTQUAKEEVENTWIDGET_H
