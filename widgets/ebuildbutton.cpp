#include "ebuildbutton.h"

#include "textures/egametextures.h"

void eBuildButton::initialize(const std::string& name,
                              const int marbleCost,
                              const int cost) {
    const auto& intrfc = eGameTextures::interface();
    int iRes;
    int mult;
    iResAndMult(iRes, mult);

    const int width = 190*mult;

    setWidth(width);
    setHeight(10*mult);

    const auto& coll = intrfc[iRes];

    {
        const auto nameWidget = new eWidget(window());
        nameWidget->setWidth(width/2 + 10*mult);

        addWidget(nameWidget);
        nameWidget->align(eAlignment::vcenter);

        const auto nameLabel = new eLabel(name, window());
        nameLabel->setSmallFontSize();
        nameLabel->setNoPadding();
        nameLabel->fitContent();

        nameWidget->addWidget(nameLabel);

        nameLabel->align(eAlignment::vcenter | eAlignment::hcenter);
    }

    if(marbleCost > 0) {
        const auto marbleIcon = new eLabel(window());
        marbleIcon->setTexture(coll.fMarbleUnit);
        marbleIcon->setNoPadding();
        marbleIcon->fitContent();

        const auto cstr = std::to_string(marbleCost);
        const auto marbleText = new eLabel(cstr, window());
        marbleText->setSmallFontSize();
        marbleText->setNoPadding();
        marbleText->fitContent();

        addWidget(marbleIcon);
        addWidget(marbleText);

        marbleIcon->align(eAlignment::vcenter);
        marbleText->align(eAlignment::vcenter);

        marbleIcon->setX(width/2 + 30*mult);
        marbleText->setX(marbleIcon->x() + marbleIcon->width());
    }
    if(cost > 0) {
        const auto drachmaIcon = new eLabel(window());
        drachmaIcon->setTexture(coll.fDrachmasUnit);
        drachmaIcon->setNoPadding();
        drachmaIcon->fitContent();

        const auto cstr = std::to_string(cost);
        const auto drachmaText = new eLabel(cstr, window());
        drachmaText->setSmallFontSize();
        drachmaText->setNoPadding();
        drachmaText->fitContent();

        addWidget(drachmaIcon);
        addWidget(drachmaText);

        drachmaIcon->align(eAlignment::vcenter);
        drachmaText->align(eAlignment::vcenter);

        drachmaIcon->setX(width/2 + 60*mult);
        drachmaText->setX(drachmaIcon->x() + drachmaIcon->width());
    }
}
