#include "etextureloadinghelpers.h"

#include "etextureloader.h"

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
        const eOffsets& offs) {
    const auto r = loadTex(pathBase, i, coll);
    const auto off = offs[i - 1];
    r->setOffset(off.first, off.second);
    return r;
}

const std::shared_ptr<eTexture>&
eTextureLoadingHelpers::getTexWithOffset(
        const std::string& pathBase, const int i,
        eTextureCollection& coll, std::string& path,
        const eOffsets& offs) {
    const auto& offset = offs[i - 1];
    const auto& tex = coll.addTexture();
    tex->setOffset(offset.first, offset.second);
    path = pathBase + addZeroes(std::to_string(i)) + ".png";
    return tex;
}

const std::shared_ptr<eTexture>&
eTextureLoadingHelpers::getTex(
        const std::string& pathBase, const int i,
        eTextureCollection& coll, std::string& path) {
    const auto& tex = coll.addTexture();
    path = pathBase + addZeroes(std::to_string(i)) + ".png";
    return tex;
}

const std::shared_ptr<eTexture>&
eTextureLoadingHelpers::queLoadTex(
        const std::string& pathBase,
        const int i,
        eTextureCollection& coll,
        eTextureLoader& texLoader) {
    std::string path;
    const auto& tex = getTex(pathBase, i, coll, path);
    texLoader.queueTask({tex, path});
    return tex;
}

const std::shared_ptr<eTexture>&
eTextureLoadingHelpers::queLoadTexWithOffset(
        const std::string& pathBase,
        const int i,
        eTextureCollection& coll,
        const eOffsets& offs,
        eTextureLoader& texLoader) {
    std::string path;
    const auto& tex = getTexWithOffset(pathBase, i, coll, path, offs);
    texLoader.queueTask({tex, path});
    return tex;
}

std::shared_ptr<eTexture>
eTextureLoadingHelpers::queLoadTex(
        const std::string& pathBase, const int i,
        eTextureLoader& texLoader) {
    const auto path = pathBase + addZeroes(std::to_string(i)) + ".png";
    const auto tex = std::make_shared<eTexture>();
    texLoader.queueTask({tex, path});
    return tex;
}

std::shared_ptr<eTexture>
eTextureLoadingHelpers::queLoadTexWithOffset(
        const std::string& pathBase, const int i,
        const eOffsets& offs, eTextureLoader& texLoader) {
    const auto tex = queLoadTex(pathBase, i, texLoader);
    const auto& offset = offs[i - 1];
    tex->setOffset(offset.first, offset.second);
    return tex;
}
