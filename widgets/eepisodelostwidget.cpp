#include "eepisodelostwidget.h"

#include "textures/egametextures.h"

#include "eframedlabel.h"
#include "eframedbutton.h"
#include "elanguage.h"

void eEpisodeLostWidget::initialize(const eAction& proceedA) {
    const auto res = resolution();
    const auto& intrfc = eGameTextures::interface();
    const int iRes = static_cast<int>(res.uiScale());
    const auto& texs = intrfc[iRes];
    setTexture(texs.fDefeatImage);

    const auto defeatLabel = new eFramedLabel(window());
    defeatLabel->setType(eFrameType::message);
    defeatLabel->setText(eLanguage::zeusText(62, 1));
    defeatLabel->setHugeFontSize();
    defeatLabel->fitContent();
    addWidget(defeatLabel);
    defeatLabel->align(eAlignment::center);

    const auto proceedButton = new eFramedButton(window());
    proceedButton->setRenderBg(true);
    proceedButton->setUnderline(false);
    proceedButton->setText(eLanguage::zeusText(62, 2));
    proceedButton->fitContent();
    addWidget(proceedButton);
    proceedButton->align(eAlignment::hcenter);
    proceedButton->setY(2*height()/3);
    proceedButton->setPressAction(proceedA);
}
