#include "emessagebox.h"

#include "elabel.h"
#include "eframedlabel.h"
#include "eframedwidget.h"
#include "eokbutton.h"
#include "eexclamationbutton.h"

#include <stdexcept>

template<typename ... Args>
std::string string_format(const std::string& format, Args... args) {
    const int size_s = std::snprintf(nullptr, 0, format.c_str(), args...) + 1; // Extra space for '\0'
    if(size_s <= 0) { throw std::runtime_error("Error during formatting."); }
    const auto size = static_cast<size_t>(size_s);
    const auto buf = std::make_unique<char[]>(size);
    std::snprintf(buf.get(), size, format.c_str(), args...);
    return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

void replaceAll(std::string& source, const std::string& from, const std::string& to) {
    std::string newString;
    newString.reserve(source.length());  // avoids a few memory allocations

    std::string::size_type lastPos = 0;
    std::string::size_type findPos;

    while(std::string::npos != (findPos = source.find(from, lastPos)))
    {
        newString.append(source, lastPos, findPos - lastPos);
        newString += to;
        lastPos = findPos + from.length();
    }

    // Care for the rest after last occurrence
    newString += source.substr(lastPos);

    source.swap(newString);
}

void eMessageBox::initialize(const eAction& viewTile,
                             const eDate& date,
                             eMessage msg,
                             const std::string& name) {
    setType(eFrameType::message);

    const int p = padding();

    const auto w = new eWidget(window());
    w->setHeight(p);
    addWidget(w);

    const auto w0 = new eWidget(window());
    w0->setNoPadding();
    const auto d = new eLabel(date.shortString(), window());
    d->setSmallFontSize();
    d->fitContent();
    w0->addWidget(d);
    const auto title = new eLabel(msg.fTitle, window());
    title->setHugeFontSize();
    title->fitContent();
    w0->addWidget(title);
    w0->fitContent();
    w0->setWidth(width() - 2*p);
    title->align(eAlignment::hcenter);
    addWidget(w0);

    const auto ww = new eFramedWidget(window());
    ww->setType(eFrameType::inner);
    ww->setNoPadding();

    if(viewTile) {
        const auto www = new eWidget(window());
        www->setNoPadding();
        const auto butt = new eExclamationButton(window());
        butt->setPressAction(viewTile);
        www->addWidget(butt);
        const auto l = new eLabel("Go to site of event", window());
        l->setSmallFontSize();
        l->fitContent();
        www->addWidget(l);
        www->stackHorizontally();
        www->fitContent();
        butt->align(eAlignment::vcenter);
        addWidget(www);
        www->setX(3*p);
    }

    const auto text = new eLabel(window());
    text->setSmallFontSize();
    text->setWrapWidth(width() - 4*p);
    replaceAll(msg.fText, "[player_name]", name);
    text->setText(msg.fText);
    text->fitContent();

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
    ok->setX(ok->x() - 2*p);
    ok->setY(ok->y() - 2*p);
    w0->align(eAlignment::hcenter);
    ww->align(eAlignment::hcenter);
}
