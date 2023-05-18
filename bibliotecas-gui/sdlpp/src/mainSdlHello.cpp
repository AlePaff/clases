#include <iostream>
#include <exception>
#include <SDL2pp/SDL2pp.hh>

int main(int argc, char** argv){
    try {
        // Inicializo biblioteca de SDL
        SDL2pp::SDL sdl(SDL_INIT_VIDEO);
        // Creo una ventana dinamica con titulo "Hello world"
        SDL2pp::Window window("Hello world", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            800, 600,
            SDL_WINDOW_RESIZABLE);

        // Creo renderer
        SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

        // Usar factory
        SDL2pp::Texture sprite(renderer, "assets/cat.gif");

        // modulación de color. Con esta técnica simple podemos con un solo sprite crear
        // y mostrar distintos players, pintandolós de colores distintos. Cambiá los valores de RGB
        // para ver como cambia el resultado final!
        //sprite.SetColorMod(0,0, 0xff);

        // Clear screen
        renderer.Clear();

        // Render our image, stretching it to the whole window
        renderer.Copy(sprite);

        // Show rendered frame
        renderer.Present();

        SDL_Delay(30000);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
