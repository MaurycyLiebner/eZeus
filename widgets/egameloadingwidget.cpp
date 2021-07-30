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

    for(const auto& s : {std::pair<int, int>{29, 15},
                         std::pair<int, int>{58, 30},
                         std::pair<int, int>{116, 60}}) {
        mTerrainTextures.emplace_back(s.first, s.second, renderer());
        mDemeterTextures.emplace_back(s.first, s.second, renderer());
        mBuildingTextures.emplace_back(s.first, s.second, renderer());
    }

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

std::vector<eBuildingTextures>&& eGameLoadingWidget::takeBuildingTextures() {
    return std::move(mBuildingTextures);
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
            } else if(toLoad <= 8) {
                const int dload = toLoad - 6;
                if(dload == 0) {
                    mLabel->setText("Loading small building textures...");
                } else if(dload == 1) {
                    mLabel->setText("Loading medium building textures...");
                } else if(dload == 2) {
                    mLabel->setText("Loading large building textures...");
                }
                mBuildingTextures[dload].load();
            }
            mPB->setValue(mPB->value() + 1);
        };
        window()->addSlot(load);
    }
    eWidget::paintEvent(p);
}
