#include "erosterofleaders.h"

#include "eframedwidget.h"
#include "eframedbutton.h"
#include "elanguage.h"
#include "escrollwidgetcomplete.h"
#include "estringhelpers.h"
#include "emainwindow.h"
#include "enamewidget.h"
#include "engine/eworldcity.h"

#include <string>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

void eRosterOfLeaders::initialize() {
    eMainMenuBase::initialize();

    const auto frame = new eFramedWidget(window());
    frame->setType(eFrameType::message);
    addWidget(frame);

    const auto res = resolution();

    const int p = res.largePadding();
    const int cww = res.centralWidgetSmallWidth();
    const int cwh = res.centralWidgetSmallHeight();
    frame->resize(cww, cwh);

    frame->align(eAlignment::center);

    const auto inner = new eWidget(window());
    inner->setNoPadding();
    frame->addWidget(inner);
    inner->move(2*p, 2*p);
    inner->resize(frame->width() - 4*p, frame->height() - 4*p);

    const auto title = new eLabel(window());
    title->setHugeFontSize();
    title->setText(eLanguage::zeusText(292, 3)); // roster of leaders
    title->fitContent();
    inner->addWidget(title);
    title->align(eAlignment::hcenter);

    const auto buttons = new eWidget(window());
    buttons->setNoPadding();
    buttons->setWidth(inner->width());
    const auto buttons1 = new eWidget(window());
    buttons1->setNoPadding();
    buttons1->setWidth(inner->width());

    const int bw = (inner->width() - 2*p)/3;

    const auto createB = new eFramedButton(window());
    createB->setSmallFontSize();
    createB->setSmallPadding();
    createB->setUnderline(false);
    createB->setText(eLanguage::zeusText(292, 0)); // create leader
    createB->fitContent();
    createB->setWidth(bw);
    buttons1->addWidget(createB);
    createB->setPressAction([this]() {
        const auto w = window();
        const auto d = new eNameWidget(w);
        d->initialize("", eWorldCity::sLeaders(),
                      [this](const std::string& name) {
            if(name.empty()) return;
            const auto dir = "../Save/" + name + "/";
            std::filesystem::create_directories(dir);
            const auto w = window();
            w->showRosterOfLeaders();
        }, eLanguage::zeusText(44, 374), true);

        w->execDialog(d);
        d->align(eAlignment::center);
    });


    const auto selected = std::make_shared<std::string>();

    const auto deleteB = new eFramedButton(window());
    deleteB->setSmallFontSize();
    deleteB->setSmallPadding();
    deleteB->setUnderline(false);
    deleteB->setText(eLanguage::zeusText(292, 1)); // delete leader
    deleteB->fitContent();
    deleteB->setWidth(bw);
    buttons1->addWidget(deleteB);
    deleteB->setPressAction([this, selected]() {
        if(selected->empty()) return;
        const auto dir = "../Save/" + *selected + "/";
        std::filesystem::remove_all(dir);
        const auto w = window();
        if(*selected == w->leader()) {
            w->setLeader("");
        }
        w->showRosterOfLeaders();
    });

    const auto proceedB = new eFramedButton(window());
    proceedB->setSmallFontSize();
    proceedB->setSmallPadding();
    proceedB->setUnderline(false);
    proceedB->setText(eLanguage::zeusText(292, 2)); // proceed
    proceedB->fitContent();
    proceedB->setWidth(bw);
    buttons1->addWidget(proceedB);
    proceedB->setPressAction([this, selected]() {
        if(selected->empty()) return;
        const auto w = window();
        w->setLeader(*selected);
        w->showMainMenu();
    });

    buttons1->layoutHorizontallyWithoutSpaces();
    buttons1->fitHeight();
    buttons->addWidget(buttons1);

    const auto w = window();
    const auto leader = w->leader();
    if(!leader.empty()) {
        const auto returnB = new eFramedButton(window());
        returnB->setSmallFontSize();
        returnB->setSmallPadding();
        returnB->setUnderline(false);
        returnB->setText(eLanguage::zeusText(292, 4)); // return
        returnB->fitContent();
        buttons->addWidget(returnB);
        returnB->align(eAlignment::hcenter);
        returnB->setPressAction([this]() {
            const auto w = window();
            w->showMainMenu();
        });
    }
    buttons->stackVertically(p);
    buttons->fitHeight();

    {
        const auto scrollCont = new eScrollWidgetComplete(window());
        inner->addWidget(scrollCont);
        scrollCont->setWidth(inner->width());

        const int h = inner->height() - title->height() -
                      buttons->height() - 2*p;
        scrollCont->setHeight(h);
        scrollCont->initialize();
        const int swwidth = scrollCont->listWidth();

        const auto filesWidget = new eWidget(window());

        const auto leaders = eRosterOfLeaders::sLeaders();

        int y = 0;
        const auto selectedB = std::make_shared<eButton*>(nullptr);
        for(const auto& name : leaders) {
            const auto b = new eButton(name, window());
            b->setUnderline(false);
            b->setDarkFontColor();
            b->setMouseEnterAction([b]() {
                b->setLightFontColor();
            });
            b->setMouseLeaveAction([b, selected]() {
                if(b->text() == *selected) {
                    b->setLightFontColor();
                } else {
                    b->setDarkFontColor();
                }
            });
            b->setTextAlignment(eAlignment::left | eAlignment::vcenter);
            b->setNoPadding();
            b->fitContent();
            b->setWidth(swwidth);
            filesWidget->addWidget(b);
            b->setY(y);
            y += b->height();
            b->setPressAction([b, selected, selectedB]() {
                if(*selectedB) {
                    (*selectedB)->setDarkFontColor();
                }
                *selectedB = b;
                *selected = b->text();
                b->setLightFontColor();
            });
        }
        filesWidget->setNoPadding();
        filesWidget->fitContent();

        scrollCont->setScrollArea(filesWidget);
    }

    inner->addWidget(buttons);

    inner->stackVertically(p);
}

std::vector<std::string> eRosterOfLeaders::sLeaders() {
    std::vector<std::string> leaders;
    const auto folder = "../Save/";
    if(std::filesystem::exists(folder)) {
        for(const auto& entry : fs::directory_iterator(folder)) {
            const bool id = entry.is_directory();
            if(!id) continue;
            const auto path = entry.path();
            leaders.push_back(path.filename());
        }
    }
    return leaders;
}
