#include "ebinaryimageloader.h"

#include <fstream>

#include "binary.h"
#include "egamedir.h"

std::shared_ptr<eTexture> eBinaryImageLoader::load(SDL_Renderer* const r,
                                                   const std::string& path) {
    const auto it = eBinaryDataMap.find(path);
    if(it == eBinaryDataMap.end()) {
        printf("Could not find '%s' image\n", path.c_str());
        return nullptr;
    }
    const auto bp = eGameDir::binaryPath();
    std::ifstream file(bp, std::ios::in | std::ios::binary);
    if(!file) {
        printf("Could not open '%s'\n", bp.c_str());
        return nullptr;
    }

    const auto& bd = it->second;
    const auto data = new char[bd.fSize];
    file.seekg(bd.fPos);
    file.read(data, bd.fSize);
    file.close();
    const auto rw = SDL_RWFromMem(data, bd.fSize);
    const auto surf = IMG_Load_RW(rw, SDL_FALSE);
    if(!surf) {
        printf("Unable to load image %s! SDL_image Error: %s\n",
               path.c_str(), IMG_GetError());
        return nullptr;
    }
    delete[] data;

    const auto tex = std::make_shared<eTexture>();
    tex->load(r, surf);

    return tex;
}
