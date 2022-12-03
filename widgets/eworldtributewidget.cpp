#include "eworldtributewidget.h"

#include "elanguage.h"

void eWorldTributeWidget::initialize() {
    const auto titleStr = eLanguage::text("paying_tribute");
    const auto titleW = new eLabel(titleStr, window());
    titleW->setTinyFontSize();
    titleW->setNoPadding();
    titleW->fitContent();
    addWidget(titleW);
    titleW->align(eAlignment::hcenter);

    mTypeIcon = new eLabel(window());
    mTypeIcon->setNoPadding();
    addWidget(mTypeIcon);
    mTypeIcon->setY(titleW->height());

    mTextLabel = new eLabel(window());
    mTextLabel->setTinyFontSize();
    mTextLabel->setNoPadding();
    addWidget(mTextLabel);
    mTextLabel->setY(titleW->height());

    fitContent();
}

void eWorldTributeWidget::setCity(const stdsptr<eWorldCity>& c) {
    if(c) {
        const auto rel = c->relationship();
        const bool vassOrCol = rel == eWorldCityRelationship::vassal ||
                               rel == eWorldCityRelationship::collony;
        if(!vassOrCol) return hide();
        const auto type = c->tributeType();
        const int count = c->tributeCount();
        const auto uiScale = resolution().uiScale();
        const auto icon = eResourceTypeHelpers::icon(uiScale, type);
        mTypeIcon->setTexture(icon);
        mTypeIcon->fitContent();
        const auto name = eResourceTypeHelpers::typeName(type);
        const auto yearly = eLanguage::text("yearly");
        const auto text = std::to_string(count) + " " + name + " " + yearly;
        mTextLabel->setText(text);
        mTextLabel->fitContent();
        mTextLabel->setX(mTypeIcon->x() + mTypeIcon->width());
        show();
    } else {
        hide();
    }
}
