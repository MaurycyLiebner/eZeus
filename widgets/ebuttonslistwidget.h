#ifndef EBUTTONSLISTWIDGET_H
#define EBUTTONSLISTWIDGET_H

#include "ewidget.h"

class eLabel;
class eFramedButton;
class eCancelButton;

class eListButton : public eWidget {
public:
    using eWidget::eWidget;

    void initialize(const std::string& text,
                    const int id);

    int id() const { return mId; }
    void setId(const int id);

    void setText(const std::string& text);

    using eCloseAction = std::function<void(int)>;
    void setCloseAction(const eCloseAction& ca);
    using ePressAction = std::function<void(int)>;
    void setPressAction(const ePressAction& pa);

    void fitToWidth(const int w);
private:
    eLabel* mIdLabel = nullptr;
    eFramedButton* mButton = nullptr;
    eCancelButton* mCloseButton = nullptr;

    eCloseAction mCloseAction;
    ePressAction mPressAction;
    int mId = -1;
};

class eButtonsListWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize();

    using eButtonPressedEvent = std::function<void(int)>;
    void setButtonPressEvent(const eButtonPressedEvent& e);
    using eButtonCreateEvent = std::function<void()>;
    void setButtonCreateEvent(const eButtonCreateEvent& e);
    using eButtonRemoveEvent = std::function<void(int)>;
    void setButtonRemoveEvent(const eButtonRemoveEvent& e);

    void setText(const int id, const std::string& text);
    int addButton(const std::string& text);
    void removeButton(const int id);
private:
    void updateButtons();

    eButtonPressedEvent mPressE;
    eButtonCreateEvent mCreateE;
    eButtonRemoveEvent mRemoveE;

    std::vector<eListButton*> mButtons;
    eFramedButton* mNewButton = nullptr;
};

#endif // EBUTTONSLISTWIDGET_H
