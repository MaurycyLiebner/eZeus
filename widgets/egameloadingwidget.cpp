#include "egameloadingwidget.h"

#include "emainwindow.h"

eGameLoadingWidget::eGameLoadingWidget(eMainWindow* const window) :
    eWidget(window) {}

void eGameLoadingWidget::initialize() {
    mPB = new eProgressBar(window());
    mPB->fitContent();
    addWidget(mPB);
    mPB->align(eAlignment::center);

    mLabel = new eLabel("Waiting...", window());
    mLabel->fitContent();
    addWidget(mLabel);
    mLabel->align(eAlignment::hcenter);
    mLabel->setY(mPB->y() + 2*mLabel->height());

    mTerrainTextures.emplace_back(29, 15, renderer());
    mTerrainTextures.emplace_back(58, 30, renderer());
    mTerrainTextures.emplace_back(116, 60, renderer());

    mDemeterTextures.emplace_back(29, 15, renderer());
    mDemeterTextures.emplace_back(58, 30, renderer());
    mDemeterTextures.emplace_back(116, 60, renderer());

    mSize = mTerrainTextures.size() + mDemeterTextures.size();
    mPB->setRange(0, mSize);
}

void eGameLoadingWidget::setDoneAction(const eAction& a) {
    mDoneAction = a;
}

std::vector<eTerrainTextures>&& eGameLoadingWidget::takeTerrainTextures() {
    return std::move(mTerrainTextures);
}

std::vector<eDemeterTextures>&& eGameLoadingWidget::takeDemeterTextures() {
    return std::move(mDemeterTextures);
}

void eGameLoadingWidget::paintEvent(ePainter& p) {
    if(mNextToLoad >= mSize) {
        if(mDoneAction) mDoneAction();
    } else {
        const int toLoad = mNextToLoad++;
        const auto load = [this, toLoad]() {
            if(toLoad <= 2) {
                if(toLoad == 0) {
                    mLabel->setText("Loading small terrain textures...");
                } else if(toLoad == 1) {
                    mLabel->setText("Loading medium terrain textures...");
                } else if(toLoad == 2) {
                    mLabel->setText("Loading large terrain textures...");
                }
                mTerrainTextures[toLoad].load();
            } else if(toLoad <= 5) {
                const int dload = toLoad - 3;
                if(dload == 0) {
                    mLabel->setText("Loading small Demeter textures...");
                } else if(dload == 1) {
                    mLabel->setText("Loading medium Demeter textures...");
                } else if(dload == 2) {
                    mLabel->setText("Loading large Demeter textures...");
                }
                mDemeterTextures[dload].load();
            }
            mPB->setValue(mPB->value() + 1);
        };
        window()->addSlot(load);
    }
    eWidget::paintEvent(p);
}
