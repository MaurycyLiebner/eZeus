#include "emusicvector.h"

Mix_Music* loadMusic(const std::string& path) {
    const auto music = Mix_LoadMUS(path.c_str());
    if(!music) {
        printf("Failed to load music! SDL_mixer Error: %s\n",
               Mix_GetError());
        return nullptr;
    }
    return music;
}

eMusicVector::~eMusicVector() {
    for(const auto& s : mPaths) {
        if(!s.first) continue;
        Mix_FreeMusic(s.first);
    }
}

const bool sLoadOnAdd = false;

void eMusicVector::addPath(const std::string& path) {
    const auto sound = sLoadOnAdd ? loadMusic(path) : nullptr;
    mPaths.push_back({sound, path});
}

void eMusicVector::play(const int id, const bool loop) {
    auto& p = mPaths[id];
    if(!p.first) p.first = loadMusic(p.second);
    if(p.first) Mix_PlayMusic(p.first, loop ? -1 : 0);
}

void eMusicVector::playRandomSound(const bool loop) {
    const int sc = soundCount();
    if(sc <= 0) return;
    const int id = rand() % sc;
    play(id, loop);
}
