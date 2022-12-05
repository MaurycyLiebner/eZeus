#ifndef EMESSAGEBOX_H
#define EMESSAGEBOX_H

#include "eframedwidget.h"

#include "emessage.h"
#include "engine/edate.h"

class eWorldCity;
struct eEventData;
enum class eResourceType;

class eMessageBox : public eFramedWidget {
public:
    using eFramedWidget::eFramedWidget;

    void initialize(const eEventData& ed,
                    const eAction& viewTile,
                    const eAction& close,
                    eMessage msg);

    eWidget* createTributeWidget(const eResourceType type,
                                 const int count, const int space);
protected:
    bool mousePressEvent(const eMouseEvent& e);
};

#endif // EMESSAGEBOX_H
