#include "eworldtributewidget.h"

#include "elanguage.h"

void eWorldTributeWidget::initialize() {
    const auto titleStr = eLanguage::zeusText(44, 320);
    mTitleLabel = new eLabel(titleStr, window());
    mTitleLabel->setTinyFontSize();
    mTitleLabel->setNoPadding();
    mTitleLabel->fitContent();
    addWidget(mTitleLabel);
    mTitleLabel->align(eAlignment::hcenter);

    mTypeIcon = new eLabel(window());
    mTypeIcon->setNoPadding();
    addWidget(mTypeIcon);
    mTypeIcon->setY(mTitleLabel->height());

    mTextLabel = new eLabel(window());
    mTextLabel->setTinyFontSize();
    mTextLabel->setNoPadding();
    addWidget(mTextLabel);
    mTextLabel->setY(mTitleLabel->height());

    mAlliesLabel = new eLabel(window());
    mAlliesLabel->setTinyFontSize();
    mAlliesLabel->setNoPadding();
    addWidget(mAlliesLabel);
    const auto alliesText = eLanguage::zeusText(44, 323);
    mAlliesLabel->resize(width(), height());
    mAlliesLabel->setWrapWidth(width());
    mAlliesLabel->setWrapAlignment(eAlignment::hcenter);
    mAlliesLabel->setText(alliesText);
    mAlliesLabel->hide();
}

void eWorldTributeWidget::setCity(const stdsptr<eWorldCity>& c) {
    mAlliesLabel->hide();
    mTitleLabel->hide();
    mTypeIcon->hide();
    mTextLabel->hide();
    if(c) {
        const bool isDist = c->isDistant();
        if(isDist) {
            mAlliesLabel->setText(eLanguage::zeusText(44, 325));
            mAlliesLabel->show();
            return;
        }
        const auto rel = c->relationship();
        const bool vassOrCol = rel == eWorldCityRelationship::vassal ||
                               rel == eWorldCityRelationship::collony;
        if(!vassOrCol) {
            if(rel == eWorldCityRelationship::ally) {
                mAlliesLabel->setText(eLanguage::zeusText(44, 323));
                mAlliesLabel->show();
            } else if(rel == eWorldCityRelationship::rival) {
                mAlliesLabel->setText(eLanguage::zeusText(44, 324));
                mAlliesLabel->show();
            }
            return;
        }
        mTitleLabel->show();
        mTypeIcon->show();
        mTextLabel->show();
        const auto ttype = c->tributeType();
        const int count = c->tributeCount();
        const auto uiScale = resolution().uiScale();
        const auto icon = eResourceTypeHelpers::icon(uiScale, ttype);
        mTypeIcon->setTexture(icon);
        mTypeIcon->fitContent();
        const auto name = eResourceTypeHelpers::typeName(ttype);
        const auto yearly = eLanguage::zeusText(44, 322);
        const auto text = std::to_string(count) + " " + name + " " + yearly;
        mTextLabel->setText(text);
        mTextLabel->fitContent();
        mTextLabel->setX(mTypeIcon->x() + mTypeIcon->width());
    }
}
