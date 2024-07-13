#include "egamedir.h"

#include <SDL2/SDL_filesystem.h>
#include <fstream>

std::string eGameDir::sPath;

void eGameDir::initialize() {
    sPath = exeDir() + "../../";
    const auto zp = exeDir() + "../zeus_path.txt";
    std::ifstream file(zp);
    if(!file.good()) return;
    std::string str;
    const bool g = !!std::getline(file, str);
    if(!g) return;
    sPath = exeDir() + str;
}

std::string eGameDir::path(const std::string& path) {
    return sPath + path;
}

std::string eGameDir::settingsPath() {
    return exeDir() + "../settings.txt";
}

std::string eGameDir::exeDir() {
    const auto d = SDL_GetBasePath();
    const std::string str(d);
    return str;
}

std::string eGameDir::adventuresDir() {
    return exeDir() + "../Adventures/";
}

std::string eGameDir::saveDir() {
    return exeDir() + "../Save/";
}

std::string eGameDir::texturesDir() {
    return exeDir() + "../Textures/";
}
