#include <SDL2pp/SDL2pp.hh>
#include <iostream>
#include <exception>
#include <unistd.h>
#include <vector>

#include "Player.h"
#include <SDL2pp/SDLMixer.hh>
#include <SDL2pp/Mixer.hh>
#include <SDL2pp/Chunk.hh>
#include <SDL2pp/SDLTTF.hh>
#include <SDL2pp/Font.hh>

static bool handleEvents(Player &player);
static void render(SDL2pp::Renderer &renderer, Player &player,std::vector<SDL2pp::Texture> &textures);
static void update(Player &player, float dt);

int main(int argc, char** argv){
    try {
        // Inicializo biblioteca de SDL
        SDL2pp::SDL sdl(SDL_INIT_VIDEO);
        SDL2pp::SDLTTF ttf;
        // Creo una ventana dinamica con titulo "Hello world"
        SDL2pp::Window window("Hello world", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            800, 600, SDL_WINDOW_RESIZABLE);
        SDL2pp::Mixer mixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);

        SDL2pp::Chunk sound("assets/MurderTrain.wav");
        mixer.PlayChannel(-1, sound);
        // Creo renderer
        SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);
        
        SDL2pp::Font font("./assets/fefo.TTF", 100);

        std::vector<SDL2pp::Texture> textures;
        textures.emplace_back(renderer,
            font.RenderText_Solid("Hello, world! (solid mode)", SDL_Color{0xff,0xff,0,0xff})
        );

        // Usar factory
        SDL2pp::Texture im(renderer, 
            SDL2pp::Surface("assets/soldier2.png").SetColorKey(true, 0));

        Player player(im);
        bool running = true;
        // Gameloop, notar como tenemos desacoplado el procesamiento de los inputs (handleEvents)
        // del update del modelo.
        while (running) {
            running = handleEvents(player);
            update(player, FRAME_RATE);
            render(renderer, player, textures);
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
static bool handleEvents(Player &player) {
    SDL_Event event;
    // Para el alumno: Buscar diferencia entre waitEvent y pollEvent
    while(SDL_PollEvent(&event)){
        switch(event.type) {
            case SDL_KEYDOWN: {
                // ¿Qué pasa si mantengo presionada la tecla?    
                SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                switch (keyEvent.keysym.sym) {
                    case SDLK_LEFT:
                        player.moveLeft();
                        break;
                    case SDLK_RIGHT:
                        player.moveRigth();
                        break;
                    }
                } // Fin KEY_DOWN
                break;
            case SDL_KEYUP: {
                SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                switch (keyEvent.keysym.sym) {
                    case SDLK_LEFT:
                        player.stopMoving();
                        break;
                    case SDLK_RIGHT:
                        player.stopMoving();
                        break;
                    } 
                }// Fin KEY_UP
                break;
            case SDL_MOUSEMOTION:
                std::cout << "Oh! Mouse" << std::endl;
                break;
            case SDL_QUIT:
                std::cout << "Quit :(" << std::endl;
                return false;
        } // fin switch(event)
    } // fin while(SDL_PollEvents)
    return true;
}

static void render(SDL2pp::Renderer &renderer, Player &player, std::vector<SDL2pp::Texture> &textures) {
    renderer.SetDrawColor(0xFF,0xFF,0xFF,0xFF);
    renderer.Clear();
    player.render(renderer);
    for (auto& texture: textures) {
        renderer.Copy(texture, SDL2pp::NullOpt, SDL2pp::Rect(50, 50, texture.GetWidth(), texture.GetHeight()));
    }

    renderer.Present();
}

static void update(Player &player, float dt) {
    player.update(dt);
}