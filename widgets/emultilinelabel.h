#ifndef EMULTILINELABEL_H
#define EMULTILINELABEL_H

#include "ewidget.h"

class eLabel;

class eMultiLineLabel : public eWidget {
public:
    using eWidget::eWidget;

    void setTinyFontSize();
    void setVerySmallFontSize();
    void setSmallFontSize();
    void setHugeFontSize();
    void setFontSize(const int s);

    void setLightFontColor();
    void setDarkFontColor();
    void setYellowFontColor();
    void setFontColor(const eFontColor color);

    void setText(const std::string& text);

    void clear();
private:
    const eResolution& res() const;

    int mFontSize = 0;
    eFontColor mFontColor = eFontColor::light;
    std::vector<eLabel*> mLabels;
};

#endif // EMULTILINELABEL_H
