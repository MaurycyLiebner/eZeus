#include "efilewidget.h"

#include "emainwindow.h"

#include "eacceptbutton.h"
#include "ecancelbutton.h"

#include "escrollwidget.h"
#include "escrollbar.h"

#include "elineedit.h"

#include <string>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

void eFileWidget::intialize(const std::string& title,
                            const std::string& folder,
                            const eFileFunc& func,
                            const eAction& closeAction) {
    mFolder = folder;

    setType(eFrameType::message);

    const int p = padding();
    const auto res = window()->resolution();
    const int ww = res.centralWidgetSmallWidth();
    const int hh = res.centralWidgetSmallHeight();

    resize(ww, hh);

    mTitleLabel = new eLabel(title, window());
    mTitleLabel->fitContent();
    addWidget(mTitleLabel);
    mTitleLabel->align(eAlignment::top | eAlignment::hcenter);
    mTitleLabel->setY(mTitleLabel->y() + p);

    mOk = new eAcceptButton(window());
    addWidget(mOk);
    mOk->align(eAlignment::bottom | eAlignment::right);
    mOk->move(mOk->x() - 2*p, mOk->y() - 2*p);
    mOk->setPressAction([this, func, closeAction] {
        const auto path = filePath();
        const bool r = func(path);
        if(r) closeAction();
    });

    mCancel = new eCancelButton(window());
    addWidget(mCancel);
    mCancel->align(eAlignment::bottom | eAlignment::left);
    mCancel->move(mCancel->x() + 2*p, mCancel->y() - 2*p);
    mCancel->setPressAction(closeAction);

    const auto lineW = new eFramedWidget(window());
    lineW->setType(eFrameType::inner);
    lineW->setNoPadding();
    mLineEdit = new eLineEdit(window());
    mLineEdit->setTinyPadding();
    mLineEdit->setText("A");
    mLineEdit->fitContent();
    mLineEdit->setText("");
    lineW->addWidget(mLineEdit);
    mLineEdit->setX(p);
    const int lineY = mTitleLabel->y() + mTitleLabel->height() + p;
    lineW->setY(lineY);
    lineW->setX(2*p);
    addWidget(lineW);

    const auto scrollCont = new eWidget(window());
    addWidget(scrollCont);
    scrollCont->resize(ww - 4*p, hh - lineY - mLineEdit->height() - 10*p);
    scrollCont->setY(lineY + mLineEdit->height() + 2*p);
    scrollCont->setX(2*p);

    const auto sb = new eScrollBar(window());
    sb->initialize(scrollCont->height());
    scrollCont->addWidget(sb);

    const int swwidth = scrollCont->width() - sb->width() - p;

    mLineEdit->resize(swwidth - 2*p, mLineEdit->height());
    lineW->resize(swwidth, mLineEdit->height());

    const auto filesWidget = new eWidget(window());

    int y = 0;
    for(const auto & entry : fs::directory_iterator(folder)) {
        const auto path = entry.path();
        const auto name = entry.path().filename().stem();
        const auto b = new eButton(name, window());
        b->setUnderline(false);
        b->setDarkFontColor();
        b->setMouseEnterAction([b]() {
            b->setLightFontColor();
        });
        b->setMouseLeaveAction([b]() {
            b->setDarkFontColor();
        });
        b->setTextAlignment(eAlignment::left | eAlignment::vcenter);
        b->setNoPadding();
        b->fitContent();
        b->setWidth(swwidth);
        filesWidget->addWidget(b);
        b->setY(y);
        y += b->height();
        b->setPressAction([this, name]() {
            setFileName(name);
        });
    }
    filesWidget->setNoPadding();
    filesWidget->fitContent();

    const auto swww = new eFramedWidget(window());
    swww->setNoPadding();
    swww->setType(eFrameType::inner);
    const auto sw = new eScrollWidget(window());
    swww->addWidget(sw);
    sw->resize(swwidth - 2*p, scrollCont->height() - 2*p);
    sw->move(p, p);
    swww->resize(swwidth, scrollCont->height());
    sw->setScrollArea(filesWidget);
    sb->setScrollWidget(sw);
    scrollCont->addWidget(swww);

    sb->align(eAlignment::right);
}

void eFileWidget::setFileName(const std::string& path) {
    mLineEdit->setText(path);
}

std::string eFileWidget::filePath() const {
    return mFolder + mLineEdit->text() + ".ez";
}
