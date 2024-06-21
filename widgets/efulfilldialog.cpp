#include "efulfilldialog.h"

#include "engine/eworldcity.h"
#include "engine/egameboard.h"
#include "estringhelpers.h"
#include "elanguage.h"
#include "gameEvents/ereceiverequestevent.h"
#include "gameEvents/etroopsrequestevent.h"
#include "buildings/eheroshall.h"
#include "widgets/eframedbutton.h"
#include "widgets/equestionwidget.h"
#include "widgets/emessagewidget.h"
#include "widgets/eworldwidget.h"
#include "widgets/elabel.h"
#include "emainwindow.h"

eFulfillDialog::eFulfillDialog(eMainWindow* const window) :
    eInfoWidget(window, true, true) {}

void eFulfillDialog::initialize(eGameBoard* const board,
                                const eCity& city) {
    auto title = eLanguage::zeusText(41, 2);
    eStringHelpers::replace(title, "[city_name]", city->name());
    eInfoWidget::initialize(title);

    const auto res = resolution();
    const auto uiScale = res.uiScale();
    const int iRes = static_cast<int>(uiScale);
    const auto& intrfc = eGameTextures::interface();
    const auto& texs = intrfc[iRes];
    const int p = res.largePadding();

    const auto iw = addFramedWidget(remainingHeight());
    const int bw = iw->width() - 2*p;
    int y = p;
    const auto& qs = board->cityRequests();
//    std::vector<stdsptr<eReceiveRequestEvent>> qs;
//    const auto q = e::make_shared<eReceiveRequestEvent>(eGameEventBranch::root);
//    q->initialize(0, eResourceType::fleece, 10, city);
//    qs.push_back(q);
    for(const auto q : qs) {
        const bool c = city == q->city();
        if(!c) continue;
        const auto resource = q->resourceType();
        const int count = q->resourceCount();
        const auto countStr = std::to_string(count);
        const auto b = new eFramedButton(window());
        b->setNoPadding();
        b->setRenderBg(true);
        b->setPressAction([this, q, board, resource, count]() {
            const auto bcount = board->resourceCount(resource);
            const auto w = window();
            const auto ww = w->worldWidget();
            if(bcount >= count) {
                const auto acceptA = [q]() {
                    q->dispatch();
                };
                const auto title = eLanguage::zeusText(5, 6); // Request
                const auto text = eLanguage::zeusText(5, 7); // Dispatch goods?

                const auto qw = new eQuestionWidget(window());
                qw->initialize(title, text, acceptA, nullptr);
                ww->openDialog(qw);
            } else {
                const auto title = eLanguage::zeusText(5, 6); // Request
                const auto text = eLanguage::zeusText(5, 9); // You do not have enough to fulfill the request

                const auto qw = new eMessageWidget(window());
                qw->initialize(title, text);
                ww->openDialog(qw);
            }
        });

        const auto iww = new eWidget(window());
        iww->setNoPadding();
        b->addWidget(iww);
        iww->move(p, p);

        const bool f = board->resourceCount(resource) >= count;

        const auto stateLabel = new eLabel(window());
        stateLabel->setNoPadding();
        iww->addWidget(stateLabel);
        const auto& coll = f ? texs.fRequestFulfilledBox :
                               texs.fRequestWaitingBox;
        const auto tex = coll.getTexture(0);
        stateLabel->setTexture(tex);
        stateLabel->fitContent();

        const auto resIcon = eResourceTypeHelpers::icon(
                                 uiScale, resource);
        const auto iconLabel = new eLabel(window());
        iconLabel->setNoPadding();
        iconLabel->setTexture(resIcon);
        iconLabel->fitContent();
        iww->addWidget(iconLabel);

        const auto resName = eResourceTypeHelpers::typeLongName(
                                 resource);
        const auto textLabel = new eLabel(window());
        textLabel->setSmallFontSize();
        textLabel->setNoPadding();
        textLabel->setText(countStr + "  " + resName);
        textLabel->fitContent();
        iww->addWidget(textLabel);

        iww->stackHorizontally(p);
        iww->fitContent();
        b->setHeight(iww->height() + 2*p);
        b->setWidth(bw);
        iw->addWidget(b);
        b->move(p, y);
        y += p + b->height();
    }

    bool hasArmy = false;
    const auto& bs = board->banners();
    for(const auto& b : bs) {
        const bool a = b->isAbroad();
        if(!a) {
            hasArmy = true;
            break;
        }
    }
    if(!hasArmy) {
        const auto& hs = board->heroHalls();
        for(const auto h : hs) {
            const bool a = h->heroOnQuest();
            if(!a) {
                hasArmy = true;
                break;
            }
        }
    }

    const auto& qqs = board->cityTroopsRequests();
//    std::vector<stdsptr<eTroopsRequestEvent>> qqs;
//    const auto qq = e::make_shared<eTroopsRequestEvent>(eGameEventBranch::root);
//    qq->initialize(0, city, city, false);
//    qq->setGameBoard(board);
//    qqs.push_back(qq);
    for(const auto q : qqs) {
        const bool c = city == q->city();
        if(!c) continue;
        const auto b = new eFramedButton(window());
        b->setNoPadding();
        b->setRenderBg(true);
        b->setPressAction([q]() {
            q->dispatch();
        });

        const auto iww = new eWidget(window());
        iww->setNoPadding();
        b->addWidget(iww);
        iww->move(p, p);

        const auto stateLabel = new eLabel(window());
        stateLabel->setNoPadding();
        iww->addWidget(stateLabel);
        const auto& coll = hasArmy ? texs.fRequestFulfilledBox :
                                     texs.fRequestWaitingBox;
        const auto tex = coll.getTexture(0);
        stateLabel->setTexture(tex);
        stateLabel->fitContent();

        const auto& troopsIcon = texs.fTroopsRequestIcon;
        const auto iconLabel = new eLabel(window());
        iconLabel->setNoPadding();
        iconLabel->setTexture(troopsIcon);
        iconLabel->fitContent();
        iww->addWidget(iconLabel);

        const auto resName = eLanguage::zeusText(61, 187); // troops requested
        const auto textLabel = new eLabel(window());
        textLabel->setSmallFontSize();
        textLabel->setNoPadding();
        textLabel->setText(resName);
        textLabel->fitContent();
        iww->addWidget(textLabel);

        iww->stackHorizontally(p);
        iww->fitContent();
        b->setHeight(iww->height() + 2*p);
        b->setWidth(bw);
        iw->addWidget(b);
        b->move(p, y);
        y += p + b->height();
    }

    if(iw->children().empty()) {
        const auto noRequests = eLanguage::zeusText(41, 21);
        const auto noRequestsL = new eLabel(window());
        noRequestsL->setNoPadding();
        noRequestsL->setText(noRequests);
        noRequestsL->fitContent();
        iw->addWidget(noRequestsL);
        noRequestsL->align(eAlignment::center);
    }

    setCloseAction([this]() {
        deleteLater();
    });
}
