#ifndef ESELECTCOLONYWIDGET_H
#define ESELECTCOLONYWIDGET_H

#include "ewidget.h"

class eWorldBoard;
class eWorldCity;
class eColonyEpisode;

class eSelectColonyWidget : public eWidget {
public:
    using eWidget::eWidget;

    using eColonySelection = std::vector<eColonyEpisode*>;
    using eCitySelected = std::function<void(const std::shared_ptr<eWorldCity>)>;
    void initialize(const eColonySelection& sel,
                    const eCitySelected& s,
                    eWorldBoard* const board);
};

#endif // ESELECTCOLONYWIDGET_H
