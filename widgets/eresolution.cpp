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
    eResolution{3440, 1440},
    eResolution{3840, 2160},
};

eResolution::eResolution(const int width, const int height) :
    mWidth(width), mHeight(height) {
    if(height <= 600) {
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

int eResolution::margin() const {
    return largePadding();
}

double eResolution::multiplier() const {
    return height()/720.;
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

int eResolution::tinyFontSize() const {
    return largeFontSize()/2;
}

int eResolution::centralWidgetWidth() const {
    return 3*centralWidgetHeight()/2;
}

int eResolution::centralWidgetHeight() const {
    return 480*multiplier();
}
