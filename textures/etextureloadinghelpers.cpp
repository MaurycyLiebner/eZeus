#include "etextureloadinghelpers.h"

std::string eTextureLoadingHelpers::addZeroes(const std::string& str) {
    std::string result = str;
    while(result.size() < 5) {
        result.insert(0, "0");
    }
    return result;
}

std::shared_ptr<eTexture> eTextureLoadingHelpers::loadTex(
        const std::string& pathBase,
        const int i, eTextureCollection& coll) {
    const auto path = pathBase + addZeroes(std::to_string(i)) + ".png";
    const auto r = coll.loadTexture(path);
    if(!r) std::printf("Failed to load %s\n", path.c_str());
    return r;
}

std::shared_ptr<eTexture> eTextureLoadingHelpers::loadTexWithOffset(
        const std::string& pathBase,
        const int i, eTextureCollection& coll,
        const std::vector<std::pair<int, int>>& offs) {
    const auto r = loadTex(pathBase, i, coll);
    const auto off = offs[i - 1];
    r->setOffset(off.first, off.second);
    return r;
}
