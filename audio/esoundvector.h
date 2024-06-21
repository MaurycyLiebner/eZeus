#ifndef ESOUNDVECTOR_H
#define ESOUNDVECTOR_H

#include <string>
#include <vector>

#include <SDL2/SDL_mixer.h>

class eSoundVector {
public:
    ~eSoundVector();

    int soundCount() const { return mPaths.size(); }
    void addPath(const std::string& path);
    void play(const int id);
    void playRandomSound();
private:
    std::vector<std::pair<Mix_Chunk*, std::string>> mPaths;
};

#endif // ESOUNDVECTOR_H
