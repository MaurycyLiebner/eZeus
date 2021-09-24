#ifndef ERESOLUTION_H
#define ERESOLUTION_H

#include <string>
#include <vector>

enum class eUIScale {
    tiny, small, medium, large
};

class eResolution {
public:
    eResolution() {}
    eResolution(const int width, const int height);

    int width() const { return mWidth; }
    int height() const { return mHeight; }

    double multiplier() const;

    int hugePadding() const;
    int largePadding() const;
    int smallPadding() const;
    int tinyPadding() const;

    int margin() const;

    int hugeFontSize() const;
    int largeFontSize() const;
    int smallFontSize() const;
    int verySmallFontSize() const;
    int tinyFontSize() const;

    int centralWidgetWidth() const;
    int centralWidgetHeight() const;

    static std::vector<eResolution> sResolutions;

    const std::string& name() const { return mName; }
    eUIScale uiScale() const { return mUIScale; }

    bool operator==(const eResolution other) const {
        return mWidth == other.mWidth &&
               mHeight == other.mHeight;
    }

    bool operator!=(const eResolution other) const {
        return !(*this == other);
    }
private:
    int mWidth;
    int mHeight;
    eUIScale mUIScale;
    std::string mName;
};

#endif // ERESOLUTION_H
