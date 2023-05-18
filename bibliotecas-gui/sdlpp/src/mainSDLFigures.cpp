//
// Created by fedemgp on 01/05/23.
//
#include <iostream>
#include <exception>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <csignal>

#define WIDTH 640
#define HEIGHT 480

static void render(SDL2pp::Renderer &renderer);
static bool handleEvents();

int main(int argc, char** argv){
    try {
        // Inicializo biblioteca de SDL
        SDL2pp::SDL sdl(SDL_INIT_VIDEO);
        // Creo una ventana dinamica con titulo "Hello world"
        SDL2pp::Window window("Hello world", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              WIDTH, HEIGHT,
                              SDL_WINDOW_RESIZABLE);

        // Creo renderer
        SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

        bool running = true;
        while (running){
            running = handleEvents();
            //update()
            render(renderer);
            // la cantidad de segundos que debo dormir se debe ajustar en función
            // de la cantidad de tiempo que demoró el handleEvents y el render
            usleep(1000000/30);
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}

bool handleEvents() {
    SDL_Event e;
    // Event loop de SDL, proceso todos los eventos de teclado que haya
    // (podrían ser muchos, hay que limitarlo)
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT)
            return false;
    }
    return true;
}

void render(SDL2pp::Renderer &renderer) {
    // Pintamos fondo de gris
    renderer.SetDrawColor(0xff,0xff ,0xff);
    renderer.Clear();

    // Cuadrado que va desde la posición (200, 200) a (250,250)
    boxRGBA(renderer.Get(), 200, 200, 250, 250, 0xff, 0x00, 0xff, 0xff);

    // Circulo de 20 pixeles de radio, de color rojo
    filledCircleRGBA(renderer.Get(), 300, 300, 20, 0, 0, 0xff, 0xff);

    // Para dibujar un poligono, le tenemos que pasar las posiciones (x,y) de cada uno de los vertices.
    // Como queremos dibujar un triangulo, le pasamos 3 vertices (300, 200) (400, 200) y (350,300)
    const short triangle_x[] = { 300, 400, 350 };
    const short triangle_y[] = {
            200, 200, 300
    }; // offset a little to see the line
    filledPolygonRGBA(renderer.Get(),
                      triangle_x,
                      triangle_y,
                      3,
                      0xff,
                      0xff,
                      0xff,
                      0xff);

    renderer.Present();
}