#include "emessagebox.h"

#include "elabel.h"
#include "eframedlabel.h"
#include "eframedwidget.h"
#include "eokbutton.h"
#include "eexclamationbutton.h"
#include "eframedbutton.h"

#include <stdexcept>

#include "elanguage.h"

#include "estringhelpers.h"
#include "engine/eworldcity.h"
#include "widgets/egamewidget.h"

template<typename ... Args>
std::string string_format(const std::string& format, Args... args) {
    const int size_s = std::snprintf(nullptr, 0, format.c_str(), args...) + 1; // Extra space for '\0'
    if(size_s <= 0) { throw std::runtime_error("Error during formatting."); }
    const auto size = static_cast<size_t>(size_s);
    const auto buf = std::make_unique<char[]>(size);
    std::snprintf(buf.get(), size, format.c_str(), args...);
    return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

void eMessageBox::initialize(const eEventData& ed,
                             const eAction& viewTile,
                             eMessage msg) {
    setType(eFrameType::message);

    const int p = padding();

    const auto w0 = new eWidget(window());
    {
        w0->setNoPadding();
        if(ed.fCity) {
            eStringHelpers::replaceAll(msg.fTitle, "[city_name]",
                                       ed.fCity->name());
        }
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
        const auto str = ed.fDate.shortString() +
                         "     " + to + " " + ed.fPlayerName;
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
    eStringHelpers::replaceAll(msg.fText, "[greeting]",
                               eLanguage::text("greetings"));
    eStringHelpers::replaceAll(msg.fText, "[player_name]",
                               ed.fPlayerName);
    if(ed.fCity) {
        eStringHelpers::replaceAll(msg.fText, "[city_name]",
                                   ed.fCity->name());
        eStringHelpers::replaceAll(msg.fText, "[leader_name]",
                                   ed.fCity->leader());
        eStringHelpers::replaceAll(msg.fText, "[a_foreign_army]",
                                   eLanguage::text("an_army"));
    }
    text->setText(msg.fText);
    text->fitContent();
    text->setX(p);

    ww->addWidget(text);
    ww->stackVertically();
    ww->fitContent();
    addWidget(ww);

    eOkButton* ok = nullptr;
    eWidget* wid = nullptr;
    if(ed.fType == eMessageEventType::common) {
        ok = new eOkButton(window());
        ok->setPressAction([this]() {
            deleteLater();
        });
        addWidget(ok);
    } else if(ed.fType == eMessageEventType::invasion) {
        wid = new eWidget(window());

        const auto surrenderB = new eFramedButton(window());
        surrenderB->setSmallFontSize();
        surrenderB->setUnderline(false);
        surrenderB->setText(eLanguage::text("surrender"));
        surrenderB->fitContent();
        wid->addWidget(surrenderB);
        surrenderB->setPressAction([this, ed]() {
            if(ed.fA0) ed.fA0();
            deleteLater();
        });
        surrenderB->setVisible(bool(ed.fA0));

        const auto bribeB = new eFramedButton(window());
        bribeB->setSmallFontSize();
        bribeB->setUnderline(false);
        bribeB->setText(eLanguage::text("bribe") + " " +
                        std::to_string(ed.fBribe) + " " +
                        eLanguage::text("drachmas"));
        bribeB->fitContent();
        wid->addWidget(bribeB);
        bribeB->setPressAction([this, ed]() {
            if(ed.fA1) ed.fA1();
            deleteLater();
        });
        bribeB->setVisible(bool(ed.fA1));

        const auto fightToDefend = new eFramedButton(window());
        fightToDefend->setSmallFontSize();
        fightToDefend->setUnderline(false);
        fightToDefend->setText(eLanguage::text("fight_to_defend"));
        fightToDefend->fitContent();
        wid->addWidget(fightToDefend);
        fightToDefend->setPressAction([this, ed]() {
            if(ed.fA2) ed.fA2();
            deleteLater();
        });

        wid->setWidth(width() - 8*p);
        wid->layoutHorizontally();
        wid->fitContent();
        surrenderB->align(eAlignment::vcenter);
        bribeB->align(eAlignment::vcenter);
        fightToDefend->align(eAlignment::vcenter);

        addWidget(wid);
    }

    stackVertically();

    fitContent();

    if(ok) {
        ok->align(eAlignment::right | eAlignment::bottom);
        ok->setX(ok->x() - 1.5*p);
        ok->setY(ok->y() - 1.5*p);
    }
    if(wid) {
        wid->align(eAlignment::hcenter);
    }
    w0->align(eAlignment::hcenter);
    ww->align(eAlignment::hcenter);
}

bool eMessageBox::mousePressEvent(const eMouseEvent& e) {
    (void)e;
    return true;
}
