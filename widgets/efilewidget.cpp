#include "efilewidget.h"

#include "emainwindow.h"

#include "eacceptbutton.h"
#include "ecancelbutton.h"

#include "escrollwidgetcomplete.h"

#include "elineedit.h"

#include <string>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

template <typename TP>
time_t to_time_t(TP tp) {
    using namespace std::chrono;
    auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now() + system_clock::now());
    return system_clock::to_time_t(sctp);
}

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
    mLineEdit->setSmallFontSize();
    mLineEdit->setText("");
    lineW->addWidget(mLineEdit);
    mLineEdit->setX(p);
    const int lineY = mTitleLabel->y() + mTitleLabel->height() + p;
    lineW->setY(lineY);
    lineW->setX(2*p);
    addWidget(lineW);

    const auto scrollCont = new eScrollWidgetComplete(window());
    addWidget(scrollCont);
    scrollCont->resize(ww - 4*p, hh - lineY - mLineEdit->height() - 10*p);
    scrollCont->setY(lineY + mLineEdit->height() + 2*p);
    scrollCont->setX(2*p);
    scrollCont->initialize();
    const int swwidth = scrollCont->listWidth();

    const auto filesWidget = new eWidget(window());

    std::map<time_t, fs::path> sorted;
    if(std::filesystem::exists(folder)) {
        for(const auto& entry : fs::directory_iterator(folder)) {
            const auto path = entry.path();
            const auto ext = path.extension();
            if(ext != ".ez") continue;
            const auto lwt = fs::last_write_time(path);
            const auto time = to_time_t(lwt);
            sorted[-time] = path;
        }
    }

    int y = 0;
    for(const auto& entry : sorted) {
        const auto path = entry.second;
        const auto name = path.filename().stem();
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

    scrollCont->setScrollArea(filesWidget);

    mLineEdit->resize(swwidth - 2*p, mLineEdit->height());
    lineW->resize(swwidth, mLineEdit->height());

    mLineEdit->grabKeyboard();
}

void eFileWidget::setFileName(const std::string& path) {
    mLineEdit->setText(path);
}

std::string eFileWidget::filePath() const {
    return mFolder + mLineEdit->text() + ".ez";
}
