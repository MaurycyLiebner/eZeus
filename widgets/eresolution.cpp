#include "eresolution.h"

const std::vector<eResolution> eResolution::sResolutions{
    eResolution{eRes::p2160},
    eResolution{eRes::p1440},
    eResolution{eRes::p1080},
    eResolution{eRes::p720},
    eResolution{eRes::p480}
};

eResolution eResolution::sGetResolution(const eRes res) {
    return sResolutions[static_cast<int>(res)];
}
