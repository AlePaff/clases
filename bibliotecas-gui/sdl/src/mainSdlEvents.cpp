#include <SDL2/SDL.h>
#include <iostream>
#include <exception>
#include "SdlWindow.h"
#include "SdlTexture.h"
#include "Animation.h"

int main(int argc, char** argv){
    try {
        SdlWindow window(800, 600);
        window.fill();
        // Usar factory
        SdlTexture im("assets/wwalk2.png", window, Color{0x7f, 0x7f, 0xbb});
        Animation an(&im);
        SDL_RendererFlip flip = SDL_FLIP_NONE;
        bool running = true;
        int x = 100;
        int y = 150;
        while (running) {
            SDL_Event event;
            window.fill(); // Repinto el fondo gris
            // Para el alumno: Buscar diferencia entre waitEvent y pollEvent
            SDL_WaitEvent(&event);
            switch(event.type) {
                case SDL_KEYDOWN: {
                        SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                        switch (keyEvent.keysym.sym) {
                            case SDLK_LEFT:
                                flip = SDL_FLIP_NONE;
                                
                                x -= 5;
                                an.update(1.0f/25.0f);
                                break;
                            case SDLK_RIGHT:
                                flip = SDL_FLIP_HORIZONTAL;
                                x += 5;
                                an.update(1.0f/25.0f);
                                break;
                            case SDLK_UP:
                                y -= 10;
                                break;
                            case SDLK_DOWN:
                                y += 10;
                                break;
                            }
                    } // Fin KEY_DOWN
                    break;
                case SDL_MOUSEMOTION:
                    std::cout << "Oh! Mouse" << std::endl;
                    break;
                case SDL_QUIT:
                    std::cout << "Quit :(" << std::endl;
                    running = false;
                    break;
            }
            Area destArea(x, y, 60, 60);
            an.render(destArea, flip);
            window.render();
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}

