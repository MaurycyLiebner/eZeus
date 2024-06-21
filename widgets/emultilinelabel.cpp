#include "emultilinelabel.h"

#include "emainwindow.h"
#include "widgets/elabel.h"

#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> split_string_by_newline(const std::string& str) {
    auto result = std::vector<std::string>{};
    auto ss = std::stringstream{str};

    for(std::string line; std::getline(ss, line, '*');) {
        result.push_back(line);
    }

    return result;
}

const eResolution& eMultiLineLabel::res() const {
    return window()->resolution();
}

void eMultiLineLabel::setTinyFontSize() {
    const int s = res().tinyFontSize();
    return setFontSize(s);
}

void eMultiLineLabel::setVerySmallFontSize() {
    const int s = res().verySmallFontSize();
    return setFontSize(s);
}

void eMultiLineLabel::setSmallFontSize() {
    const int s = res().smallFontSize();
    return setFontSize(s);
}

void eMultiLineLabel::setHugeFontSize() {
    const int s = res().hugeFontSize();
    return setFontSize(s);
}

void eMultiLineLabel::setFontSize(const int s) {
    mFontSize = s;
}

void eMultiLineLabel::setFontColor(const eFontColor color) {
    mFontColor = color;
}

void eMultiLineLabel::setText(const std::string& text) {
    clear();
    const auto lines = split_string_by_newline(text);
    if(lines.empty()) return;
    for(const auto& l : lines) {
        const auto label = new eLabel(window());
        label->setFontSize(mFontSize);
        label->setFontColor(mFontColor);
        label->setNoPadding();
        label->setText(l);
        label->fitContent();
        addWidget(label);
        mLabels.push_back(label);
    }
    stackVertically();
    fitContent();
    for(const auto l : mLabels) {
        l->align(eAlignment::hcenter);
    }
}

void eMultiLineLabel::clear() {
    for(const auto l : mLabels) {
        l->deleteLater();
    }
    mLabels.clear();
}

void eMultiLineLabel::setLightFontColor() {
    setFontColor(eFontColor::light);
}

void eMultiLineLabel::setDarkFontColor() {
    setFontColor(eFontColor::dark);
}

void eMultiLineLabel::setYellowFontColor() {
    setFontColor(eFontColor::yellow);
}
