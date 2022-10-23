#ifndef EFILEWIDGET_H
#define EFILEWIDGET_H

#include "eframedwidget.h"

class eLabel;
class eAcceptButton;
class eCancelButton;

class eFileWidget : public eFramedWidget {
public:
    using eFramedWidget::eFramedWidget;

    using eFileFunc = std::function<bool(const std::string&)>;
    void intialize(const std::string& title,
                   const std::string& folder,
                   const eFileFunc& func,
                   const eAction& closeAction);

    void setFilePath(const std::string& path);
    std::string filePath() const;
private:
    eLabel* mTitleLabel = nullptr;
    eAcceptButton* mOk = nullptr;
    eCancelButton* mCancel = nullptr;

    std::string mFilePath;
};

#endif // EFILEWIDGET_H
