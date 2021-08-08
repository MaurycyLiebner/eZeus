#ifndef ERESOLUTION_H
#define ERESOLUTION_H

#include <string>
#include <vector>

enum class eRes {
    p2160, p1440, p1080, p720, p480
};

//switch(resolution()) {
//case eRes::p2160:
//    break;
//case eRes::p1440:
//    break;
//case eRes::p1080:
//    break;
//case eRes::p720:
//    break;
//case eRes::p480:
//    break;
//}

class eResolution {
public:
    eResolution(const eRes res);

    static int width(const eRes res);
    static int height(const eRes res);
    static int padding(const eRes res);
    static int margin(const eRes res);

    static int hugeFontSize(const eRes res);
    static int largeFontSize(const eRes res);
    static int smallFontSize(const eRes res);
    static int tinyFontSize(const eRes res);

    static int centralWidgetWidth(const eRes res);
    static int centralWidgetHeight(const eRes res);

    static const std::vector<eResolution> sResolutions;

    const std::string& name() const { return mName; }
    eRes res() const { return mRes; }
private:
    eRes mRes;
    std::string mName;
};

#endif // ERESOLUTION_H
