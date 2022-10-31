#include "emessagebox.h"

#include "elabel.h"
#include "eframedlabel.h"
#include "eframedwidget.h"
#include "eokbutton.h"
#include "eexclamationbutton.h"

#include <stdexcept>

#include "elanguage.h"

#include "estringhelpers.h"

template<typename ... Args>
std::string string_format(const std::string& format, Args... args) {
    const int size_s = std::snprintf(nullptr, 0, format.c_str(), args...) + 1; // Extra space for '\0'
    if(size_s <= 0) { throw std::runtime_error("Error during formatting."); }
    const auto size = static_cast<size_t>(size_s);
    const auto buf = std::make_unique<char[]>(size);
    std::snprintf(buf.get(), size, format.c_str(), args...);
    return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

void eMessageBox::initialize(const eAction& viewTile,
                             const eDate& date,
                             eMessage msg,
                             const std::string& name) {
    setType(eFrameType::message);

    const int p = padding();

    const auto w0 = new eWidget(window());
    {
        w0->setNoPadding();
        const auto title = new eLabel(msg.fTitle, window());
        title->setHugeFontSize();
        title->fitContent();
        w0->addWidget(title);
        w0->fitContent();
        w0->setWidth(width() - 2*p);
        title->align(eAlignment::hcenter);
        addWidget(w0);
    }

    const auto ww = new eFramedWidget(window());
    ww->setType(eFrameType::inner);
    ww->setSmallPadding();

    {
        const auto to = eLanguage::text("message_to");
        const auto str = date.shortString() + "     " + to + " " + name;
        const auto d = new eLabel(str, window());
        d->setSmallFontSize();
        d->fitContent();
        ww->addWidget(d);
        d->setX(p);
    }

    if(viewTile) {
        const auto www = new eWidget(window());
        www->setNoPadding();
        const auto butt = new eExclamationButton(window());
        butt->setPressAction(viewTile);
        www->addWidget(butt);
        const auto go = eLanguage::text("go_to_site");
        const auto l = new eLabel(go, window());
        l->setSmallFontSize();
        l->fitContent();
        www->addWidget(l);
        www->stackHorizontally();
        www->fitContent();
        butt->align(eAlignment::vcenter);
        ww->addWidget(www);
        www->setX(3*p);
    }

    const auto text = new eLabel(window());
    text->setSmallFontSize();
    text->setWrapWidth(width() - 8*p);
    eStringHelpers::replaceAll(msg.fText, "[player_name]", name);
    text->setText(msg.fText);
    text->fitContent();
    text->setX(p);

    ww->addWidget(text);
    ww->stackVertically();
    ww->fitContent();
    addWidget(ww);

    const auto ok = new eOkButton(window());
    ok->setPressAction([this]() {
        deleteLater();
    });
    addWidget(ok);

    stackVertically();

    fitContent();

    ok->align(eAlignment::right | eAlignment::bottom);
    ok->setX(ok->x() - 1.5*p);
    ok->setY(ok->y() - 1.5*p);
    w0->align(eAlignment::hcenter);
    ww->align(eAlignment::hcenter);
}
