#include <SDL2/SDL.h>
#include <iostream>
#include <exception>
#include <unistd.h>

#include "SdlWindow.h"
#include "SdlTexture.h"
#include "Animation.h"
#include "Player.h"

static bool handleEvents(Player &player);
static void render(SdlWindow &window, Player &player);
static void update(Player &player, float dt);

int main(int argc, char** argv){
    try {
        SdlWindow window(800, 600);
        window.fill();
        // Usar factory
        SdlTexture im("assets/soldier2.png", window, Color{0x00, 0x00, 0x00});
        Player player(im);
        bool running = true;
        // Gameloop, notar como tenemos desacoplado el procesamiento de los inputs (handleEvents)
        // del update del modelo.
        while (running) {
            running = handleEvents(player);
            update(player, FRAME_RATE);
            render(window, player);
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

static void render(SdlWindow &window, Player &player) {
    window.fill(); // Repinto el fondo gris
    player.render();
    window.render();
}

static void update(Player &player, float dt) {
    player.update(dt);
}