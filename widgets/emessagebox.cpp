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
                             const eAction& closeFunc,
                             eMessage msg) {
    mCloseFunc = closeFunc;
    setType(eFrameType::message);

    const int p = padding();

    const auto w0 = new eWidget(window());
    {
        w0->setNoPadding();
        if(const auto& c = ed.fCity) {
            eStringHelpers::replaceAll(msg.fTitle, "[city_name]",
                                       c->name());
        }
        if(const auto& c = ed.fRivalCity) {
            eStringHelpers::replaceAll(msg.fTitle, "[rival_city_name]",
                                       c->name());
        }
        {
            const auto type = ed.fResourceType;
            const auto nameShort = eResourceTypeHelpers::typeName(type);
            eStringHelpers::replaceAll(msg.fTitle, "[itemshort]",
                                       nameShort);
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
        const auto to = eLanguage::zeusText(63, 5); // to
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
        const auto go = eLanguage::zeusText(12, 1); // got to site of event
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
        const auto nat = ed.fCity->nationality();
        const auto natName = eWorldCity::sNationalityName(nat);
        eStringHelpers::replaceAll(msg.fText, "[nationality]",
                                   natName);
        eStringHelpers::replaceAll(msg.fText, "[city_name]",
                                   ed.fCity->name());
        eStringHelpers::replaceAll(msg.fText, "[leader_name]",
                                   ed.fCity->leader());
        eStringHelpers::replaceAll(msg.fText, "[a_foreign_army]",
                                   ed.fCity->anArmy());
        if(ed.fType == eMessageEventType::invasionMessage) {
            eStringHelpers::replaceAll(msg.fText, "[time_until_attack]",
                                      std::to_string(ed.fTime));
        }
    }
    const auto c = ed.fRivalCity ? ed.fRivalCity : ed.fCity;
    if(c) {
        const auto nat = c->nationality();
        const auto natName = eWorldCity::sNationalityName(nat);
        eStringHelpers::replaceAll(msg.fText, "[rival_nationality]",
                                   natName);
        eStringHelpers::replaceAll(msg.fText, "[rival_city_name]",
                                   c->name());
    }

    ww->addWidget(text);
    addWidget(ww);

    eOkButton* ok = nullptr;
    eWidget* wid = nullptr;
    const bool addOk = !ed.fCA0 && !ed.fA0 && !ed.fA1 && !ed.fA2;
    if(addOk) {
        ok = new eOkButton(window());
        ok->setPressAction([this]() {
            close();
        });
        addWidget(ok);
    }
    if(ed.fType == eMessageEventType::invasion) {
        wid = new eWidget(window());
        wid->setNoPadding();

        const auto surrenderB = new eFramedButton(window());
        surrenderB->setSmallFontSize();
        surrenderB->setUnderline(false);
        surrenderB->setText(eLanguage::zeusText(44, 282));
        surrenderB->fitContent();
        wid->addWidget(surrenderB);
        surrenderB->setPressAction([this, ed]() {
            if(ed.fA0) ed.fA0();
            close();
        });
        surrenderB->setVisible(bool(ed.fA0));

        const auto bribeB = new eFramedButton(window());
        bribeB->setSmallFontSize();
        bribeB->setUnderline(false);
        auto bribeStr = eLanguage::zeusText(44, 281);
        eStringHelpers::replace(bribeStr, "[bribe_amount]",
                                std::to_string(ed.fBribe));
        bribeB->setText(bribeStr);
        bribeB->fitContent();
        wid->addWidget(bribeB);
        bribeB->setPressAction([this, ed]() {
            if(ed.fA1) ed.fA1();
            close();
        });
        bribeB->setVisible(bool(ed.fA1));

        const auto fightToDefend = new eFramedButton(window());
        fightToDefend->setSmallFontSize();
        fightToDefend->setUnderline(false);
        fightToDefend->setText(eLanguage::zeusText(44, 283));
        fightToDefend->fitContent();
        wid->addWidget(fightToDefend);
        fightToDefend->setPressAction([this, ed]() {
            if(ed.fA2) ed.fA2();
            close();
        });

        const int w = width() - 4*p;
        wid->setWidth(w);
        wid->layoutHorizontallyWithoutSpaces();
        wid->fitContent();
        wid->setWidth(w);

        surrenderB->align(eAlignment::vcenter);
        bribeB->align(eAlignment::vcenter);
        fightToDefend->align(eAlignment::vcenter);

        addWidget(wid);
    } else if(ed.fType == eMessageEventType::requestTributeGranted) {
        const auto c = ed.fCity;
        if(!c) return;
        const auto type = ed.fResourceType;
        const auto nameShort = eResourceTypeHelpers::typeName(type);
        const auto name = eResourceTypeHelpers::typeLongName(type);
        const auto itemshort = eResourceTypeHelpers::typeName(type);
        const int count = ed.fResourceCount;
        const auto countStr = std::to_string(count);
        const int space = ed.fSpaceCount;
        const auto tributeWid = createTributeWidget(type, count, space);

        eStringHelpers::replaceAll(msg.fText, "[amount]",
                                   countStr);
        eStringHelpers::replaceAll(msg.fText, "[item]",
                                   name);
        eStringHelpers::replaceAll(msg.fText, "[itemshort]",
                                   itemshort);

        ww->addWidget(tributeWid);
        tributeWid->setX(p);

        wid = new eWidget(window());
        wid->setNoPadding();

        const auto acceptB = new eFramedButton(window());
        acceptB->setSmallFontSize();
        acceptB->setUnderline(false);
        acceptB->setText(eLanguage::zeusText(44, 209));
        acceptB->fitContent();
        wid->addWidget(acceptB);
        acceptB->setPressAction([this, ed]() {
            if(ed.fA0) ed.fA0();
            close();
        });
        acceptB->setVisible(space > 0 || type == eResourceType::drachmas);

        const auto postponeB = new eFramedButton(window());
        postponeB->setSmallFontSize();
        postponeB->setUnderline(false);
        postponeB->setText(eLanguage::zeusText(44, 211));
        postponeB->fitContent();
        wid->addWidget(postponeB);
        postponeB->setPressAction([this, ed]() {
            if(ed.fA1) ed.fA1();
            close();
        });
        postponeB->setVisible(ed.fA1 && type != eResourceType::drachmas);

        const auto declineB = new eFramedButton(window());
        declineB->setSmallFontSize();
        declineB->setUnderline(false);
        declineB->setText(eLanguage::zeusText(44, 210));
        declineB->fitContent();
        wid->addWidget(declineB);
        declineB->setPressAction([this, ed]() {
            if(ed.fA2) ed.fA2();
            close();
        });

        const int w = width() - 4*p;
        wid->setWidth(w);
        wid->layoutHorizontallyWithoutSpaces();
        wid->fitContent();
        wid->setWidth(w);
        acceptB->align(eAlignment::vcenter);
        postponeB->align(eAlignment::vcenter);
        declineB->align(eAlignment::vcenter);

        addWidget(wid);
    } else if(ed.fType == eMessageEventType::resourceGranted) {
        const auto type = ed.fResourceType;
        const auto name = eResourceTypeHelpers::typeLongName(type);
        const auto itemshort = eResourceTypeHelpers::typeName(type);
        const int count = ed.fResourceCount;
        const auto countStr = std::to_string(count);
        const auto tributeWid = createTributeWidget(type, count, -1);

        eStringHelpers::replaceAll(msg.fText, "[amount]",
                                   countStr);
        eStringHelpers::replaceAll(msg.fText, "[item]",
                                   name);
        eStringHelpers::replaceAll(msg.fText, "[itemshort]",
                                   itemshort);

        ww->addWidget(tributeWid);
        tributeWid->setX(p);
    } else if(ed.fType == eMessageEventType::generalRequestGranted) {
        const auto c = ed.fCity;
        if(!c) return;
        const auto type = ed.fResourceType;
        const auto nameShort = eResourceTypeHelpers::typeName(type);
        const auto name = eResourceTypeHelpers::typeLongName(type);
        const auto itemshort = eResourceTypeHelpers::typeName(type);
        const int count = ed.fResourceCount;
        const auto countStr = std::to_string(count);
        const int space = ed.fSpaceCount;
        const int time = ed.fTime;
        const auto timeStr = std::to_string(time);
        const auto tributeWid = createTributeWidget(type, count, space, time);

        eStringHelpers::replaceAll(msg.fText, "[amount]",
                                   countStr);
        eStringHelpers::replaceAll(msg.fText, "[item]",
                                   name);
        eStringHelpers::replaceAll(msg.fText, "[itemshort]",
                                   itemshort);
        eStringHelpers::replaceAll(msg.fText, "[time_allotted]",
                                   timeStr);

        ww->addWidget(tributeWid);
        tributeWid->setX(p);

        wid = new eWidget(window());
        wid->setNoPadding();

        const auto a0B = new eFramedButton(window());
        a0B->setSmallFontSize();
        a0B->setUnderline(false);
        a0B->setText(ed.fA0Key);
        a0B->fitContent();
        wid->addWidget(a0B);
        a0B->setPressAction([this, ed]() {
            if(ed.fA0) ed.fA0();
            close();
        });
        a0B->setVisible(ed.fA0 != nullptr);

        const auto a1B = new eFramedButton(window());
        a1B->setSmallFontSize();
        a1B->setUnderline(false);
        a1B->setText(ed.fA1Key);
        a1B->fitContent();
        wid->addWidget(a1B);
        a1B->setPressAction([this, ed]() {
            if(ed.fA1) ed.fA1();
            close();
        });
        a1B->setVisible(ed.fA1 != nullptr);

        const auto a2B = new eFramedButton(window());
        a2B->setSmallFontSize();
        a2B->setUnderline(false);
        a2B->setText(ed.fA2Key);
        a2B->fitContent();
        wid->addWidget(a2B);
        a2B->setPressAction([this, ed]() {
            if(ed.fA2) ed.fA2();
            close();
        });

        const int w = width() - 4*p;
        wid->setWidth(w);
        wid->layoutHorizontallyWithoutSpaces();
        wid->fitContent();
        wid->setWidth(w);
        a0B->align(eAlignment::vcenter);
        a1B->align(eAlignment::vcenter);
        a2B->align(eAlignment::vcenter);

        addWidget(wid);
    } else if(ed.fType == eMessageEventType::troopsRequest) {
        const auto c = ed.fCity;
        if(!c) return;
        const int time = ed.fTime;
        const auto timeStr = std::to_string(time);

        eStringHelpers::replaceAll(msg.fText, "[travel_time]",
                                   timeStr);

        wid = new eWidget(window());
        wid->setNoPadding();

        const auto a0B = new eFramedButton(window());
        a0B->setSmallFontSize();
        a0B->setUnderline(false);
        a0B->setText(ed.fA0Key);
        a0B->fitContent();
        wid->addWidget(a0B);
        if(ed.fCA0) {
            a0B->setPressAction([this, ed]() {
                ed.fCA0([this]() { close(); });
            });
        } else {
            a0B->setPressAction([this, ed]() {
                if(ed.fA0) ed.fA0();
                close();
            });
        }
        a0B->setVisible(ed.fA0 != nullptr || ed.fCA0 != nullptr);

        const auto a1B = new eFramedButton(window());
        a1B->setSmallFontSize();
        a1B->setUnderline(false);
        a1B->setText(ed.fA1Key);
        a1B->fitContent();
        wid->addWidget(a1B);
        a1B->setPressAction([this, ed]() {
            if(ed.fA1) ed.fA1();
            close();
        });
        a1B->setVisible(ed.fA1 != nullptr);

        const auto a2B = new eFramedButton(window());
        a2B->setSmallFontSize();
        a2B->setUnderline(false);
        a2B->setText(ed.fA2Key);
        a2B->fitContent();
        wid->addWidget(a2B);
        a2B->setPressAction([this, ed]() {
            if(ed.fA2) ed.fA2();
            close();
        });
        a1B->setVisible(ed.fA2 != nullptr);

        const int w = width() - 4*p;
        wid->setWidth(w);
        wid->layoutHorizontallyWithoutSpaces();
        wid->fitContent();
        wid->setWidth(w);
        a0B->align(eAlignment::vcenter);
        a1B->align(eAlignment::vcenter);
        a2B->align(eAlignment::vcenter);

        addWidget(wid);
    }

    text->setText(msg.fText);
    text->fitContent();
    text->setX(p);

    ww->stackVertically();
    ww->fitContent();

    stackVertically();
    fitContent();

    if(ok) {
        mClosable = true;
        ok->align(eAlignment::right | eAlignment::bottom);
        ok->setX(ok->x() - 1.5*p);
        ok->setY(ok->y() - 1.5*p);
    }
    if(wid) {
        wid->align(eAlignment::hcenter);
        wid->setY(wid->y() + p/2);
    }
    w0->align(eAlignment::hcenter);
    ww->align(eAlignment::hcenter);
}

void eMessageBox::close() {
    if(mCloseFunc) mCloseFunc();
    deleteLater();
}

eWidget* eMessageBox::createTributeWidget(const eResourceType type,
                                          const int count,
                                          const int space,
                                          const int months) {
    const auto res = resolution();
    const auto uiScale = res.uiScale();
    const auto tributeWid = new eWidget(window());
    tributeWid->setNoPadding();
    const auto countStr = std::to_string(count);

    const auto typeIcon = new eLabel(window());
    const auto icon = eResourceTypeHelpers::icon(uiScale, type);
    typeIcon->setTexture(icon);
    typeIcon->setNoPadding();
    typeIcon->fitContent();
    tributeWid->addWidget(typeIcon);

    const auto countLabel = new eLabel(window());
    countLabel->setSmallFontSize();
    countLabel->setNoPadding();
    countLabel->setText(countStr);
    countLabel->fitContent();
    tributeWid->addWidget(countLabel);

    const auto name = eResourceTypeHelpers::typeLongName(type);
    const auto nameLabel = new eLabel(window());
    nameLabel->setSmallFontSize();
    nameLabel->setNoPadding();
    nameLabel->setText(" " + name);
    nameLabel->fitContent();
    tributeWid->addWidget(nameLabel);

    if(months != -1) {
        const auto monthsStr = std::to_string(months);

        const auto textLabel = new eLabel(window());
        textLabel->setSmallFontSize();
        textLabel->setNoPadding();
        const auto m = eLanguage::zeusText(8, 5);
        const auto c = eLanguage::zeusText(12, 2);
        const auto mtc = m + " " + c; // months to comply
        textLabel->setText("        " + mtc + " " + monthsStr);
        textLabel->fitContent();
        tributeWid->addWidget(textLabel);
    } else if(space != -1 && type != eResourceType::drachmas) {
        const auto countStr = std::to_string(std::min(count, space));

        const auto textLabel = new eLabel(window());
        textLabel->setSmallFontSize();
        textLabel->setNoPadding();
        textLabel->setText(" / " + eLanguage::text("can_accept") + " ");
        textLabel->fitContent();
        tributeWid->addWidget(textLabel);

        const auto typeIcon = new eLabel(window());
        const auto icon = eResourceTypeHelpers::icon(uiScale, type);
        typeIcon->setTexture(icon);
        typeIcon->setNoPadding();
        typeIcon->fitContent();
        tributeWid->addWidget(typeIcon);

        const auto countLabel = new eLabel(window());
        countLabel->setSmallFontSize();
        countLabel->setNoPadding();
        countLabel->setText(countStr);
        countLabel->fitContent();
        tributeWid->addWidget(countLabel);

        const auto name = eResourceTypeHelpers::typeLongName(type);
        const auto nameLabel = new eLabel(window());
        nameLabel->setSmallFontSize();
        nameLabel->setNoPadding();
        nameLabel->setText(" " + name);
        nameLabel->fitContent();
        tributeWid->addWidget(nameLabel);
    }

    tributeWid->stackHorizontally();
    tributeWid->fitContent();
    return tributeWid;
}

bool eMessageBox::keyPressEvent(const eKeyPressEvent& e) {
    if(!mClosable) return true;
    const auto k = e.key();
    if(k == SDL_SCANCODE_ESCAPE) {
        close();
    }
    return true;
}

bool eMessageBox::mousePressEvent(const eMouseEvent& e) {
    if(!mClosable) return true;
    const auto b = e.button();
    if(b == eMouseButton::right) {
        close();
    }
    return true;
}
