#include "esoundvector.h"

eSoundVector::~eSoundVector() {
    for(const auto& s : mPaths) {
        if(!s.first) continue;
        Mix_FreeChunk(s.first);
    }
}

void eSoundVector::addPath(const std::string& path) {
    mPaths.push_back({nullptr, path});
}

Mix_Chunk* loadSound(const std::string& path) {
    const auto wav = Mix_LoadWAV(path.c_str());
    if(!wav) {
        printf("Failed to load sound '%s'!\n SDL_mixer Error: %s\n",
               path.c_str(), Mix_GetError());
        return nullptr;
    }
    return wav;
}

void eSoundVector::play(const int id) {
    auto& p = mPaths[id];
    if(!p.first) {
        p.first = loadSound(p.second);
    }
    if(p.first) Mix_PlayChannel(-1, p.first, 0);
}

void eSoundVector::playRandomSound() {
    const int sc = soundCount();
    if(sc <= 0) return;
    const int id = rand() % sc;
    play(id);
}
