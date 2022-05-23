#ifndef EWORLDMAPWIDGET_H
#define EWORLDMAPWIDGET_H

#include "elabel.h"

class eWorldMapWidget : public eLabel {
public:
    eWorldMapWidget(eMainWindow* const window);

    void initialize();
};

#endif // EWORLDMAPWIDGET_H
