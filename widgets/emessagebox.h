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
                    const eAction& closeFunc,
                    eMessage msg);

    void close();
    bool closable() const { return mClosable; }

    eWidget* createTributeWidget(const eResourceType type,
                                 const int count, const int space);
protected:
    bool keyPressEvent(const eKeyPressEvent& e);
    bool mousePressEvent(const eMouseEvent& e);
private:
    bool mClosable = false;
    eAction mCloseFunc;
};

#endif // EMESSAGEBOX_H
