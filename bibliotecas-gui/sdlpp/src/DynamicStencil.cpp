//
// Created by fedemgp on 01/05/23.
//

#include "DynamicStencil.h"
#include "SdlException.h"
#include <SDL2/SDL2_gfxPrimitives.h>

DynamicStencil::DynamicStencil(SDL2pp::Renderer &renderer, uint32_t width, uint32_t height):
    stencil(
        renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height
    ),
    width(width),
    height(height) {
    // Primero, nos aseguramos de crear una textura vacía, seteando el formato RGB para colorear,
    // y habilitando a esta textura para que se pueda dibujar sobre ella.

    // Configuramos al renderer para que dibuje sobre la textura y no sobre la ventana (necesitamos
    // haberle dado permisos de target a la textura previamente) y la pintamos de negro.
    // Como SDL_SetRenderTarget y SDL_RenderClear son primitivas de SDL2 (y no wrappers de SDL2pp)
    // debemos pasar los punteros primitivos de C
    SDL_SetRenderTarget(renderer.Get(), stencil.Get());
    renderer.SetDrawColor(0, 0, 0);
    SDL_RenderClear(renderer.Get());

    // Acá  dibujamos nuestros "focos de luz" usando las primitivas de SDL2 gfx
    boxRGBA(renderer.Get(), 200, 200, 250, 250, 0xff, 0xff, 0xff, 0xff);
    filledCircleRGBA(renderer.Get(), 300, 300, 20, 0xff, 0xff, 0xff, 0xff);

    // Para dibujar un poligono, le tenemos que pasar las posiciones (x,y) de cada uno de los vertices.
    // Como queremos dibujar un triangulo, le pasamos 3 vertices (300, 200) (400, 200) y (350,300)
    const short triangle_x[] = { 300, 400, 350 };
    const short triangle_y[] = {200, 200, 300};
    filledPolygonRGBA(renderer.Get(),
                      triangle_x,
                      triangle_y,
                      3,
                      0xff,
                      0xff,
                      0xff,
                      0xff);

    // Una vez dibujados los focos de luz, necesitamos crear una superficie, para aplicarle color keying (filtrar
    // el color blanco) y volvernos a quedar con la textura final). Este proceso es MUY costoso, y no debe
    // hacerse en cada ciclo del gameloop, o haría nuestro juego muy lento
    SDL2pp::Surface surf(
            0, width, height, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000
    );

    // Copiamos la textura recientemente dibujada en una superficie
    int s = SDL_RenderReadPixels(
            renderer.Get(), NULL, SDL_PIXELFORMAT_ARGB8888, surf.Get()->pixels, surf.Get()->pitch
    );
    if (s != 0) {
        throw SdlException("Error reading pixels from texture");
    }

    // Creamos una nueva textura con las transformaciones deseadas.
    stencil = SDL2pp::Texture(renderer, surf.SetColorKey(true, 0xffffff));

    // Configuramos al renderer para que vuelva a dibujar en la ventana
    SDL_SetRenderTarget(renderer.Get(), nullptr);

    // Le aplicamostransparencia al fondo negro
    stencil.SetBlendMode(SDL_BLENDMODE_BLEND).SetAlphaMod(0xf0);

}

void DynamicStencil::render(SDL2pp::Renderer &renderer, const SDL2pp::Rect &dest, float angle, SDL_RendererFlip flipType) {
    renderer.Copy(
            stencil,
            SDL2pp::Rect(0, 0, width,height),
            dest,
            angle,                     // don't rotate
            SDL2pp::NullOpt,    // rotation center - not needed
            flipType
    );

}
