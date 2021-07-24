#ifndef ERESOLUTION_H
#define ERESOLUTION_H

#include <string>
#include <vector>

enum class eRes {
    p2160, p1440, p1080, p720, p480
};

class eResolution {
private:
    eResolution(const eRes res) {
        int w;
        int h;
        switch(res) {
        case eRes::p2160:
            w = 3840;
            h = 2160;
            break;
        case eRes::p1440:
            w = 2560;
            h = 1440;
            break;
        case eRes::p1080:
            w = 1920;
            h = 1080;
            break;
        case eRes::p720:
            w = 1280;
            h = 720;
            break;
        case eRes::p480:
            w = 854;
            h = 480;
            break;
        }

        mRes = res;
        mWidth = w;
        mHeight = h;
        mName = std::to_string(w) + "x" + std::to_string(h);
    }
public:
    eResolution() {}

    static const std::vector<eResolution> sResolutions;
    static eResolution sGetResolution(const eRes res);

    int width() const { return mWidth; }
    int height() const { return mHeight; }
    const std::string& name() const { return mName; }
    eRes res() const { return mRes; }
private:
    eRes mRes;
    std::string mName;
    int mWidth;
    int mHeight;
};

#endif // ERESOLUTION_H
