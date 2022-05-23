#include "egamedir.h"

std::string eGameDir::sPath;

void eGameDir::initialize() {
    sPath = "../Zeus and Poseidon/";
}

std::string eGameDir::path(const std::string& path) {
    return sPath + path;
}
