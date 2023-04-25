#ifndef ESCROLLBUTTONSLIST_H
#define ESCROLLBUTTONSLIST_H

#include "eframedwidget.h"

#include "ebuttonslistwidget.h"

class eScrollButtonsList : public eFramedWidget {
public:
    using eFramedWidget::eFramedWidget;

    void initialize();

    using eButtonPressedEvent = eButtonsListWidget::eButtonPressedEvent;
    void setButtonPressEvent(const eButtonPressedEvent& e);
    using eButtonCreateEvent = eButtonsListWidget::eButtonCreateEvent;
    void setButtonCreateEvent(const eButtonCreateEvent& e);
    using eButtonRemoveEvent = eButtonsListWidget::eButtonRemoveEvent;
    void setButtonRemoveEvent(const eButtonRemoveEvent& e);

    void setText(const int id, const std::string& text);
    int addButton(const std::string& text);
    void removeButton(const int id);
private:
    void updateWidgetSize();

    eWidget* mSA = nullptr;
    eButtonsListWidget* mBLW = nullptr;
};

#endif // ESCROLLBUTTONSLIST_H
