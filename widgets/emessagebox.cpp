#include "emessagebox.h"

#include "elabel.h"
#include "eframedlabel.h"
#include "eokbutton.h"

template<typename ... Args>
std::string string_format(const std::string& format, Args... args) {
    const int size_s = std::snprintf(nullptr, 0, format.c_str(), args...) + 1; // Extra space for '\0'
    if(size_s <= 0) { throw std::runtime_error("Error during formatting."); }
    const auto size = static_cast<size_t>(size_s);
    const auto buf = std::make_unique<char[]>(size);
    std::snprintf(buf.get(), size, format.c_str(), args...);
    return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

void eMessageBox::initialize(const std::shared_ptr<eMessage>& msg,
                             const std::string& name) {
    setType(eFrameType::message);

    const int p = padding();

    const auto w = new eWidget(window());
    w->setHeight(p);
    addWidget(w);

    const auto title = new eLabel(msg->fTitle, window());
    title->setHugeFontSize();
    title->fitContent();
    addWidget(title);

    const auto text = new eFramedLabel(window());
    text->setSmallFontSize();
    text->setType(eFrameType::inner);
    text->setWrapWidth(width() - 4*p);
    const auto txt = string_format(msg->fText, name.c_str());
    text->setText(txt);
    text->fitContent();
    addWidget(text);

    const auto ok = new eOkButton(window());
    ok->setPressAction([this]() {
        deleteLater();
    });
    addWidget(ok);
    ok->align(eAlignment::right);

    stackVertically();

    fitContent();

    title->align(eAlignment::hcenter);
    text->align(eAlignment::hcenter);
}
