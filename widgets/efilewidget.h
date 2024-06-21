#ifndef EFILEWIDGET_H
#define EFILEWIDGET_H

#include "eframedwidget.h"

class eLabel;
class eAcceptButton;
class eCancelButton;
class eLineEdit;

class eFileWidget : public eFramedWidget {
public:
    using eFramedWidget::eFramedWidget;

    using eFileFunc = std::function<bool(const std::string&)>;
    void intialize(const std::string& title,
                   const std::string& folder,
                   const eFileFunc& func,
                   const eAction& closeAction);

    void setFileName(const std::string& path);
    std::string filePath() const;
private:
    eLabel* mTitleLabel = nullptr;
    eAcceptButton* mOk = nullptr;
    eCancelButton* mCancel = nullptr;
    eLineEdit* mLineEdit = nullptr;

    std::string mFolder;
};

#endif // EFILEWIDGET_H
