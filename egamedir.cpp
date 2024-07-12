#include "egamedir.h"

#include <SDL2/SDL_filesystem.h>

std::string eGameDir::sPath;

void eGameDir::initialize() {
    sPath = exeDir() + "../Zeus and Poseidon/";
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
