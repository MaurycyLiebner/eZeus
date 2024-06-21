#include "eresolution.h"

std::vector<eResolution> eResolution::sResolutions{
    eResolution{800, 600},
    eResolution{1024, 768},
    eResolution{1280, 720},
    eResolution{1280, 800},
    eResolution{1280, 1024},
    eResolution{1360, 768},
    eResolution{1366, 768},
    eResolution{1440, 900},
    eResolution{1600, 900},
    eResolution{1680, 1050},
    eResolution{1920, 1080},
    eResolution{1920, 1200},
    eResolution{2560, 1080},
    eResolution{2560, 1440},
    eResolution{2560, 1600},
    eResolution{3440, 1440},
    eResolution{3840, 2160},
};

eResolution::eResolution(const int width, const int height) :
    mWidth(width), mHeight(height) {
    if(height <= 800) {
        mUIScale = eUIScale::small;
    } else if(height <= 1200) {
        mUIScale = eUIScale::medium;
    } else {
        mUIScale = eUIScale::large;
    }
    mName = std::to_string(mWidth) + "x" + std::to_string(mHeight);
}

int eResolution::hugePadding() const {
    return 3*largePadding()/2;
}

int eResolution::largePadding() const {
    return 10*multiplier();
}

int eResolution::smallPadding() const {
    return 3*largePadding()/4;
}

int eResolution::tinyPadding() const {
    return largePadding()/2;
}

int eResolution::veryTinyPadding() const {
    return largePadding()/4;
}

int eResolution::veryVeryTinyPadding() const {
    return largePadding()/6;
}

int eResolution::margin() const {
    return largePadding();
}

double eResolution::multiplier() const {
    switch(mUIScale) {
    case eUIScale::tiny:
        return 0.5;
    case eUIScale::small:
        return 1.0;
    case eUIScale::medium:
        return 1.5;
    case eUIScale::large:
        return 2.0;
    }
}

int eResolution::hugeFontSize() const {
    return 3*largeFontSize()/2;
}

int eResolution::largeFontSize() const {
    return 20*multiplier();
}

int eResolution::smallFontSize() const {
    return 3*largeFontSize()/4;
}

int eResolution::verySmallFontSize() const {
    return 3*largeFontSize()/5;
}

int eResolution::tinyFontSize() const {
    return 17*largeFontSize()/30;
}

int eResolution::centralWidgetLargeWidth() const {
    return 660*multiplier();
}

int eResolution::centralWidgetSmallWidth() const {
    return 480*multiplier();
}

int eResolution::centralWidgetLargeHeight() const {
    return 540*multiplier();
}

int eResolution::centralWidgetSmallHeight() const {
    return 400*multiplier();
}
