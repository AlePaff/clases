//
// Created by fedemgp on 01/05/23.
//

#ifndef SDL_DYNAMICSTENCIL_H
#define SDL_DYNAMICSTENCIL_H
#include <SDL2pp/SDL2pp.hh>

class DynamicStencil {
private:
    SDL2pp::Texture stencil;
    uint32_t width;
    uint32_t height;

public:
    explicit DynamicStencil(SDL2pp::Renderer &renderer, uint32_t width, uint32_t height);
    ~DynamicStencil() = default;
    void render(SDL2pp::Renderer &renderer, const SDL2pp::Rect &dest, float angle, SDL_RendererFlip flipType);
};


#endif //SDL_DYNAMICSTENCIL_H
