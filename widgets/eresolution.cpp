#include "eresolution.h"

const std::vector<eResolution> eResolution::sResolutions{
    eResolution{eRes::p2160},
    eResolution{eRes::p1440},
    eResolution{eRes::p1080},
    eResolution{eRes::p720},
    eResolution{eRes::p480}
};

eResolution::eResolution(const eRes res) {
    mRes = res;
    const int w = width(res);
    const int h = height(res);
    mName = std::to_string(w) + "x" + std::to_string(h);
}

int eResolution::width(const eRes res) {
    switch(res) {
    case eRes::p2160:
        return 3840;
    case eRes::p1440:
        return 2560;
    case eRes::p1080:
        return 1920;
    case eRes::p720:
        return 1280;
    case eRes::p480:
        return 854;
    }
}

int eResolution::height(const eRes res) {
    switch(res) {
    case eRes::p2160:
        return 2160;
    case eRes::p1440:
        return 1440;
    case eRes::p1080:
        return 1080;
    case eRes::p720:
        return 720;
    case eRes::p480:
        return 480;
    }
}

int eResolution::padding(const eRes res) {
    switch(res) {
    case eRes::p2160:
        return 35;
    case eRes::p1440:
        return 25;
    case eRes::p1080:
        return 20;
    case eRes::p720:
        return 15;
    case eRes::p480:
        return 10;
    }
}

int eResolution::margin(const eRes res) {
    return padding(res);
}

int eResolution::hugeFontSize(const eRes res) {
    return 3*largeFontSize(res)/2;
}

int eResolution::largeFontSize(const eRes res) {
    switch(res) {
    case eRes::p2160:
        return 45;
    case eRes::p1440:
        return 35;
    case eRes::p1080:
        return 28;
    case eRes::p720:
        return 20;
    case eRes::p480:
        return 15;
    }
}

int eResolution::smallFontSize(const eRes res) {
    return 2*largeFontSize(res)/3;
}

int eResolution::tinyFontSize(const eRes res) {
    return largeFontSize(res)/2;
}

int eResolution::centralWidgetWidth(const eRes res) {
    switch(res) {
    case eRes::p2160:
        return 1750;
    case eRes::p1440:
        return 1000;
    case eRes::p1080:
        return 750;
    case eRes::p720:
        return 500;
    case eRes::p480:
        return 350;
    }
}

int eResolution::centralWidgetHeight(const eRes res) {
    return centralWidgetWidth(res);
}
