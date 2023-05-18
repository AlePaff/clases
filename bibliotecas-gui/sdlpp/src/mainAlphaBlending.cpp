#include <SDL2pp/SDL2pp.hh>
#include <iostream>
#include <exception>
#include <unistd.h>

#include "Player.h"
#include "DynamicStencil.h"

static bool handleEvents(float &angle);
static void render(
        SDL2pp::Window &window,
        SDL2pp::Renderer &renderer,
        SDL2pp::Texture& background,
        //SDL2pp::Texture& stencil,
        DynamicStencil &stencil,
        float angle);

int main(int argc, char** argv){
    try {
        // Inicializo biblioteca de SDL
        SDL2pp::SDL sdl(SDL_INIT_VIDEO);
        // Creo una ventana dinamica con titulo "Hello world"
        SDL2pp::Window window("Hello world", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            800, 600, SDL_WINDOW_RESIZABLE);

        // Creo renderer
        SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

        // Usar factory
        SDL2pp::Texture background(renderer,
            SDL2pp::Surface("assets/juego.png").SetColorKey(true, 0));

        // Cargo la imagen como textura, avisandolé a SDL que todo lo que sea de color blanco (0xffffff)
        // debe ser transparente en el dibujado (color keying).
        // El blending se usa para superponer dos texturas (como esto emula la sombra, quiero que sea semi-transparente)
        // El valor final es el alfa, que tan opaco quiero que se vea la imagen, a valor mas alto, menos transparente es.
        //SDL2pp::Texture stencil(renderer, SDL2pp::Surface("assets/stencil2.png").SetColorKey(true, 0xFFFFFF));
        //stencil.SetBlendMode(SDL_BLENDMODE_BLEND).SetAlphaMod(250);

        DynamicStencil stencil(renderer, 600,600);
        
        bool running = true;
        float angle = 0;
        // Gameloop, notar como tenemos desacoplado el procesamiento de los inputs (handleEvents)
        // del update del modelo.
        while (running) {
            running = handleEvents(angle);
            render(window, renderer, background, stencil, angle);
            // la cantidad de segundos que debo dormir se debe ajustar en función
            // de la cantidad de tiempo que demoró el handleEvents y el render
            usleep(FRAME_RATE);
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}

/**
 * Va a tomar un evento de teclado, y actualizará el modelo en función de los eventos que lleguen.
 * En un juego real no se tomará de a un evento por vuelta del gameloop, sino que se deberán tomar TODOS
 * o N eventos por vuelta
 */
static bool handleEvents(float &angle) {
    SDL_Event event;
    // Para el alumno: Buscar diferencia entre waitEvent y pollEvent
    while(SDL_PollEvent(&event)){
        switch(event.type) {
            case SDL_KEYDOWN: {
                // ¿Qué pasa si mantengo presionada la tecla?    
                SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                switch (keyEvent.keysym.sym) {
                    case SDLK_LEFT:
                        angle+=10.0f;
                        break;
                    case SDLK_RIGHT:
                        angle-=10.0f;
                        break;
                    }
                } // Fin KEY_DOWN
                break;
            case SDL_QUIT:
                std::cout << "Quit :(" << std::endl;
                return false;
        } // fin switch(event)
    } // fin while(SDL_PollEvents)
    return true;
}

static void render(
        SDL2pp::Window &window,
        SDL2pp::Renderer &renderer,
        SDL2pp::Texture& background,
        //SDL2pp::Texture& stencil,
        DynamicStencil &stencil,
        float angle) {
    renderer.Clear();
    renderer.Copy(
        background,
        SDL2pp::Rect(0, 0, 300, 300),
        SDL2pp::Rect((window.GetWidth() / 2) - 400, (window.GetHeight() / 2) - 300, 800, 600),
        0.0,                // don't rotate
        SDL2pp::NullOpt,    // rotation center - not needed
        SDL_FLIP_NONE
    );
    // El destination del stencil es mas grande que el tamaño de la pantalla para evitar fugas de luz
    /*renderer.Copy(
            stencil,
            SDL2pp::Rect(0, 0, 500, 500),
            SDL2pp::Rect((window.GetWidth() / 2) - 500, (window.GetHeight() / 2) - 500, 1000, 1000),
            angle,              // don't rotate
            SDL2pp::NullOpt,    // rotation center - not needed
            SDL_FLIP_NONE
    );*/
    stencil.render(
            renderer,
            SDL2pp::Rect((window.GetWidth() / 2) - 500, (window.GetHeight() / 2) - 500, 1000, 1000),
            angle,
            SDL_FLIP_NONE
    );
    renderer.Present();
}
