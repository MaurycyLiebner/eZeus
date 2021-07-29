#include "etextureloadinghelpers.h"

std::string eTextureLoadingHelpers::addZeroes(const std::string& str) {
    std::string result = str;
    while(result.size() < 5) {
        result.insert(0, "0");
    }
    return result;
}

void eTextureLoadingHelpers::loadTex(const std::string& pathBase,
                                     const int i, eTextureCollection& coll) {
    const auto path = pathBase + addZeroes(std::to_string(i)) + ".png";
    const bool r = coll.loadTexture(path);
    if(!r) std::printf("Failed to load %s\n", path.c_str());
}
