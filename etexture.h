#ifndef ETEXTURE_H
#define ETEXTURE_H

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <memory>

class eTexture {
public:
    eTexture();
    eTexture(const eTexture& other);
    ~eTexture();

    eTexture& operator=(const eTexture& src);

    void reset();
    bool load(SDL_Renderer* const r,
              const std::string& path);
    bool loadText(SDL_Renderer* const r,
                  const std::string& text,
                  const SDL_Color& color,
                  TTF_Font& font);

    void render(SDL_Renderer* const r,
                const SDL_Rect& srcRect,
                const SDL_Rect& dstRect) const;
    void render(SDL_Renderer* const r,
                const int x, const int y,
                const SDL_Rect& srcRect) const;
    void render(SDL_Renderer* const r,
                const int x, const int y) const;

    int width() const { return mWidth; }
    int height() const { return mHeight; }

    bool isNull() const;
private:
    int mWidth = 0;
    int mHeight = 0;
    SDL_Texture* mTex = nullptr;
    std::shared_ptr<int> mRefs;
};

#endif // ETEXTURE_H
